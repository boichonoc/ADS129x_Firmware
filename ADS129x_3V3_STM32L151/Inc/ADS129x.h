#ifndef ADS129x
#define ADS129x

//Opcode Command Definitions
#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stm32l1xx_hal.h"


#define cs_Set()   HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)
#define cs_Reset() HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)

//SYSTEM COMMANDS  
enum SystemCommand
{
  WAKEUP = 0x02,        // WAKE UP from standly mode
  STANDY = 0x04,        // STANDBY - Enter standly mode
  RESET_DEV  = 0x06,        // RESET the device
  START  = 0x08,        // START/RESTART (synchronize) conversions
  STOP   = 0x0A         // STOP conversion
};
//DATA READ MODE
enum DataReadMode
{
  RDATAC = 0x10,        // Enable Read Data Continuous mode(defaulte mode at power up)
  SDATAC = 0x11,        // Stop read Data Continuously mode
  RDATA  = 0x12         // Read data by command; supports multiple read back
};
enum index_rw
{
  Read  = 0x20,         // Read from regist
  Write = 0x40          // Write to regist
};

enum RegisterAddress
{
//------------------------------------------------------- Read Only ID Registers
  ID = 0x00,
//---------------------------------------------- Global Settings Across Channels
  CONFIG1 = 0x01,
  CONFIG2 = 0x02,
  CONFIG3 = 0x03,
  LOFF = 0x04,
//---------------------------------------------------- Channel-Specific Settings 
  CH1SET = 0x05,
  CH2SET = 0x06,
  CH3SET = 0x07,
  CH4SET = 0x08,
  CH5SET = 0x09,
  CH6SET = 0x0A,
  CH7SET = 0x0B,
  CH8SET = 0x0C,  
  RLD_SENS_P = 0x0D,
  RLD_SENS_N = 0x0E,
  LOFF_SENS_P = 0x0F,
  LOFF_SENS_N = 0x10,
  LOFF_FLIP = 0x11,
//------------------------------ Lead-Off Status Registers (Read-Only Registers)
  LOFF_STAT_P = 0x12,
  LOFF_STAT_N = 0x13,
//----------------------------------------------------- GPIO and OTHER Registers
  GPIO = 0x14, 
  PACE = 0x15, 
  RESP = 0x16,
  CONFIG4 = 0x17,
  WCT1 = 0x18,  
  WCT2 = 0x19  
};
//------------------------------------------------------------------------------
//Reset DATA value (HEX) *******************************************************

//Global Settings Across Channels

#define CONFIG1_DATA 0x06 // CONFIG1
#define CONFIG2_DATA 0x40 // CONFIG2
#define CONFIG3_DATA 0xC0 // CONFIG3
#define LOFF_DATA    0x00 // LOFF

//CHanel-Specific Settings

#define CH1SET_DATA  0x00 // CH1SET
#define CH2SET_DATA  0x00 // CH2SET
#define CH3SET_DATA  0x00 // CH3SET
#define CH4SET_DATA  0x00 // CH4SET
#define CH5SET_DATA  0x00 // CH5SET
#define CH6SET_DATA  0x00 // CH6SET
#define CH7SET_DATA  0x00 // CH7SET
#define CH8SET_DATA  0x00 // CH8SET

#define RLD_SENSP_DATA  0x00 // RLD_SENSP
#define RLD_SENSN_DATA  0x00 // RLD_SENSN

#define LOFF_SENSP_DATA 0x00 // LOFF_SENSP
#define LOFF_SENSN_DATA 0x00 // LOFF_SENSN
#define LOFF_FLIP_DATA  0x00 // LOFF_FLIP

//Lead-Off Status Registers (Read-Only Registers)

#define LOFF_STATP_DATA 0x00 // LOFF_STATP
#define LOFF_STATN_DARA 0x00 // LOFF_STATN

//GPIO and Others Registers

#define GPIO_DATA    0x0F // GPIO
#define PACE_DATA    0x00 // PACE
#define RESP_DATA    0x00 // RESP
#define CONFIG4_DATA 0x00 // CONFIG4
#define WCT1_DATA    0x00 // WCT1
#define WCT2_DATA    0x00 // WCT2

//==============================================================================
//-- “айминги дл€ запуска микросхемы. —огласно ƒаташиту. -----------------------

