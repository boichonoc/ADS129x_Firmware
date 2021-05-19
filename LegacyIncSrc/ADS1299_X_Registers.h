#ifndef ADS1299_X_Registers
#define ADS1299_X_Registers

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
    __IM uint8_t NU_CH:2;
    
    __IM uint8_t DEV_ID:2;
    
    __IM uint8_t _reserved:1;
    
    __IM uint8_t REV_ID:3;
    
  } BIT;

}ID;

//------------------------------------------------------------------------------
#define ADS1299_8               0b11110 // 8-channel ADS1299
#define ADS1299_6               0b11101 // 6-channel ADS1299
#define ADS1299_6               0b11100 // 4-channel ADS1299

//------------------------------------------------------------------------------

//-------- CONFIG 1 ------------------------------------------------------------
typedef union FirstConfigurationRegister
{
  uint8_t Value;
  
  struct 
  {
    __IOM uint8_t DR:3;
    
    __IM  uint8_t _reserved0:2;
    
    __IOM uint8_t CLK_EN:1;
    
    __IOM uint8_t DAISY_EN:1;
    
    __IM  uint8_t _reserved1:1;
    
  } BIT;
  
} CONFIG1;
//------------------------------------------------------------------------------
//This bit determines which mode is enable
#define DEISY_CHAIN                     0b0   // Daisy-chain mode
#define MULT_READBACK                   0b1   // Multiple readback mode

//This bit determines if the internal oscilator signal is connedted to the CLK pin when CLKSEL_pin = 1.
#define OSC_OUT_DISABLE                 0b0   // OSC output disabled
#define OSC_OUT_ENABLE                  0b1   // OSC output enabled

//This bit determine the output data rate of the device 
#define SPS_16K                         0b000 // Mode: 16kSPS
#define SPS_8K                          0b000 // Mode: 8kSPS
#define SPS_4K                          0b010 // Mode: 4kSPS
#define SPS_2K                          0b011 // Mode: 2kSPS
#define SPS_1K                          0b100 // Mode: 1kSPS
#define SPS_500                         0b101 // Mode: 500SPS
#define SPS_250                         0b110 // Mode: 250SPS

//------------------------------------------------------------------------------
//-------- CONFIG 2 ------------------------------------------------------------
typedef union SecondConfigurationRegister
{
  uint8_t Value;
    
  struct
  {
    __IOM uint8_t CAL_FREQ:2;
    
    __IOM uint8_t CAL_AMP:1;
    
    __IM  uint8_t _reserved0:1;
    
    __IOM uint8_t INT_CAL:1;
        
    __IM  uint8_t _reserved1:3;
    
  } BIT;
    
} CONFIG2;

//This bit determines the source for the test signal.
#define CAL_SOURCE_SIGNAL_EXT           0b0 //Test signals are driven externally
#define CAL_SOURCE_SIGNAL_INT           0b1 //Test signals are generated internally

//These bits determine the calibration signal amplitude.
#define CAL_SIGNAL_AMP_1                0b0 // 1 x –(VREFP – VREFN) / 2400 V
#define CAL_SIGNAL_AMP_2                0b1 // 2 x –(VREFP – VREFN) / 2400 V

//These bits determine the calibration signal frequency
#define CAL_SIGNAL_FREQ_21              0b00 // Pulsed at fCLK / 2^21
#define CAL_SIGNAL_FREQ_20              0b01 // Pulsed at fCLK / 2^20
#define CAL_SIGNAL_FREQ_NOT_USE         0b10 // Not used
#define CAL_SIGNAL_FREQ_AT_DC           0b11 // At dc

//------------------------------------------------------------------------------
//-------- CONFIG 3 ------------------------------------------------------------
typedef union ThirdConfigurationRegister
{
  uint8_t Value;
    
  struct
  {
    __IM  uint8_t BIAS_STAT:1;
    
    __IOM uint8_t BIAS_LOFF_SENS:1;
    
    __IOM uint8_t PD_BIAS:1;
    
    __IOM uint8_t BIASREF_INT:1;
    
    __IOM uint8_t BIAS_MEAS:1;
    
    __IM  uint8_t _reserved:2;
    
    __IOM uint8_t PD_REFBUF:1;
  
  } BIT;
  
} CONFIG3;

//This bit determines the power-down reference buffer state.
#define REF_BUFF_DESABLE                0b0 //Power-down internal reference buffer
#define REF_BUFF_ENABLE                 0b1 //Enable internal reference buffer

//This bit enables RLD measurement. The RLD signal may be measured with any channel.
#define BIAS_OPEN                       0b0 //Open
#define BIAS_IN                         0b1 //RLD_IN signal is routed to the channel that has the MUX_Setting 010 (VREF)

//This bit determines the RLDREF signal source.
#define BIAS_REF_SIGNAL_EXT             0b0 //BIAS REF signal fed externally
#define BIAS_REF_SIGNAL_INT             0b1 //BIAS REF signal (AVDD – AVSS) / 2 generated internally

