#ifndef ADS129X_Registers
#define ADS129X_Registers

//Opcode Command Definitions
#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stm32l1xx_hal.h"

//Regisres *********************************************************************
//-------- ID Register ---------------------------------------------------------
typedef union DeviceID
{
  uint8_t Value;
  
  struct
  {
    __IM uint8_t NU_CH:3;
    
    __IM uint8_t _reserved:2;
    
    __IM uint8_t REV_ID:3;
    
  } BIT;

}ID;

//------------------------------------------------------------------------------
#define ADS1294                 0x90 // 4-channel ADS129x
#define ADS1296                 0x91 // 6-channel ADS129x
#define ADS1298                 0x92 // 8-channel ADS129x

#define ADS1294R                0xD0 // 4-channel ADS129xR
#define ADS1296R                0xD1 // 6-channel ADS129xR
#define ADS1298R                0xD2 // 8-channel ADS129xR
//------------------------------------------------------------------------------

//-------- CONFIG 1 ------------------------------------------------------------
typedef union FirstConfigurationRegister
{
  uint8_t Value;
   
  struct
  {
    __IOM uint8_t DR:3;
    
    __IM  uint8_t _reserved:2;
    
    __IOM uint8_t CLK_EN:1;
    
    __IOM uint8_t DAISY_EN:1;
    
    __IOM uint8_t HR:1;
    
  } BIT;
  
} CONFIG1;
//------------------------------------------------------------------------------
//This bit determines whether the device runs
#define LP                      0b0 // in low-power  
#define HR                      0b1 // or high-resolution mode

//This bit determines which mode is enable
#define DEISY_CHAIN             0b0 // Daisy-chain mode
#define MULT_READBACK           0b1 // Multiple readback mode

//This bit determines if the internal oscilator signal is connedted to the CLK pin when CLKSEL_pin = 1.
#define OSC_OUT_DISABLE         0b0  // OSC output disabled
#define OSC_OUT_ENABLE          0b1  // OSC output enabled

//This bit determine the output data rate of the device
#define SPS_32K_HR_16K_LP       0b000 // HR Mode: 32kSPS, LP Mode: 16kSPS
#define SPS_16K_HR_8K_LP        0b000 // HR Mode: 16kSPS, LP Mode: 8kSPS
#define SPS_8K_HR_4K_LP         0b010 // HR Mode: 8kSPS, LP Mode: 4kSPS
#define SPS_4K_HR_2K_LP         0b011 // HR Mode: 4kSPS, LP Mode: 2kSPS
#define SPS_2K_HR_1K_LP         0b100 // HR Mode: 2kSPS, LP Mode: 1kSPS
#define SPS_1K_HR_500_LP        0b101 // HR Mode: 1kSPS, LP Mode: 500SPS
#define SPS_500_HR_250_LP       0b110 // HR Mode: 500SPS, LP Mode: 250SPS

//------------------------------------------------------------------------------

//-------- CONFIG 2 ------------------------------------------------------------
typedef union SecondConfigurationRegister
{
  uint8_t Value;
      
  struct
  {
    __IOM uint8_t TEST_FREQ:2;
    
    __IOM uint8_t TEST_AMP:1;
    
    __IM  uint8_t _reserved0:1;
    
    __IOM uint8_t INT_TEST:1;
    
    __IOM uint8_t WCT_CHOP:1;
    
    __IM  uint8_t _reserved1:2;
    
  } BIT;
  
} CONFIG2;
//------------------------------------------------------------------------------
//This bit determines whether the chopping frequency of WCT amplifiers is variable or fixed
#define FR_VARIES           0b0 //Chopping frequency varies, see Table 7 (in datasheet)
#define FR_CONST            0b1 //Chopping frequency constant at fMOD / 16

//This bit determines the source for the test signal.
#define SOURCE_SIGNAL_EXT   0b0 //Test signals are driven externally
#define SOURCE_SIGNAL_INT   0b1 //Test signals are generated internally

//These bits determine the calibration signal amplitude.
#define SIGNAL_AMP_1        0b0 // 1 x –(VREFP – VREFN) / 2400 V
#define SIGNAL_AMP_2        0b1 // 2 x –(VREFP – VREFN) / 2400 V

//These bits determine the calibration signal frequency
#define SIGNAL_FREQ_21      0b00 // Pulsed at fCLK / 2^21
#define SIGNAL_FREQ_20      0b01 // Pulsed at fCLK / 2^20
#define SIGNAL_FREQ_NOT_USE 0b10 // Not used
#define SIGNAL_FREQ_AT_DC   0b11 // At dc

//------------------------------------------------------------------------------

