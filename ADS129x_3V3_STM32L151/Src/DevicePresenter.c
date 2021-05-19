#include "DevicePresenter.h"
#include "ADS129x_Devices.h"

private DevicePresenter devicePresenter = { 0 };
private ADS_Type* device;
private StatusLed* sLed;

//------------------ Local functions prototypes ------------------------------//
#define TINTREF     1500                                                      // 1.5 sec
private bool Initialize();
private void DefualtConfiguration(SPI_HandleTypeDef * hspi);
private void DeviceDataRead(SPI_HandleTypeDef * hspi, UART_HandleTypeDef * huart);

#ifdef ADS129x

private void ADS129x_DefualtConfiguration(CONFIG1_Type* CONFIG1, CONFIG2_Type* CONFIG2,
                                          CONFIG3_Type* CONFIG3, CONFIG4_Type* CONFIG4,
                                          LOFF_Type* LOFF, CHnSET_Type* CHnSET);

#else

private void ADS1299_DefualtConfiguration(CONFIG1_Type* CONFIG1, CONFIG2_Type* CONFIG2,
                                          CONFIG3_Type* CONFIG3, CONFIG4_Type* CONFIG4,
                                          LOFF_Type* LOFF, CHnSET_Type* CHnSET);

#endif
//----------------------------------------------------------------------------//

DevicePresenter* _DevicePresenter(StatusLed * statusLed)
{
  device = GetInstance();

  sLed = statusLed;

  devicePresenter.Initialize = Initialize;
  devicePresenter.ReadData = DeviceDataRead;
  devicePresenter.CustomConfiguration = NULL;

  return &devicePresenter;
}

//------------------ Local functions -----------------------------------------//
private bool Initialize(SPI_HandleTypeDef * hspi)
{
  IPowerManager *powerManager = device->powerManager;
  ICommand *systemCommands = device->systemCommands;
  ID_Type *ID = &device->ID;

  powerManager->PowerDown();
  HAL_Delay(TINTREF);
  powerManager->PowerUp(hspi, systemCommands->ResetTheDevice);

  systemCommands->EnterStandlyMode(hspi);
  systemCommands->DisableReadDataContinuousMode(hspi);
  systemCommands->StopConversetion(hspi);

  ID->BYTE = ID->GetID(hspi, ID->ADDR);

  uint8_t repetitions = 0;
  volatile uint32_t blinkDelay = 100;

#ifdef ADS129x

  if( (ID->BYTE == ADS1294R) || (ID->BYTE == ADS1296R) || (ID->BYTE == ADS1298R) )
  {
    blinkDelay = 400;    
  }
  else
  {
    blinkDelay = 200;
  }

  if( (ID->BYTE == ADS1294) 
   || (ID->BYTE == ADS1294R) )
  {
    repetitions = 4;
  }

  if( (ID->BYTE == ADS1296) 
   || (ID->BYTE == ADS1296R) )
  {
    repetitions = 6;
  }

  if( (ID->BYTE == ADS1298) 
   || (ID->BYTE == ADS1298R) )
  {
    repetitions = 8;
  }

#else

  switch (ID->BITS.NU_CH)
  {
    case ADS1299_4:
      repetitions = 4;
      break;

    case ADS1299_6:
      repetitions = 6;
      break;
    
    case ADS1299_8:
      repetitions = 8;
      break;
  }
  
#endif

  InitBlink(sLed, repetitions, blinkDelay);
  if(devicePresenter.CustomConfiguration == NULL)
  {
    DefualtConfiguration(hspi);
  }
  else
  {
    devicePresenter.CustomConfiguration(hspi);
  }
  
  systemCommands->StartConversetion(hspi);
  systemCommands->EnableReadDataContinuousMode(hspi);
  systemCommands->WakeUpFromStandlyMode(hspi);

  return true;
}

private void DeviceDataRead(SPI_HandleTypeDef * hspi, UART_HandleTypeDef * huart)
{
  IReadData* readData = device->readData;

  HAL_UART_Transmit(huart, (uint8_t*)readData->ReadData(hspi)->PACKAGE, readData->pkgSize, 100);

}

private void DefualtConfiguration(SPI_HandleTypeDef * hspi)
{
  CONFIG1_Type* CONFIG1 = &device->CONFIG1;
  CONFIG2_Type* CONFIG2 = &device->CONFIG2;
  CONFIG3_Type* CONFIG3 = &device->CONFIG3;
  CONFIG4_Type* CONFIG4 = &device->CONFIG4;
  LOFF_Type* LOFF = &device->LOFF;
  
  CHnSET_Type* CHnSET = device->CHnSET;

#ifdef ADS129x

  ADS129x_DefualtConfiguration(CONFIG1,CONFIG2,CONFIG3,CONFIG4,LOFF,CHnSET);

#else

  ADS1299_DefualtConfiguration(CONFIG1,CONFIG2,CONFIG3,CONFIG4,LOFF,CHnSET);

#endif

  CONFIG3->SetCONFIG3(hspi,CONFIG3->ADDR,CONFIG3->BYTE);
  CONFIG1->SetCONFIG1(hspi,CONFIG1->ADDR,CONFIG1->BYTE);
  CONFIG2->SetCONFIG2(hspi,CONFIG2->ADDR,CONFIG2->BYTE);

  LOFF->SetLOFF(hspi,LOFF->ADDR,LOFF->BYTE);
  CONFIG4->SetCONFIG4(hspi,CONFIG4->ADDR,CONFIG4->BYTE);

  for(int i = 0; i <= (int)(CH8SET_ADDRESS - CH1SET_ADDRESS); i++)
  {
    CHnSET[i].SetCHnSET(hspi,CHnSET[i].ADDR,CHnSET[i].BYTE);
  }
  
}