//#define TCLK       1      // Tclk = 420 ns
//#define TPOR       32768  // 110 // Tpor = 2^18 * Tclk   

#define TCSSC   1 // 6 ns
#define TSCCS   2 // 4 TCLKs
#define TPOR    110 // 2^16 TCLKs
#define TRST    2 // 2 TCLKs 
#define TRST2   16 // 18 TCLKs
#define TINTREF 150000 // 150ms
#define TCMD    2 // 4 TCLKs
#define TCSH    1 // 2 TCLKs

//Regisres *********************************************************************
//-------- ID Register ---------------------------------------------------------
union DeviceID
{
  uint8_t Value;
  struct
  {
    const uint8_t NumberOfChannels     : 2;
    const uint8_t DeviceIdentification : 2;
    const uint8_t Reserves             : 1;
    const uint8_t RevisionOfTheDevice  : 3;
  } BIT;  
};
//------------------------------------------------------------------------------
enum id_value
{
  ADS1294 = 0x90,  // 4-channel ADS1294
  ADS1296 = 0x91,  // 6-channel ADS1296
  ADS1298 = 0x92,  // 8-channel ADS1298
//  ADS1299 = 0b1110 // 8-channel ADS1299
 
  ADS1294R = 0xD0, // 4-channel ADS1294R
  ADS1296R = 0xD1, // 6-channel ADS1296R
  ADS1298R = 0xD2, // 8-channel ADS1298R
};
//-------- CONFIG 1 ------------------------------------------------------------
union FirstConfigurationRegister
{
  uint8_t Value;
  struct 
  {
    uint8_t OutputDataRate  : 3;
    uint8_t Reserves        : 2;
    uint8_t ClockConnection : 1;
    uint8_t ReadbackMode    : 1;
    uint8_t PowerMode       : 1;  
  } BIT;
};
//------------------------------------------------------------------------------
//This bit determines whether the device runs
enum PowerMode
{
  LowPower = 0x00,          // in low-power 
  HighResolution = 0x01     // or high-resolution mode
};
//This bit determines which mode is enable
enum ReadbackMode
{
  DeisyChain = 0x00,        // Daisy-chain mode
  MultipleReadback = 0x01   // Multiple readback mode
};
//This bit determines if the internal oscilator signal is connedted to the CLK pin when CLKSEL_pin = 1.
enum ClockConnection
{
  Disable = 0x00,           // OSC output disabled
  Enable = 0x01             // OSC output enabled
};
//This bit determine the output data rate of the device 
enum OutputDataRate
{
  SPS_32K_HR_16K_LP = 0x00, // HR Mode: 32kSPS, LP Mode: 16kSPS
  SPS_16K_HR_8K_LP  = 0x01, // HR Mode: 16kSPS, LP Mode: 8kSPS
  SPS_8K_HR_4K_LP   = 0x02, // HR Mode: 8kSPS, LP Mode: 4kSPS
  SPS_4K_HR_2K_LP   = 0x03, // HR Mode: 4kSPS, LP Mode: 2kSPS
  SPS_2K_HR_1K_LP   = 0x04, // HR Mode: 2kSPS, LP Mode: 1kSPS
  SPS_1K_HR_500_LP  = 0x05, // HR Mode: 1kSPS, LP Mode: 500SPS
  SPS_500_HR_250_LP = 0x06  // HR Mode: 500SPS, LP Mode: 250SPS
};
//------------------------------------------------------------------------------
//-------- CONFIG 2 ------------------------------------------------------------

#define CONFIG2_const     0x00

//This bit determines whether the chopping frequency of WCT amplifiers is variable or fixed
#define WCT_CHOP_FrVaries 0x00 //Chopping frequency varies, see Table 7 (in datasheet)
#define WCT_CHOP_FrCONST  0x20 //Chopping frequency constant at fMOD / 16
//This bit determines the source for the test signal.
#define INT_TEST_EXT      0x00 //Test signals are driven externally
#define INT_TEST_INT      0x10 //Test signals are generated internally
//These bits determine the calibration signal amplitude.
#define TEST_SIGNAL_AMP_1 0x00 // 1 x Ц(VREFP Ц VREFN) / 2400 V
#define TEST_SIGNAL_AMP_2 0x04 // 2 x Ц(VREFP Ц VREFN) / 2400 V
//These bits determine the calibration signal frequency
#define TEST_FREQ_21      0x00 // Pulsed at fCLK / 2^21
#define TEST_FREQ_20      0x01 // Pulsed at fCLK / 2^20
#define TEST_FREQ_NOT_USE 0x02 // Not used
#define TEST_FREQ_AT_DC   0x03 // At dc