//This bit determines the BIAS buffer power state.
#define BIAS_BUF_DISABLE                0b0 //BIAS buffer is powered down
#define BIAS_BUF_ENABLE                 0b1 //BIAS buffer is enabled

//This bit enables the RLD(BIAS) sense function.
#define BIAS_LOFF_SENS_DISABLE          0b0 //RLD(BIAS) sense is disabled
#define BIAS_LOFF_SENS_ENABLE           0b1 //RLD(BIAS) sense is enabled

//------------------------------------------------------------------------------
//-------- LEAD-OFF Control ----------------------------------------------------

typedef union LeadOffControlRegister
{
  uint8_t Value;
  
  struct
  {
    __IOM uint8_t FLEAD_OFF:2;
    
    __IOM uint8_t ILEAD_OFF:2;
        
    __IO  uint8_t _reserved:1;
    
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

// These bits determine the magnitude of current for the current lead-off mode.
#define I_LEAD_OFF_6nA                  0b00 // 6 nA
#define I_LEAD_OFF_24nA                 0b01 // 24 nA
#define I_LEAD_OFF_6uA                  0b10 // 6  uA
#define I_LEAD_OFF_24uA                 0b11 // 24 uA

// These bits determine the frequency of lead-off detect for each channel.
#define F_LEAD_OFF                      0b00 // DC lead-off detection
#define F_LEAD_OFF_AC                   0b01 // AC lead-off detection at 7.8 Hz (fCLK / 2^18)
#define F_LEAD_OFF_NOT_USE              0b10 // AC lead-off detection at 31.2 Hz (fCLK / 2^16)
#define F_LEAD_OFF_DC                   0b11 // AC lead-off detection at fDR / 4

//------------------------------------------------------------------------------

//-------- CH_N_SET_CONFIGS ----------------------------------------------------
typedef union IndividualChannelSettingsRegister
{
  uint8_t Value;
  
  struct
  {
    _IOM uint8_t MUX:2;
    
    _I0M uint8_t SRB2:1;
    
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
#define  PGA_1                          0b000 // x1
#define  PGA_2                          0b001 // x2
#define  PGA_4                          0b010 // x4
#define  PGA_6                          0b011 // x6
#define  PGA_8                          0b100 // x8
#define  PGA_12                         0b101 // x12
#define  PGA_24                         0b110 // x24

//This bit determines the SRB2 connection for the corresponding channel
#define  SRB2_OPEN                      0b0   // Open
#define  SRB2_CLOSE                     0b1   // Close

// These bits determine the channel input selection.
#define  MUX_NORMAL_ELEC_INPUT          0b000 // Normal electrode input
#define  MUX_INPUT_SHORTED              0b001 // Input shorted (for offset or noise measurements)
#define  MUX_USED_WITH_BIAS_MEAS_bit    0b010 // Used in conjunction with BIAS_MEAS bit for BIAS
                                              // measurements.
#define  MUX_MVDD                       0b011 // MVDD for supply measurement
#define  MUX_TEMPERATURE_SENSOR         0b100 // Temperature sensor
#define  MUX_TEST_SIGNAL                0b101 // Test signal
#define  MUX_BIAS_DRP                   0b110 // BIAS_DRP (positive electrode is the driver)
#define  MUX_BIAS_DRN                   0b111 // BIAS_DRN (negative electrode is the driver)
//------------------------------------------------------------------------------

//-------- BIAS_SENSP: BIAS Positive Signal Derivation Register ------------------
typedef union BIASPositiveSignalDerivationRegister
{
  uint8_t Value;
  
  struct
  {
    _IOM uint8_t BIAS1P:1;
    
    _IOM uint8_t BIAS2P:1;
    
    _IOM uint8_t BIAS3P:1;
    
    _IOM uint8_t BIAS4P:1;
    
    _IOM uint8_t BIAS5P:1;
    
    _IOM uint8_t BIAS6P:1;
   
    _IOM uint8_t BIAS7P:1;
    
    _IOM uint8_t BIAS8P:1;
    
  } BIT;
  
} BIAS_SENSP;
//------------------------------------------------------------------------------
// Route channel N positive signal into BIAS channel
#define BIASP_DISABLE                    0b0 // Disable
#define BIASP_ENABLE                     0b1 // Enable
//------------------------------------------------------------------------------

//-------- BIAS_SENSN: BIAS Negative Signal Derivation Register ------------------
typedef union BIASNegativeSignalDerivationRegister
{
  uint8_t Value;
  
  struct
  {
    _IOM uint8_t BIAS1N:1;
    
    _IOM uint8_t BIAS2N:1;
    
    _IOM uint8_t BIAS3N:1;
    
    _IOM uint8_t BIAS4N:1;
    
    _IOM uint8_t BIAS5N:1;
    
    _IOM uint8_t BIAS6N:1;
   
    _IOM uint8_t BIAS7N:1;
    
    _IOM uint8_t BIAS8N:1;
    
  } BIT;
  
} BIAS_SENSN;
//------------------------------------------------------------------------------
// Route channel N Negative signal into BIAS channel
#define BIASN_DISABLE                    0b0 // Disable
#define BIASN_ENABLE                     0b1 // Enable
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