//-------- CONFIG 3 ------------------------------------------------------------
typedef union ThirdConfigurationRegister
{
  uint8_t Value;
  
  struct
  {
    __IM  uint8_t RLD_STAT:1;
    
    __IOM uint8_t RLD_LOFF_SENS:1;
    
    __IOM uint8_t PD_RLD:1;
    
    __IOM uint8_t RLDREF_INT:1;
    
    __IOM uint8_t RLD_MEAS:1;
    
    __IOM uint8_t VREF_4V:1;
    
    __IM  uint8_t _reserved:1;
    
    __IOM uint8_t PD_REFBUF:1;
  
  } BIT;
    
} CONFIG3;
//------------------------------------------------------------------------------
//This bit determines the power-down reference buffer state.
#define REF_BUFF_DESABLE                0b0 //Power-down internal reference buffer
#define REF_BUFF_ENABLE                 0b1 //Enable internal reference buffer

//This bit determines the reference voltage, VREFP
#define VREF_2V4                        0b0  //VREFP is set to 2.4 V
#define VREF_4V                         0b1  //VREFP is set to 4 V (use only with a 5-V analog supply)

//This bit enables RLD measurement. The RLD signal may be measured with any channel.
#define RLD_OPEN                        0b0 //Open
#define RLD_IN                          0b1 //RLD_IN signal is routed to the channel that has the MUX_Setting 010 (VREF)

//This bit determines the RLDREF signal source.
#define RLD_REF_SIGNAL_EXT              0b0 //RLDREF signal fed externally
#define RLD_REF_SIGNAL_INT              0b1 //RLDREF signal (AVDD – AVSS) / 2 generated internally

//This bit determines the RLD buffer power state.
#define RLD_BUF_DISABLE                 0b0 //RLD buffer is powered down
#define RLD_BUF_ENABLE                  0b1 //RLD buffer is enabled

//This bit enables the RLD(BIAS) sense function.
#define RLD_LOFF_SENS_DISABLE           0b0 //RLD sense is disabled
#define RLD_LOFF_SENS_ENABLE            0b1 //RLD sense is enabled

//------------------------------------------------------------------------------
//-------- LEAD-OFF Control ----------------------------------------------------

typedef union LeadOffControlRegister
{
  uint8_t Value;
  
  struct
  {
    __IOM uint8_t FLEAD_OFF:2;
    
    __IOM uint8_t ILEAD_OFF:2;
        
    __IOM uint8_t VLEAD_OFF_EN:1;
    
    __IOM uint8_t COMP_TH:3;
  
  } BIT;
    
} LOFF;
//------------------------------------------------------------------------------
// Lead-off comparator threshold
#define COMP_TH_95_5                    0b000 // Comparator positive side: 95 Comparator negative side: 5
#define COMP_TH_92_75                   0b001 // Comparator positive side: 92.5 Comparator negative side: 7.5
#define COMP_TH_90_10                   0b010 // Comparator positive side: 90 Comparator negative side: 10
#define COMP_TH_87_12                   0b011 // Comparator positive side: 87.5 Comparator negative side: 12.5
#define COMP_TH_85_15                   0b100 // Comparator positive side: 85 Comparator negative side: 15
#define COMP_TH_80_20                   0b101 // Comparator positive side: 80 Comparator negative side: 20
#define COMP_TH_75_25                   0b110 // Comparator positive side: 75 Comparator negative side: 25
#define COMP_TH_70_30                   0b111 // Comparator positive side: 70 Comparator negative side: 30

// This bit determines the lead-off detection mode.
#define VLEAD_OFF_EN_CS                 0b0   //Current source mode lead-off
#define VLEAD_OFF_EN_Pull_UP_DWN        0b1   //pullup or pulldown resistor mode lead-off

// These bits determine the magnitude of current for the current lead-off mode.
#define I_LEAD_OFF_6nA                  0b00 // 6 nA
#define I_LEAD_OFF_12nA                 0b01 // 12 nA
#define I_LEAD_OFF_18nA                 0b10 // 18 nA
#define I_LEAD_OFF_24nA                 0b11 // 24 nA

// These bits determine the frequency of lead-off detect for each channel.
#define F_LEAD_OFF                      0b00 // When any bits of the LOFF_SENSP or LOFF_SENSN registers are turned on, make sure that FLEAD[1:0] are either set to 01 or 11
#define F_LEAD_OFF_AC                   0b01 // AC lead-off detection at fDR / 4
#define F_LEAD_OFF_NOT_USE              0b10 // Do not use
#define F_LEAD_OFF_DC                   0b11 // DC lead-off detection turned on

//------------------------------------------------------------------------------

//-------- CH_N_SET_CONFIGS ----------------------------------------------------
typedef union IndividualChannelSettingsRegister
{
  uint8_t Value;
  
  struct
  {
    _IOM uint8_t MUX:2;
    
    _IM  uint8_t _reserved:1;
    
    _IOM uint8_t GAIN:2;
    
    _IOM uint8_t PD;
    
  } BIT;
  
} CHnSET;
//------------------------------------------------------------------------------
// This bit determines the channel power mode for the corresponding channel.
#define  PD_NORMAL                      0b0   // Normal operation
#define  PD_POWER_DOWN                  0b1   // Channel power-down 
                                              // When powering down a channel, TI recommends that the
                                              // channel be set to input short by setting the appropriate
                                              // MUXn[2:0] = 001 of the CHnSET register.
                                              // These bits determine the PGA gain setting.