#ifdef ADS129x

private void ADS129x_DefualtConfiguration(CONFIG1_Type* CONFIG1, CONFIG2_Type* CONFIG2,
                                          CONFIG3_Type* CONFIG3, CONFIG4_Type* CONFIG4,
                                          LOFF_Type* LOFF, CHnSET_Type* CHnSET)
{
  CONFIG3->BITS.PD_REFBUF = REF_BUFF_ENABLE;
  CONFIG3->BITS.VREF = VREF_2V4;
  CONFIG3->BITS.RLD_MEAS = CLOSE;
  CONFIG3->BITS.RLDREF_INT = REF_SIGNAL_INT;
  CONFIG3->BITS.PD_RLD = BUF_ENABLE;
  CONFIG3->BITS.RLD_LOFF_SENS = LOFF_SENS_DISABLE;

  CONFIG1->BITS.HR = HRM;
  CONFIG1->BITS.DAISY_EN = MULT_READBACK;
  CONFIG1->BITS.CLK_EN = OSC_OUT_DISABLE;
  CONFIG1->BITS.DR = SPS_500_HR_250_LP;

  CONFIG2->BITS.INT_TEST = SOURCE_SIGNAL_INT;
  CONFIG2->BITS.TEST_AMP = SIGNAL_AMP_2;
  CONFIG2->BITS.TEST_FREQ = SIGNAL_FREQ_20;
  CONFIG2->BITS.WCT_CHOP = FR_VARIES;

  LOFF->BITS.COMP_TH = COMP_TH_95_5;
  LOFF->BITS.ILEAD_OFF = I_LEAD_OFF_6nA;
  LOFF->BITS.FLEAD_OFF = F_LEAD_OFF_AC;
  LOFF->BITS.VLEAD_OFF_EN = VLEAD_OFF_EN_CS;

  CONFIG4->BITS.PD_LOFF_COMP = PD_LOFF_COMP_DISABLED;
  CONFIG4->BITS.RESP_FREQ = RESP_FREQ_64kHZ;
  CONFIG4->BITS.SINGLE_SHOT = CONTINIUS_CONVERSETION_MODE_SH;
  CONFIG4->BITS.WCT_TO_RLD = WCT_TO_RLD_OFF;

  for(int i = 0; i <= (int)(CH8SET_ADDRESS - CH1SET_ADDRESS); i++)
  {
    CHnSET[i].BITS.GAIN = PGA_12;
    CHnSET[i].BITS.MUX = MUX_NORMAL_ELEC_INPUT;
    CHnSET[i].BITS.PD = PD_NORMAL;
  }
  CHnSET[7].BITS.MUX = MUX_USED_WITH_RLD_MEAS_bit;

}

#else

private void ADS1299_DefualtConfiguration(CONFIG1_Type* CONFIG1, CONFIG2_Type* CONFIG2,
                                          CONFIG3_Type* CONFIG3, CONFIG4_Type* CONFIG4,
                                          LOFF_Type* LOFF, CHnSET_Type* CHnSET)
{
  CONFIG3->BITS.PD_REFBUF = REF_BUFF_ENABLE;
  CONFIG3->BITS.BIAS_MEAS = CLOSE;
  CONFIG3->BITS.BIASREF_INT = REF_SIGNAL_INT;
  CONFIG3->BITS.PD_BIAS = BUF_ENABLE;
  CONFIG3->BITS.BIAS_LOFF_SENS = LOFF_SENS_DISABLE;

  CONFIG1->BITS.DAISY_EN = MULT_READBACK;
  CONFIG1->BITS.CLK_EN = OSC_OUT_DISABLE;
  CONFIG1->BITS.DR = SPS_500;

  CONFIG2->BITS.INT_CAL = SOURCE_SIGNAL_INT;
  CONFIG2->BITS.CAL_AMP = SIGNAL_AMP_2;
  CONFIG2->BITS.CAL_FREQ = SIGNAL_FREQ_20;

  LOFF->BITS.COMP_TH = COMP_TH_95_5;
  LOFF->BITS.ILEAD_OFF = I_LEAD_OFF_6nA;
  LOFF->BITS.FLEAD_OFF = F_LEAD_OFF_AC;

  CONFIG4->BITS.PD_LOFF_COMP = PD_LOFF_COMP_DISABLED;
  CONFIG4->BITS.SINGLE_SHOT = CONTINIUS_CONVERSETION_MODE_SH;

  for(int i = 0; i <= (int)(CH8SET_ADDRESS - CH1SET_ADDRESS); i++)
  {
    CHnSET[i].BITS.GAIN = PGA_24;
    CHnSET[i].BITS.MUX = MUX_NORMAL_ELEC_INPUT;
    CHnSET[i].BITS.PD = PD_NORMAL;
    CHnSET[i].BITS.SRB2 = SRB2_OPEN;
  }
  CHnSET[7].BITS.MUX = MUX_USED_WITH_BIAS_MEAS_bit;
}

#endif