//------------------------------------------------------------------------------
//-------- CONFIG 3 ------------------------------------------------------------

#define CONFIG3_const 0x40

//This bit determines the power-down reference buffer state.
#define PD_REFBUF_PWDN_INT 0x40 //Power-down internal reference buffer
#define PD_REFBUF_ENAB_INT 0xC0 //Enable internal reference buffer
//This bit determines the reference voltage, VREFP
#define VREF_2V4 0x40 //VREFP is set to 2.4 V
#define VREF_4V 0x60  //VREFP is set to 4 V (use only with a 5-V analog supply)
//This bit enables RLD measurement. The RLD signal may be measured with any channel.
#define RLD_MEAS_OPEN 0x40 //Open
#define RLD_MEAS_FOR_MUX_010 0x50 //RLD_IN signal is routed to the channel that has the MUX_Setting 010 (VREF)
//This bit determines the RLDREF signal source.
#define RLDREF_EXT 0x40 //RLDREF signal fed externally
#define RLDREF_INT 0x48 //RLDREF signal (AVDD Ц AVSS) / 2 generated internally
//This bit determines the RLD buffer power state.
#define RLDBUF_DISABLE 0x40 //RLD buffer is powered down
#define RLDBUF_ENABLE 0x44  //RLD buffer is enabled
//This bit enables the RLD sense function.
#define RLD_LOFF_SENS_DISABLE 0x40 //RLD sense is disabled
#define RLD_LOFF_SENS_ENABLE 0x42  //RLD sense is enabled

//------------------------------------------------------------------------------
//-------- LEAD-OFF Control ----------------------------------------------------

#define LEAD_OFF_Const 0x00

#define COMP_TH_95_5    0x00 // Comparator positive side: 95 Comparator negative side: 5
#define COMP_TH_925_75  0x20 // Comparator positive side: 92.5 Comparator negative side: 7.5
#define COMP_TH_90_10   0x40 // Comparator positive side: 90 Comparator negative side: 10
#define COMP_TH_875_125 0x60 // Comparator positive side: 87.5 Comparator negative side: 12.5
#define COMP_TH_85_15   0x80 // Comparator positive side: 85 Comparator negative side: 15
#define COMP_TH_80_20   0xA0 // Comparator positive side: 80 Comparator negative side: 20
#define COMP_TH_75_25   0xC0 // Comparator positive side: 75 Comparator negative side: 25
#define COMP_TH_70_30   0xE0 // Comparator positive side: 70 Comparator negative side: 30
// This bit determines the lead-off detection mode.
#define VLEAD_OFF_EN_CS          0x00 //Current source mode lead-off
#define VLEAD_OFF_EN_Pull_UP_DWN 0x10 //pullup or pulldown resistor mode lead-off
// These bits determine the magnitude of current for the current lead-off mode.
#define I_LEAD_OFF_6nA  0x00 // 6 nA
#define I_LEAD_OFF_12nA 0x40 // 12 nA
#define I_LEAD_OFF_18nA 0x80 // 18 nA
#define I_LEAD_OFF_24nA 0xC0 // 24 nA
// These bits determine the frequency of lead-off detect for each channel.
#define F_LEAD_OFF         0x00 // When any bits of the LOFF_SENSP or LOFF_SENSN
// registers are turned on, make sure that FLEAD[1:0] are either
// set to 01 or 11
#define F_LEAD_OFF_AC      0x01 // AC lead-off detection at fDR / 4
#define F_LEAD_OFF_NOT_USE 0x02 // Do not use
#define F_LEAD_OFF_DC      0x03 // DC lead-off detection turned on

//------------------------------------------------------------------------------
//-------- CONFIG 4 ------------------------------------------------------------

#define CONFIG4_const 0x00

// These bits control the respiration control frequency when
// RESP_CTRL[1:0] = 10 or RESP_CTRL[1:0] = 10(1).

