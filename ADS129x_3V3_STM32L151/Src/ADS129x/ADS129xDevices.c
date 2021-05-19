#include "ADS129x_Devices.h"
#include "Utils.h"

private ADS_Type device = {0};

public ADS_Type * GetInstance()
{  
  device.ID.ADDR = ID_ADDRESS;          
  device.ID.BYTE = ID_RST_VALUE;
  device.ID.GetID = RREG;
  
  device.CONFIG1.ADDR = CONFIG1_ADDRESS;
  device.CONFIG1.BYTE = CONFIG1_RST_VALUE;
  device.CONFIG1.GetCONFIG1 = RREG;
  device.CONFIG1.SetCONFIG1 = WREG;
  
  device.CONFIG2.ADDR = CONFIG2_ADDRESS;
  device.CONFIG2.BYTE = CONFIG2_RST_VALUE;
  device.CONFIG2.GetCONFIG2 = RREG;
  device.CONFIG2.SetCONFIG2 = WREG;
  
  device.CONFIG3.ADDR = CONFIG3_ADDRESS;
  device.CONFIG3.BYTE = CONFIG3_RST_VALUE;
  device.CONFIG3.GetCONFIG3 = RREG;
  device.CONFIG3.SetCONFIG3 = WREG;
  
  device.LOFF.ADDR = LOFF_ADDRESS;
  device.LOFF.BYTE = LOFF_RST_VALUE;
  device.LOFF.GetLOFF = RREG;
  device.LOFF.SetLOFF = WREG;
  
  for(int i = 0; i <= (int)(CH8SET_ADDRESS - CH1SET_ADDRESS); i++)
  {
    device.CHnSET[i].ADDR = (uint8_t)i + CH1SET_ADDRESS;
    device.CHnSET[i].BYTE = CHnSET_RST_VALUE;
    device.CHnSET[i].GetCHnSET = RREG;
    device.CHnSET[i].SetCHnSET = WREG;
  }

#ifdef ADS129x
  
  device.RLD_SENSP.ADDR = RLD_SENSP_ADDRESS;   
  device.RLD_SENSP.BYTE = RLD_SENSP_RST_VALUE;
  device.RLD_SENSP.GetRLD_SENSP = RREG;
  device.RLD_SENSP.SetRLD_SENSP = WREG;
    
  device.RLD_SENSN.ADDR = RLD_SENSN_ADDRESS;
  device.RLD_SENSN.BYTE = RLD_SENSN_RST_VALUE;
  device.RLD_SENSN.GetRLD_SENSN = RREG;
  device.RLD_SENSN.SetRLD_SENSN = WREG;
  
#else 
  
  device.BIAS_SENSP.ADDR = BIAS_SENSP_ADDRESS;
  device.BIAS_SENSP.BYTE = BIAS_SENSP_RST_VALUE;
  device.BIAS_SENSP.GetBIAS_SENSP = RREG;
  device.BIAS_SENSP.SetBIAS_SENSP = WREG;
  
  device.BIAS_SENSN.ADDR = BIAS_SENSN_ADDRESS;
  device.BIAS_SENSN.BYTE = BIAS_SENSN_RST_VALUE;
  device.BIAS_SENSN.GetBIAS_SENSN = RREG;
  device.BIAS_SENSN.SetBIAS_SENSN = WREG;
  
#endif
  
  device.LOFF_SENSP.ADDR = LOFF_SENSP_ADDRESS;  
  device.LOFF_SENSP.BYTE = LOFF_SENSP_RST_VALUE;
  device.LOFF_SENSP.GetLOFF_SENSP = RREG;
  device.LOFF_SENSP.SetLOFF_SENSP = WREG;
  
  device.LOFF_SENSN.ADDR = LOFF_SENSN_ADDRESS;
  device.LOFF_SENSN.BYTE = LOFF_SENSN_RST_VALUE;
  device.LOFF_SENSN.GetLOFF_SENSN = RREG;
  device.LOFF_SENSN.SetLOFF_SENSN = WREG;
  
  device.LOFF_FLIP.ADDR = LOFF_FLIP_ADDRESS;   
  device.LOFF_FLIP.BYTE = LOFF_FLIP_RST_VALUE;
  device.LOFF_FLIP.GetLOFF_FLIP = RREG;
  device.LOFF_FLIP.SetLOFF_FLIP = WREG;
  
  device.LOFF_STATP.ADDR = LOFF_STATP_ADDRESS;
  device.LOFF_STATP.BYTE = LOFF_STATP_RST_VALUE;
  device.LOFF_STATP.GetLOFF_STATP = RREG;
  
  device.LOFF_STATN.ADDR = LOFF_STATN_ADDRESS;  
  device.LOFF_STATN.BYTE = LOFF_STATN_RST_VALUE;
  device.LOFF_STATN.GetLOFF_STATN = RREG;
  
  device.CONFIG4.ADDR = CONFIG4_ADDRESS;
  device.CONFIG4.BYTE = CONFIG4_RST_VALUE;
  device.CONFIG4.GetCONFIG4 = RREG;
  device.CONFIG4.SetCONFIG4 = WREG;
  
  device.powerManager = PowerManager();  
  device.systemCommands = SystemCommands();
  device.readData = ReadData();
    
  return &device;
}