// These bits determine the PGA gain setting.
#define  PGA_6                          0b000 // x6 
#define  PGA_1                          0b001 // x1
#define  PGA_2                          0b010 // x2
#define  PGA_3                          0b011 // x3
#define  PGA_4                          0b100 // x4
#define  PGA_8                          0b101 // x8
#define  PGA_12                         0b110 // x12

// These bits determine the channel input selection.
#define  MUX_NORMAL_ELEC_INPUT          0b000 // Normal electrode input
#define  MUX_INPUT_SHORTED              0b001 // Input shorted (for offset or noise measurements)
#define  MUX_USED_WITH_RLD_MEAS_bit     0b010 // Used in conjunction with RLD_MEAS bit for RLD
                                              // measurements. See the Right Leg Drive (RLD) DC Bias Circuit
                                              // subsection of the ECG-Specific Functions section for more
                                              // details.
#define  MUX_MVDD                       0b011 // MVDD for supply measurement
#define  MUX_TEMPERATURE_SENSOR         0b100 // Temperature sensor
#define  MUX_TEST_SIGNAL                0b101 // Test signal
#define  MUX_RLD_DRP                    0b110 // RLD_DRP (positive electrode is the driver)
#define  MUX_RLD_DRN                    0b111 // RLD_DRN (negative electrode is the driver)
//------------------------------------------------------------------------------

//-------- RLD_SENSP: RLD Positive Signal Derivation Register ------------------
typedef union RLDPositiveSignalDerivationRegister
{
  uint8_t Value;
  
  struct
  {
    _IOM uint8_t RLD1P:1;
    
    _IOM uint8_t RLD2P:1;
    
    _IOM uint8_t RLD3P:1;
    
    _IOM uint8_t RLD4P:1;
    
    _IOM uint8_t RLD5P:1;
    
    _IOM uint8_t RLD6P:1;
   
    _IOM uint8_t RLD7P:1;
    
    _IOM uint8_t RLD8P:1;
    
  } BIT;
  
} RLD_SENSP;
//------------------------------------------------------------------------------
// Route channel N positive signal into RLD channel
#define RLDP_DISABLE                    0b0 // Disable
#define RLDP_ENABLE                     0b1 // Enable
//------------------------------------------------------------------------------

//-------- RLD_SENSN: RLD Negative Signal Derivation Register ------------------
typedef union RLDNegativeSignalDerivationRegister
{
  uint8_t Value;
  
  struct
  {
    _IOM uint8_t RLD1N:1;
    
    _IOM uint8_t RLD2N:1;
    
    _IOM uint8_t RLD3N:1;
    
    _IOM uint8_t RLD4N:1;
    
    _IOM uint8_t RLD5N:1;
    
    _IOM uint8_t RLD6N:1;
   
    _IOM uint8_t RLD7N:1;
    
    _IOM uint8_t RLD8N:1;
    
  } BIT;
  
} RLD_SENSN;
//------------------------------------------------------------------------------
// Route channel N Negative signal into RLD channel
#define RLDN_DISABLE                    0b0 // Disable
#define RLDN_ENABLE                     0b1 // Enable
//------------------------------------------------------------------------------

//-------- LOFF_SENSP: Positive Signal Lead-Off Detection Register -------------
typedef union PositiveSignalLeadOffDetectionRegister
{
  uint8_t Value;
  
  struct
  {
    _IOM uint8_t LOFF1P:1;
    
    _IOM uint8_t LOFF2P:1;
    
    _IOM uint8_t LOFF3P:1;
    
    _IOM uint8_t LOFF4P:1;
    
    _IOM uint8_t LOFF5P:1;
    
    _IOM uint8_t LOFF6P:1;
   
    _IOM uint8_t LOFF7P:1;
    
    _IOM uint8_t LOFF8P:1;
    
  } BIT;
  
} LOFF_SENSP;
//------------------------------------------------------------------------------
// Enable lead-off detection on INxP
#define LOFFP_DISABLE                    0b0 // Disable
#define LOFFP_ENABLE                     0b1 // Enable
//------------------------------------------------------------------------------

//-------- LOFF_SENSN: Negative Signal Lead-Off Detection Register -------------
typedef union NegativeSignalLeadOffDetectionRegister
{
  uint8_t Value;
  
  struct
  {
    _IOM uint8_t LOFF1N:1;
    
    _IOM uint8_t LOFF2N:1;
    
    _IOM uint8_t LOFF3N:1;
    
    _IOM uint8_t LOFF4N:1;
    
    _IOM uint8_t LOFF5N:1;
    
    _IOM uint8_t LOFF6N:1;
   
    _IOM uint8_t LOFF7N:1;
    
    _IOM uint8_t LOFF8N:1;
    
  } BIT;
  
} LOFF_SENSN;
//------------------------------------------------------------------------------
// Enable lead-off detection on INxP
#define LOFFN_DISABLE                    0b0 // Disable
#define LOFFN_ENABLE                     0b1 // Enable
//------------------------------------------------------------------------------

#endif