#define RESP_FREQ_64kHZ 0x00 // 64 kHz modulation clock
#define RESP_FREQ_32kHZ 0x20 // 32 kHz modulation clock
#define RESP_FREQ_16kHZ 0x40 // 16kHz square wave on GPIO3 and GPIO04. Output on
// GPIO4 is 180 degree out of phase with GPIO3
#define RESP_FREQ_8kHZ  0x60 // 8kHz square wave on GPIO3 and GPIO04. Output on
// GPIO4 is 180 degree out of phase with GPIO3.
#define RESP_FREQ_4kHZ  0x80 // 4kHz square wave on GPIO3 and GPIO04. Output on
// GPIO4 is 180 degree out of phase with GPIO3.
#define RESP_FREQ_2kHZ  0xA0 // 2kHz square wave on GPIO3 and GPIO04. Output on
// GPIO4 is 180 degree out of phase with GPIO3
#define RESP_FREQ_1kHZ  0xC0 // 1kHz square wave on GPIO3 and GPIO04. Output on
// GPIO4 is 180 degree out of phase with GPIO3.
#define RESP_FREQ_500HZ 0xE0 // 500Hz square wave on GPIO3 and GPIO04. Output on
// GPIO4 is 180 degree out of phase with GPIO3.

// Modes 000 and 001 are modulation frequencies in internal and
// external respiration modes. In internal respiration mode, the
// control signals appear at the RESP_MODP and RESP_MODN
// terminals. All other bit settings generate square waves as
// described above on GPIO4 and GPIO3.

// This bit sets the conversion mode
#define CONTINIUS_CONVERSETION_MODE_SH 0x00 // Continuous conversion mode
#define                 SINGLE_SHOT_SH 0x08 // Single-shot mode
// This bit connects WCT to RLD              
#define                 WCT_TO_RLD_OFF 0x00 // WCT to RLD connection off
#define                  WCT_TO_RLD_ON 0x04 // WCT to RLD connection on
// This bit powers down the lead-off comparators.
#define          PD_LOFF_COMP_DISABLED 0x00 // Lead-off comparators disabled
#define           PD_LOFF_COMP_ENABLED 0x02 // Lead-off comparators enabled

//------------------------------------------------------------------------------
//-------- CH_N_SET_CONFIGS ----------------------------------------------------

#define              CN_N_SET_const 0x00
// This bit determines the channel power mode for the corresponding channel.
#define   PWDN_CHN_NORMAL_OPERATION 0x00 // Normal operation
#define          PWDN_CHN_POWER_OFF 0x80 // Channel power-down
// When powering down a channel, TI recommends that the
// channel be set to input short by setting the appropriate
// MUXn[2:0] = 001 of the CHnSET register.
// These bits determine the PGA gain setting.
#define                       PGA_6 0x00 
#define                       PGA_1 0x10
#define                       PGA_2 0x20
#define                       PGA_3 0x30
#define                       PGA_4 0x40
#define                       PGA_8 0x50
#define                      PGA_12 0x60
// These bits determine the channel input selection.
#define       MUX_NORMAL_ELEC_INPUT 0x00 // Normal electrode input
#define           MUX_INPUT_SHORTED 0x01 // Input shorted (for offset or noise measurements)
#define  MUX_USED_WITH_RLD_MEAS_bit 0x02 // Used in conjunction with RLD_MEAS bit for RLD
// measurements. See the Right Leg Drive (RLD) DC Bias Circuit
// subsection of the ECG-Specific Functions section for more
// details.
#define                    MUX_MVDD 0x03 // MVDD for supply measurement
#define      MUX_TEMPERATURE_SENSOR 0x04 // Temperature sensor
#define             MUX_TEST_SIGNAL 0x05 // Test signal
#define                 MUX_RLD_DRP 0x06 // RLD_DRP (positive electrode is the driver)
#define                 MUX_RLD_DRN 0x07 // RLD_DRN (negative electrode is the driver)

//---------------- Global functions prototypes ---------------------------------//
void Init_ADS1294 (SPI_HandleTypeDef * hspi1, DAC_HandleTypeDef * hdac);        // Init device
void ReadData (SPI_HandleTypeDef * hspi1, UART_HandleTypeDef * huart2);         // Read data from device
//------------------------------------------------------------------------------//
#endif