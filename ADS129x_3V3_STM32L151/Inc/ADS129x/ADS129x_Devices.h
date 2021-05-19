#ifndef __ADS129x_DEVICES_H
#define __ADS129x_DEVICES_H

//Opcode Command Definitions
#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stm32l1xx_hal.h"

//Regisres *********************************************************************
#define ADS129x
//-------- ID Register ---------------------------------------------------------
public typedef struct
{
  
  uint8_t ADDR;
  
  union
  {
    
    __IOM uint8_t BYTE;
    
    struct
    {
      
#ifdef ADS129x    
      
      __IM uint8_t NU_CH:3;
      
      __IM uint8_t _reserved:2;
      
      __IM uint8_t REV_ID:3;
      
#else
      __IM uint8_t NU_CH:2;
      
      __IM uint8_t DEV_ID:2;
      
      __IM uint8_t _reserved:1;
      
      __IM uint8_t REV_ID:3;
      
#endif    
      
    } BITS;
    
  };
  
  uint8_t (*GetID) (SPI_HandleTypeDef * hspi1, uint8_t  address);

} ID_Type;

//------------------------------------------------------------------------------
#ifdef ADS129x   

  #define ADS1294                 0x90 // 4-channel ADS129x
  #define ADS1296                 0x91 // 6-channel ADS129x
  #define ADS1298                 0x92 // 8-channel ADS129x

  #define ADS1294R                0xD0 // 4-channel ADS129xR
  #define ADS1296R                0xD1 // 6-channel ADS129xR
  #define ADS1298R                0xD2 // 8-channel ADS129xR

#else

  #define ADS1299_8               0x2 // 8-channel ADS1299
  #define ADS1299_6               0x1 // 6-channel ADS1299
  #define ADS1299_4               0x0 // 4-channel ADS1299

#endif
//------------------------------------------------------------------------------

//-------- CONFIG 1 ------------------------------------------------------------
public typedef struct
{
  
  uint8_t ADDR;
  
  union
  {
    
    uint8_t BYTE;
    
    struct
    {
      
#ifdef ADS129x    
      
      __IOM uint8_t DR:3;
      
      __IM  uint8_t _reserved:2;
      
      __IOM uint8_t CLK_EN:1;
      
      __IOM uint8_t DAISY_EN:1;
      
      __IOM uint8_t HR:1;
      
#else
      
      __IOM uint8_t DR:3;
      
      __IM  uint8_t _reserved0:2;
      
      __IOM uint8_t CLK_EN:1;
      
      __IOM uint8_t DAISY_EN:1;
      
      __IM  uint8_t _reserved1:1;
      
#endif    
      
    } BITS;
      
  };

  uint8_t (*GetCONFIG1)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetCONFIG1)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} CONFIG1_Type;

//------------------------------------------------------------------------------
#ifdef ADS129x

  //This bit determines whether the device runs
  #define LPM                                   0x0 // in low-power  
  #define HRM                                   0x1 // or high-resolution mode

  //This bit determine the output data rate of the device
  #define SPS_32K_HR_16K_LP                     0x0 // HR Mode: 32kSPS, LP Mode: 16kSPS
  #define SPS_16K_HR_8K_LP                      0x1 // HR Mode: 16kSPS, LP Mode: 8kSPS
  #define SPS_8K_HR_4K_LP                       0x2 // HR Mode: 8kSPS, LP Mode: 4kSPS
  #define SPS_4K_HR_2K_LP                       0x3 // HR Mode: 4kSPS, LP Mode: 2kSPS
  #define SPS_2K_HR_1K_LP                       0x4 // HR Mode: 2kSPS, LP Mode: 1kSPS
  #define SPS_1K_HR_500_LP                      0x5 // HR Mode: 1kSPS, LP Mode: 500SPS
  #define SPS_500_HR_250_LP                     0x6 // HR Mode: 500SPS, LP Mode: 250SPS

#else
  
  //This bit determine the output data rate of the device 
  #define SPS_16K                               0x0 // Mode: 16kSPS
  #define SPS_8K                                0x1 // Mode: 8kSPS
  #define SPS_4K                                0x2 // Mode: 4kSPS
  #define SPS_2K                                0x3 // Mode: 2kSPS
  #define SPS_1K                                0x4 // Mode: 1kSPS
  #define SPS_500                               0x5 // Mode: 500SPS
  #define SPS_250                               0x6 // Mode: 250SPS

#endif

//This bit determines which mode is enable
#define DEISY_CHAIN                             0x0 // Daisy-chain mode
#define MULT_READBACK                           0x1 // Multiple readback mode

//This bit determines if the internal oscilator signal is connedted to the CLK pin when CLKSEL_pin = 1.
#define OSC_OUT_DISABLE                         0x0  // OSC output disabled
#define OSC_OUT_ENABLE                          0x1  // OSC output enabled
//------------------------------------------------------------------------------

//-------- CONFIG 2 ------------------------------------------------------------
public typedef struct
{
  
  uint8_t ADDR;
  
  union 
  {
    
    uint8_t BYTE;
    
    struct
    {
      
#ifdef ADS129x
      
      __IOM uint8_t TEST_FREQ:2;
      
      __IOM uint8_t TEST_AMP:1;
      
      __IM  uint8_t _reserved0:1;
      
      __IOM uint8_t INT_TEST:1;
      
      __IOM uint8_t WCT_CHOP:1;
      
      __IM  uint8_t _reserved1:2;
      
#else
      
      __IOM uint8_t CAL_FREQ:2;
      
      __IOM uint8_t CAL_AMP:1;
      
      __IM  uint8_t _reserved0:1;
      
      __IOM uint8_t INT_CAL:1;
      
      __IM  uint8_t _reserved1:3;
      
#endif    
      
    } BITS;
        
  };

  uint8_t (*GetCONFIG2)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetCONFIG2)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} CONFIG2_Type;

//------------------------------------------------------------------------------
#ifdef ADS129x

  //This bit determines whether the chopping frequency of WCT amplifiers is variable or fixed
  #define FR_VARIES           0x0 //Chopping frequency varies, see Table 7 (in datasheet)
  #define FR_CONST            0x1 //Chopping frequency constant at fMOD / 16

#endif

//This bit determines the source for the test signal.
#define SOURCE_SIGNAL_EXT   0x0 //Test signals are driven externally
#define SOURCE_SIGNAL_INT   0x1 //Test signals are generated internally

//These bits determine the calibration signal amplitude.
#define SIGNAL_AMP_1        0x0 // 1 x �(VREFP � VREFN) / 2400 V
#define SIGNAL_AMP_2        0x1 // 2 x �(VREFP � VREFN) / 2400 V

//These bits determine the calibration signal frequency
#define SIGNAL_FREQ_21      0x0 // Pulsed at fCLK / 2^21
#define SIGNAL_FREQ_20      0x1 // Pulsed at fCLK / 2^20
#define SIGNAL_FREQ_NOT_USE 0x2 // Not used
#define SIGNAL_FREQ_AT_DC   0x3 // At dc
//------------------------------------------------------------------------------

//-------- CONFIG 3 ------------------------------------------------------------
public typedef struct
{
  
  uint8_t ADDR;
  
  union 
  {
    
    uint8_t BYTE;
    
    struct
    {
      
#ifdef ADS129x
      
      __IM  uint8_t RLD_STAT:1;
      
      __IOM uint8_t RLD_LOFF_SENS:1;
      
      __IOM uint8_t PD_RLD:1;
      
      __IOM uint8_t RLDREF_INT:1;
      
      __IOM uint8_t RLD_MEAS:1;
      
      __IOM uint8_t VREF:1;
      
      __IM  uint8_t _reserved:1;
      
      __IOM uint8_t PD_REFBUF:1;
      
#else
      
      __IM  uint8_t BIAS_STAT:1;
      
      __IOM uint8_t BIAS_LOFF_SENS:1;
      
      __IOM uint8_t PD_BIAS:1;
      
      __IOM uint8_t BIASREF_INT:1;
      
      __IOM uint8_t BIAS_MEAS:1;
      
      __IM  uint8_t _reserved:2;
      
      __IOM uint8_t PD_REFBUF:1;
      
#endif    
      
    } BITS;
       
  };

  uint8_t (*GetCONFIG3)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetCONFIG3)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} CONFIG3_Type;
//------------------------------------------------------------------------------
//This bit determines the power-down reference buffer state.
#define REF_BUFF_DESABLE                0x0 //Power-down internal reference buffer
#define REF_BUFF_ENABLE                 0x1 //Enable internal reference buffer

//This bit determines the reference voltage, VREFP
#define VREF_2V4                        0x0  //VREFP is set to 2.4 V
#define VREF_4V                         0x1  //VREFP is set to 4 V (use only with a 5-V analog supply)

//This bit enables RLD(BIAS) measurement. The RLD(BIAS) signal may be measured with any channel.
#define OPEN                            0x0 //Open
#define CLOSE                           0x1 //RLD(BIAS)_IN signal is routed to the channel that has the MUX_Setting 010 (VREF)

//This bit determines the RLD(BIAS)REF signal source.
#define REF_SIGNAL_EXT                  0x0 //RLD(BIAS)REF signal fed externally
#define REF_SIGNAL_INT                  0x1 //RLD(BIAS)REF signal (AVDD � AVSS) / 2 generated internally

//This bit determines the RLD(BIAS) buffer power state.
#define BUF_DISABLE                     0x0 //RLD(BIAS) buffer is powered down
#define BUF_ENABLE                      0x1 //RLD(BIAS) buffer is enabled

//This bit enables the RLD(BIAS) sense function.
#define LOFF_SENS_DISABLE               0x0 //RLD(BIAS) sense is disabled
#define LOFF_SENS_ENABLE                0x1 //RLD(BIAS) sense is enabled

//------------------------------------------------------------------------------
//-------- LEAD-OFF Control ----------------------------------------------------
public typedef struct 
{
  
  uint8_t ADDR;
  
  union 
  {
    
    uint8_t BYTE;
    
    struct
    {
      __IOM uint8_t FLEAD_OFF:2;
      
      __IOM uint8_t ILEAD_OFF:2;
      
#ifdef ADS129x    
      
      __IOM uint8_t VLEAD_OFF_EN:1;
      
#else
      
      __IO  uint8_t _reserved:1;
      
#endif    
      
      __IOM uint8_t COMP_TH:3;
      
    } BITS;
    
  };
  
  uint8_t (*GetLOFF)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetLOFF)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} LOFF_Type;
//------------------------------------------------------------------------------
// Lead-off comparator threshold
#define COMP_TH_95_5                    0x0 // Comparator positive side: 95 Comparator negative side: 5
#define COMP_TH_92_75                   0x1 // Comparator positive side: 92.5 Comparator negative side: 7.5
#define COMP_TH_90_10                   0x2 // Comparator positive side: 90 Comparator negative side: 10
#define COMP_TH_87_12                   0x3 // Comparator positive side: 87.5 Comparator negative side: 12.5
#define COMP_TH_85_15                   0x4 // Comparator positive side: 85 Comparator negative side: 15
#define COMP_TH_80_20                   0x5 // Comparator positive side: 80 Comparator negative side: 20
#define COMP_TH_75_25                   0x6 // Comparator positive side: 75 Comparator negative side: 25
#define COMP_TH_70_30                   0x7 // Comparator positive side: 70 Comparator negative side: 30

#ifdef ADS129x

  // This bit determines the lead-off detection mode.
  #define VLEAD_OFF_EN_CS                 0x0   //Current source mode lead-off
  #define VLEAD_OFF_EN_Pull_UP_DWN        0x1   //pullup or pulldown resistor mode lead-off

  // These bits determine the magnitude of current for the current lead-off mode.
  #define I_LEAD_OFF_6nA                  0x0 // 6 nA
  #define I_LEAD_OFF_12nA                 0x1 // 12 nA
  #define I_LEAD_OFF_18nA                 0x2 // 18 nA
  #define I_LEAD_OFF_24nA                 0x3 // 24 nA

#else

  // These bits determine the magnitude of current for the current lead-off mode.
  #define I_LEAD_OFF_6nA                  0x0 // 6 nA
  #define I_LEAD_OFF_24nA                 0x1 // 24 nA
  #define I_LEAD_OFF_6uA                  0x2 // 6  uA
  #define I_LEAD_OFF_24uA                 0x3 // 24 uA

#endif
// TODO :: Create #ifdef construction for ADS1298 device
// These bits determine the frequency of lead-off detect for each channel.
#define F_LEAD_OFF                      0x0 // When any bits of the LOFF_SENSP or LOFF_SENSN registers are turned on, make sure that FLEAD[1:0] are either set to 01 or 11
#define F_LEAD_OFF_AC                   0x1 // AC lead-off detection at fDR / 4
#define F_LEAD_OFF_NOT_USE              0x2 // Do not use
#define F_LEAD_OFF_DC                   0x3 // DC lead-off detection turned on

//------------------------------------------------------------------------------

//-------- CH_N_SET_CONFIGS ----------------------------------------------------
public typedef struct 
{
  
  uint8_t ADDR;
  
  union
  {
    
    uint8_t BYTE;
    
    struct
    {
      __IOM uint8_t MUX:3;
      
#ifdef ADS129x    
      
      __IM  uint8_t _reserved:1;
      
#else
      
      __IOM uint8_t SRB2:1;
      
#endif    
      
      __IOM uint8_t GAIN:3;
      
      __IOM uint8_t PD;
      
    } BITS;
    
  };
  
  uint8_t (*GetCHnSET)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetCHnSET)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} CHnSET_Type;
//------------------------------------------------------------------------------
// This bit determines the channel power mode for the corresponding channel.
#define  PD_NORMAL                      0x0   // Normal operation
#define  PD_POWER_DOWN                  0x1   // Channel power-down 
                                              // When powering down a channel, TI recommends that the
                                              // channel be set to input short by setting the appropriate
                                              // MUXn[2:0] = 001 of the CHnSET register.
                                              // These bits determine the PGA gain setting.
#ifdef ADS129x

  // These bits determine the PGA gain setting.
  #define  PGA_6                          0x0 // x6 
  #define  PGA_1                          0x1 // x1
  #define  PGA_2                          0x2 // x2
  #define  PGA_3                          0x3 // x3
  #define  PGA_4                          0x4 // x4
  #define  PGA_8                          0x5 // x8
  #define  PGA_12                         0x6 // x12

#else

  // These bits determine the PGA gain setting.
  #define  PGA_1                          0x0 // x1
  #define  PGA_2                          0x1 // x2
  #define  PGA_4                          0x2 // x4
  #define  PGA_6                          0x3 // x6
  #define  PGA_8                          0x4 // x8
  #define  PGA_12                         0x5 // x12
  #define  PGA_24                         0x6 // x24

  //This bit determines the SRB2 connection for the corresponding channel
  #define  SRB2_OPEN                      0x0   // Open
  #define  SRB2_CLOSE                     0x1   // Close

#endif

// These bits determine the channel input selection.
#define  MUX_NORMAL_ELEC_INPUT           0x0 // Normal electrode input
#define  MUX_INPUT_SHORTED               0x1 // Input shorted (for offset or noise measurements)

#ifdef ADS129x

  #define  MUX_USED_WITH_RLD_MEAS_bit     0x2 // Used in conjunction with RLD_MEAS bit for RLD
                                                // measurements. See the Right Leg Drive (RLD) DC Bias Circuit
                                                // subsection of the ECG-Specific Functions section for more
                                                // details.

#else

  #define  MUX_USED_WITH_BIAS_MEAS_bit    0x2 // Used in conjunction with BIAS_MEAS bit for BIAS
                                                // measurements.

#endif

#define  MUX_MVDD                       0x3 // MVDD for supply measurement
#define  MUX_TEMPERATURE_SENSOR         0x4 // Temperature sensor
#define  MUX_TEST_SIGNAL                0x5 // Test signal

#ifdef ADS129x

  #define  MUX_RLD_DRP                    0x6 // RLD_DRP (positive electrode is the driver)
  #define  MUX_RLD_DRN                    0x7 // RLD_DRN (negative electrode is the driver)

#else

  #define  MUX_BIAS_DRP                   0x6 // BIAS_DRP (positive electrode is the driver)
  #define  MUX_BIAS_DRN                   0x7 // BIAS_DRN (negative electrode is the driver)

#endif
//------------------------------------------------------------------------------

//-------- RLD_SENSP: RLD Positive Signal Derivation Register ------------------
struct SENSP_Type
{
  
  uint8_t ADDR;
  
  union 
  {
    
    uint8_t BYTE;
    
    struct
    {
#ifdef ADS129x
      
      __IOM uint8_t RLD1P:1;
      
      __IOM uint8_t RLD2P:1;
      
      __IOM uint8_t RLD3P:1;
      
      __IOM uint8_t RLD4P:1;
      
      __IOM uint8_t RLD5P:1;
      
      __IOM uint8_t RLD6P:1;
      
      __IOM uint8_t RLD7P:1;
      
      __IOM uint8_t RLD8P:1;
      
#else
      
      __IOM uint8_t BIAS1P:1;
      
      __IOM uint8_t BIAS2P:1;
      
      __IOM uint8_t BIAS3P:1;
      
      __IOM uint8_t BIAS4P:1;
      
      __IOM uint8_t BIAS5P:1;
      
      __IOM uint8_t BIAS6P:1;
      
      __IOM uint8_t BIAS7P:1;
      
      __IOM uint8_t BIAS8P:1;
      
#endif    
      
    } BITS;
    
  };

#ifdef ADS129x  
  
  uint8_t (*GetRLD_SENSP)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetRLD_SENSP)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
#else

  uint8_t (*GetBIAS_SENSP)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetBIAS_SENSP)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
#endif
  
};

#ifdef ADS129x

    public typedef struct SENSP_Type RLD_SENSP_Type;
  
#else

    public typedef struct SENSP_Type BIAS_SENSP_Type;
    
#endif    
  
//------------------------------------------------------------------------------
#ifdef ADS129x

  // Route channel N positive signal into RLD channel
  #define RLDP_DISABLE                    0b0 // Disable
  #define RLDP_ENABLE                     0b1 // Enable

#else

  // Route channel N positive signal into BIAS channel
  #define BIASP_DISABLE                    0b0 // Disable
  #define BIASP_ENABLE                     0b1 // Enable

#endif
//------------------------------------------------------------------------------

//-------- RLD_SENSN: RLD Negative Signal Derivation Register ------------------
struct SENSN_Type 
{
  
  uint8_t ADDR;
  
  union
  {
    
    uint8_t BYTE;
    
    struct
    {
#ifdef ADS129x
      
      __IOM uint8_t RLD1N:1;
      
      __IOM uint8_t RLD2N:1;
      
      __IOM uint8_t RLD3N:1;
      
      __IOM uint8_t RLD4N:1;
      
      __IOM uint8_t RLD5N:1;
      
      __IOM uint8_t RLD6N:1;
      
      __IOM uint8_t RLD7N:1;
      
      __IOM uint8_t RLD8N:1;
      
#else
      
      __IOM uint8_t BIAS1N:1;
      
      __IOM uint8_t BIAS2N:1;
      
      __IOM uint8_t BIAS3N:1;
      
      __IOM uint8_t BIAS4N:1;
      
      __IOM uint8_t BIAS5N:1;
      
      __IOM uint8_t BIAS6N:1;
      
      __IOM uint8_t BIAS7N:1;
      
      __IOM uint8_t BIAS8N:1;
      
#endif    
      
    } BITS;
    
  };
  
#ifdef ADS129x  
  
  uint8_t (*GetRLD_SENSN)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetRLD_SENSN)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
#else

  uint8_t (*GetBIAS_SENSN)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetBIAS_SENSN)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
#endif
  
};

#ifdef ADS129x

   public typedef struct SENSN_Type RLD_SENSN_Type;
  
#else

   public typedef struct SENSN_Type BIAS_SENSN_Type;
    
#endif 
    
//------------------------------------------------------------------------------
#ifdef ADS129x

  // Route channel N Negative signal into RLD channel
  #define RLDN_DISABLE                    0b0 // Disable
  #define RLDN_ENABLE                     0b1 // Enable

#else

  // Route channel N Negative signal into BIAS channel
  #define BIASN_DISABLE                   0b0 // Disable
  #define BIASN_ENABLE                    0b1 // Enable

#endif
//------------------------------------------------------------------------------

//-------- LOFF_SENSP: Positive Signal Lead-Off Detection Register -------------
public typedef struct
{
  
  uint8_t ADDR;
  
  union 
  {
    
    uint8_t BYTE;
    
    struct
    {
      __IOM uint8_t LOFF1P:1;
      
      __IOM uint8_t LOFF2P:1;
      
      __IOM uint8_t LOFF3P:1;
      
      __IOM uint8_t LOFF4P:1;
      
      __IOM uint8_t LOFF5P:1;
      
      __IOM uint8_t LOFF6P:1;
      
      __IOM uint8_t LOFF7P:1;
      
      __IOM uint8_t LOFF8P:1;
      
    } BITS;
    
  };
  
  uint8_t (*GetLOFF_SENSP)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetLOFF_SENSP)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} LOFF_SENSP_Type;
//------------------------------------------------------------------------------
// Enable lead-off detection on INxP
#define LOFFP_DISABLE                    0b0 // Disable
#define LOFFP_ENABLE                     0b1 // Enable
//------------------------------------------------------------------------------

//-------- LOFF_SENSN: Negative Signal Lead-Off Detection Register -------------
public typedef struct 
{
  
  uint8_t ADDR;
  
  union 
  {
    
    uint8_t BYTE;
    
    struct
    {
      __IOM uint8_t LOFF1N:1;
      
      __IOM uint8_t LOFF2N:1;
      
      __IOM uint8_t LOFF3N:1;
      
      __IOM uint8_t LOFF4N:1;
      
      __IOM uint8_t LOFF5N:1;
      
      __IOM uint8_t LOFF6N:1;
      
      __IOM uint8_t LOFF7N:1;
      
      __IOM uint8_t LOFF8N:1;
      
    } BITS;
    
  };
  
  uint8_t (*GetLOFF_SENSN)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetLOFF_SENSN)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} LOFF_SENSN_Type;
//------------------------------------------------------------------------------
// Enable lead-off detection on INxP
#define LOFFN_DISABLE                    0b0 // Disable
#define LOFFN_ENABLE                     0b1 // Enable
//------------------------------------------------------------------------------

//-------- LOFF_FLIP: Lead-Off Flip Register -----------------------------------
public typedef struct 
{
  
  uint8_t ADDR;
  
  union
  {
    
    uint8_t BYTE;
    
    struct
    {
      __IOM uint8_t LOFF_FLIP1:1;
      
      __IOM uint8_t LOFF_FLIP2:1;
      
      __IOM uint8_t LOFF_FLIP3:1;
      
      __IOM uint8_t LOFF_FLIP4:1;
      
      __IOM uint8_t LOFF_FLIP5:1;
      
      __IOM uint8_t LOFF_FLIP6:1;
      
      __IOM uint8_t LOFF_FLIP7:1;
      
      __IOM uint8_t LOFF_FLIP8:1;
      
    } BITS;
    
  };
  
  uint8_t (*GetLOFF_FLIP)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetLOFF_FLIP)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} LOFF_FLIP_Type;
//------------------------------------------------------------------------------
//Flip the pull-up or pull-down polarity of the current source on channel 8 for lead-off detection
#define NO_FLIP                          0b0 // No flip = INxP is pulled to AVDD and INxN pulled to AVSS
#define FLIPPED                          0b1 // Flipped = INxP is pulled to AVSS and INxN pulled to AVDD
//------------------------------------------------------------------------------


//----- LOFF_STATP: Lead-Off Positive Signal Status Register (Read-Only) -------
public typedef struct 
{
  
  uint8_t ADDR;
  
  union
  {
    
    uint8_t BYTE;
    
    struct
    {
      __IM uint8_t IN1P_OFF:1;
      
      __IM uint8_t IN2P_OFF:1;
      
      __IM uint8_t IN3P_OFF:1;
      
      __IM uint8_t IN4P_OFF:1;
      
      __IM uint8_t IN5P_OFF:1;
      
      __IM uint8_t IN6P_OFF:1;
      
      __IM uint8_t IN7P_OFF:1;
      
      __IM uint8_t IN8P_OFF:1;
      
    } BITS;
    
  };
  
  uint8_t (*GetLOFF_STATP)(SPI_HandleTypeDef * hspi1, uint8_t address);
  
} LOFF_STATP_Type;
//------------------------------------------------------------------------------

// Status of whether INxP electrode is on or off
#define P_ELECTRODE_IS_ON             0b0 // Electrode is on
#define P_ELECTRODE_IS_OFF            0b1 // Electrode is off
//------------------------------------------------------------------------------

//----- LOFF_STATN: Lead-Off Negative Signal Status Register (Read-Only) -------
public typedef struct
{
  
  uint8_t ADDR;
  
  union
  {
    
    uint8_t BYTE;
    
    struct
    {
      __IM uint8_t IN1N_OFF:1;
      
      __IM uint8_t IN2N_OFF:1;
      
      __IM uint8_t IN3N_OFF:1;
      
      __IM uint8_t IN4N_OFF:1;
      
      __IM uint8_t IN5N_OFF:1;
      
      __IM uint8_t IN6N_OFF:1;
      
      __IM uint8_t IN7N_OFF:1;
      
      __IM uint8_t IN8N_OFF:1;
      
    } BITS;
    
  };
  
  uint8_t (*GetLOFF_STATN)(SPI_HandleTypeDef * hspi1, uint8_t address);
  
} LOFF_STATN_Type;
//------------------------------------------------------------------------------

// Status of whether INxN electrode is on or off
#define N_ELECTRODE_IS_ON             0b0 // Electrode is on
#define N_ELECTRODE_IS_OFF            0b1 // Electrode is off
//------------------------------------------------------------------------------

//--------------- GPIO: General-Purpose I/O Register ---------------------------
public typedef struct 
{
  
  uint8_t ADDR;
  
  union
  {
    
    uint8_t BYTE;
    
    struct
    {
      __IOM uint8_t GPIOC1:1;
      
      __IOM uint8_t GPIOC2:1;
      
      __IOM uint8_t GPIOC3:1;
      
      __IOM uint8_t GPIOC4:1;
      
      __IOM uint8_t GPIOD1:1;
      
      __IOM uint8_t GPIOD2:1;
      
      __IOM uint8_t GPIOD3:1;
      
      __IOM uint8_t GPIOD4:1;
      
    } BITS;
    
  };
  
  uint8_t (*GetGPIO)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetGPIO)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} GPIO_Type;
//------------------------------------------------------------------------------

//These bits determine if the corresponding GPIOD pin is an input or output.
#define GPIO_OTPUT             0b0 // Output
#define GPIO_INPUT             0b1 // Input
//------------------------------------------------------------------------------

#ifdef ADS129x

//------------------- PACE: Pace Detect Register -------------------------------
public typedef struct 
{
  
  uint8_t ADDR;
  
  union
  {
    
    uint8_t BYTE;
    
    struct 
    {
      
      __IOM uint8_t PD_PACE:1;
      
      __IOM uint8_t PACEO:2;
      
      __IOM uint8_t PACEE:2;
      
      __IM  uint8_t _reserved:3;
      
    } BITS;
    
  };
  
  uint8_t (*GetPACE)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetPACE)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} PACE_Type;

//------------------------------------------------------------------------------
// This bit is used to enable/disable the pace detect buffer.
#define PD_BUFF_OFF                     0b0 // Pace detect buffer turned off
#define PD_BUFF_ON                      0b1 // Pace detect buffer turned on

// These bits control the selection of the odd number channels
// available on TEST_PACE_OUT2. Only one channel may be
// selected at any time.
#define PACE_CHN_1                      0b00 // Channel 1
#define PACE_CHN_3                      0b01 // Channel 3
#define PACE_CHN_5                      0b10 // Channel 5 (ADS1296, ADS1296R, ADS1298, ADS1298R)
#define PACE_CHN_7                      0b11 // Channel 7 (ADS1298, ADS1298R)

// These bits control the selection of the even number channels
// available on TEST_PACE_OUT1. Only one channel may be
// selected at any time
#define PACE_CHN_2                      0b00 // Channel 2
#define PACE_CHN_4                      0b01 // Channel 4
#define PACE_CHN_6                      0b10 // Channel 6 (ADS1296, ADS1296R, ADS1298, ADS1298R)
#define PACE_CHN_8                      0b11 // Channel 8 (ADS1298, ADS1298R)
//------------------------------------------------------------------------------

//------------------- RESP: Respiration Control Register -----------------------
public typedef struct 
{
  
  uint8_t ADDR;
  
  union 
  {
    
    uint8_t BYTE;
    
    struct
    {
      
      __IOM uint8_t RESP_CTRL:2;
      
      __IOM uint8_t RESP_PH:2;
      
      __IM  uint8_t _reserved:1;
      
      __IOM uint8_t RESP_MODE_EN1:1;
      
      __IOM uint8_t RESP_DEMODE_EN1:1;
      
    } BITS;
    
  };
  
  uint8_t (*GetRESP)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetRESP)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} RESP_Type;

//------------------------------------------------------------------------------
// Enables respiration demodulation circuitry (ADS129xR only; for ADS129x always write 0)
// This bit enables and disables the demodulation circuitry on channel 1.
#define RESP_DEMOD_ON                         0b0 // RESP demodulation circuitry turned off
#define RESP_DEMOD_OFF                        0b1 // RESP demodulation circuitry turned on

// RESP_MOD_EN1: Enables respiration modulation circuitry (ADS129xR only; for ADS129x always write 0)
// This bit enables and disables the modulation circuitry on channel 1.
#define RESP_MOD_ON                           0b0 // RESP modulation circuitry turned off
#define RESP_MOD_OFF                          0b1 // RESP modulation circuitry turned on

// Respiration phase (1)
// (1) RESP_PH[2:0] phase control bits only for internal respiration (RESP_CTRL = 10) and external respiration (RESP_CTRL = 01) modes
// when the CONFIG4.RESP_FREQ[2:0] register bits are 000b or 001b.
#define RPHASE_22_5                           0b000 // 22.5�
#define RPHASE_45                             0b001 // 45�
#define RPHASE_67_5                           0b010 // 67.5�
#define RPHASE_90                             0b011 // 90�
#define RPHASE_112_5                          0b100 // 112.5�
#define RPHASE_135                            0b101 // 135�
#define RPHASE_157_5                          0b110 // 157.5�

//Respiration control 
// These bits set the mode of the respiration circuitry.
#define NO_RESP                               0b00 // No respiration
#define EXT_RESP                              0b01 // External respiration
#define INT_RESP_IN_SIGN                      0b10 // Internal respiration with internal signals
#define INT_RESP_EXT_SIGN                     0b11 // Internal respiration with user-generated signals
//------------------------------------------------------------------------------

//----- WCT1: Wilson Central Terminal and Augmented Lead Control Register ------
public typedef struct 
{
  
  uint8_t ADDR;
  
  union
  {
    
    uint8_t BYTE;
    
    struct
    {
      
      __IOM uint8_t WCTA:3;
      
      __IOM uint8_t PD_WCTA:1;
      
      __IOM uint8_t aVR_CH4:1;
      
      __IOM uint8_t aVR_CH7:1;
      
      __IOM uint8_t aVR_CH5:1;
      
      __IOM uint8_t aVR_CH6:1;
      
    } BITS;
    
  };
  
  uint8_t (*GetWCT1)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetWCT1)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} WCT1_Type;

//------------------------------------------------------------------------------
// WCT Amplifier A channel selection, typically connected to RA electrode
// These bits select one of the eight electrode inputs of channels 1 to 4.
#define CH1P_INP_WCTA                         0b000 // Channel 1 positive input connected to WCTA amplifier
#define CH1N_INP_WCTA                         0b001 // Channel 1 negative input connected to WCTA amplifier
#define CH2P_INP_WCTA                         0b010 // Channel 2 positive input connected to WCTA amplifier
#define CH2N_INP_WCTA                         0b011 // Channel 2 negative input connected to WCTA amplifier
#define CH3P_INP_WCTA                         0b100 // Channel 3 positive input connected to WCTA amplifier
#define CH3N_INP_WCTA                         0b101 // Channel 3 negative input connected to WCTA amplifier
#define CH4P_INP_WCTA                         0b110 // Channel 4 positive input connected to WCTA amplifier
#define CH4N_INP_WCTA                         0b111 // Channel 4 negative input connected to WCTA amplifier

// Power-down WCTA
#define WCTA_PW_DOWN                          0b0 // Powered down
#define WCTA_PW_ON                            0b1 // Powered on

// Enable (WCTB + WCTC)/2 to the negative input of channel 4
#define SUM_WCT_2_DISABLE                     0b0 // Disabled
#define SUM_WCT_2_ENABLE                      0b1 // Enabled
//------------------------------------------------------------------------------

//----------- Wilson Central Terminal Control Registe --------------------------
public typedef struct 
{
  
  uint8_t ADDR;
  
  union 
  {
    
    uint8_t BYTE;
    
    struct
    {
      
      __IOM uint8_t WCTC:3;
      
      __IOM uint8_t WCTB:3;
      
      __IOM uint8_t PD_WCTB:1;
      
      __IOM uint8_t PD_WCTC:1;
      
    } BITS;
    
  };
  
  uint8_t (*GetWCT2)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetWCT2)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} WCT2_Type;

//------------------------------------------------------------------------------
// WCT amplifier C channel selection, typically connected to LL electrode.
// These bits select one of the eight electrode inputs of channels 1 to 4.
#define CH1P_INP_WCTC                         0b000 // Channel 1 positive input connected to WCTC amplifier
#define CH1N_INP_WCTC                         0b001 // Channel 1 negative input connected to WCTC amplifier
#define CH2P_INP_WCTC                         0b010 // Channel 2 positive input connected to WCTC amplifier
#define CH2N_INP_WCTC                         0b011 // Channel 2 negative input connected to WCTC amplifier
#define CH3P_INP_WCTC                         0b100 // Channel 3 positive input connected to WCTC amplifier
#define CH3N_INP_WCTC                         0b101 // Channel 3 negative input connected to WCTC amplifier
#define CH4P_INP_WCTC                         0b110 // Channel 4 positive input connected to WCTC amplifier
#define CH4N_INP_WCTC                         0b111 // Channel 4 negative input connected to WCTC amplifier

// WCT amplifier B channel selection, typically connected to LA electrode
// These bits select one of the eight electrode inputs of channels 1 to 4.
#define CH1P_INP_WCTB                         0b000 // Channel 1 positive input connected to WCTB amplifier
#define CH1N_INP_WCTB                         0b001 // Channel 1 negative input connected to WCTB amplifier
#define CH2P_INP_WCTB                         0b010 // Channel 2 positive input connected to WCTB amplifier
#define CH2N_INP_WCTB                         0b011 // Channel 2 negative input connected to WCTB amplifier
#define CH3P_INP_WCTB                         0b100 // Channel 3 positive input connected to WCTB amplifier
#define CH3N_INP_WCTB                         0b101 // Channel 3 negative input connected to WCTB amplifier
#define CH4P_INP_WCTB                         0b110 // Channel 4 positive input connected to WCTB amplifier
#define CH4N_INP_WCTB                         0b111 // Channel 4 negative input connected to WCTB amplifier

// Power-down WCTC
#define WCTC_PW_DOWN                          0b0 // Powered down WCTC
#define WCTC_PW_ON                            0b1 // Powered on WCTC

// Power-down WCTB
#define WCTB_PW_DOWN                          0b0 // Powered down WCTB
#define WCTB_PW_ON                            0b1 // Powered on WCTB
//------------------------------------------------------------------------------

#else

//---------------------- MISC1: Miscellaneous 1 Register -----------------------
public typedef struct 
{
  
  uint8_t ADDR;
  
  union
  {
    
    uint8_t BYTE;
    
    struct
    {
      
      __IM  uint8_t _reserved0:5;
      
      __IOM uint8_t SRB1:1;
      
      __IM  uint8_t _reserved1:2;
      
    } BITS;
    
  };
  
  uint8_t (*GetMISC1)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetMISC1)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} MISC1_Type;

//------------------------------------------------------------------------------
// Stimulus, reference, and bias 1
// This bit connects the SRB1 to all 4, 6, or 8 channels inverting inputs
#define SRB_OPEN                              0b0 // Switches open
#define SRB_CLOSE                             0b1 // Switches closed
//------------------------------------------------------------------------------

//----------- MISC2: Miscellaneous 2 Register ----------------------------------
public typedef struct 
{
  
  uint8_t ADDR;
  
  union
  {
    
    uint8_t BYTE;
    
    struct
    {
      
      __IM  uint8_t _reserved:8;    
      
    } BITS;
    
  };
  
  uint8_t (*GetMISC2)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetMISC2)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} MISC2_Type;
//------------------------------------------------------------------------------
// This register is reserved for future use
//------------------------------------------------------------------------------

#endif


//-------- CONFIG4: Configuration Register 4 -----------------------------------
public typedef struct 
{
  
  uint8_t ADDR;
  
  union
  {
    
    uint8_t BYTE;
    
    struct
    {
      
      __IM  uint8_t _reserved0:1;
      
      __IOM uint8_t PD_LOFF_COMP:1;
      
#ifdef ADS129x
      
      __IOM uint8_t WCT_TO_RLD:1;
      
#else
      
      __IM  uint8_t _reserved1:1;
      
#endif
      
      __IOM uint8_t SINGLE_SHOT:1;
      
#ifdef ADS129x
      
      __IM  uint8_t _reserved1:1;
      
      __IOM uint8_t RESP_FREQ:3;
      
#else
      
      __IM  uint8_t _reserved2:4;
      
#endif    
      
    } BITS;
    
  };
  
  uint8_t (*GetCONFIG4)(SPI_HandleTypeDef * hspi1, uint8_t address);
  void    (*SetCONFIG4)(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data);
  
} CONFIG4_Type;
//------------------------------------------------------------------------------
#ifdef ADS129x

// These bits control the respiration control frequency when
// RESP_CTRL[1:0] = 10 or RESP_CTRL[1:0] = 10(1).

#define RESP_FREQ_64kHZ                         0x0 // 64 kHz modulation clock

#define RESP_FREQ_32kHZ                         0x1 // 32 kHz modulation clock

#define RESP_FREQ_16kHZ                         0x2 // 16kHz square wave on GPIO3 and GPIO04. Output on
                                                      // GPIO4 is 180 degree out of phase with GPIO3

#define RESP_FREQ_8kHZ                          0x3 // 8kHz square wave on GPIO3 and GPIO04. Output on
                                                      // GPIO4 is 180 degree out of phase with GPIO3.

#define RESP_FREQ_4kHZ                          0x4 // 4kHz square wave on GPIO3 and GPIO04. Output on
                                                      // GPIO4 is 180 degree out of phase with GPIO3.

#define RESP_FREQ_2kHZ                          0x5 // 2kHz square wave on GPIO3 and GPIO04. Output on
                                                      // GPIO4 is 180 degree out of phase with GPIO3

#define RESP_FREQ_1kHZ                          0x6 // 1kHz square wave on GPIO3 and GPIO04. Output on
                                                      // GPIO4 is 180 degree out of phase with GPIO3.

#define RESP_FREQ_500HZ                         0x7 // 500Hz square wave on GPIO3 and GPIO04. Output on
                                                      // GPIO4 is 180 degree out of phase with GPIO3.

// Modes 000 and 001 are modulation frequencies in internal and
// external respiration modes. In internal respiration mode, the
// control signals appear at the RESP_MODP and RESP_MODN
// terminals. All other bit settings generate square waves as
// described above on GPIO4 and GPIO3.

// This bit connects WCT to RLD              
#define WCT_TO_RLD_OFF                          0x0 // WCT to RLD connection off
#define WCT_TO_RLD_ON                           0x1 // WCT to RLD connection on

#endif

// This bit sets the conversion mode
#define CONTINIUS_CONVERSETION_MODE_SH          0x0 // Continuous conversion mode
#define SINGLE_SHOT_SH                          0x1 // Single-shot mode

// This bit powers down the lead-off comparators.
#define PD_LOFF_COMP_DISABLED                   0x0 // Lead-off comparators disabled
#define PD_LOFF_COMP_ENABLED                    0x1 // Lead-off comparators enabled

//------------------------------------------------------------------------------

//==============================================================================
#include "IPowerManager.h"
#include "ICommand.h"
#include "IReadData.h"
//==============================================================================
public typedef struct ADS
{
// Read Only ID Registers  -----------------------------------------------------

  ID_Type           ID;
  
// -----------------------------------------------------------------------------

// Global Settings Across Channels ---------------------------------------------  
  
  CONFIG1_Type               CONFIG1;
  
  CONFIG2_Type               CONFIG2;
  
  CONFIG3_Type               CONFIG3;
  
  LOFF_Type                  LOFF;

// -----------------------------------------------------------------------------

// Channel-Specific Settings ---------------------------------------------------  
  
  CHnSET_Type                CHnSET[8];

#ifdef ADS129x
  
  RLD_SENSP_Type             RLD_SENSP;
  
  RLD_SENSN_Type             RLD_SENSN;
  
#else
    
  BIAS_SENSP_Type            BIAS_SENSP;
  
  BIAS_SENSN_Type            BIAS_SENSN;
  
#endif  
  
  LOFF_SENSP_Type            LOFF_SENSP;
  
  LOFF_SENSN_Type            LOFF_SENSN;
  
  LOFF_FLIP_Type             LOFF_FLIP;
  
// Lead-Off Status Registers (Read-Only Registers) -----------------------------  
  
  LOFF_STATP_Type            LOFF_STATP;
  
  LOFF_STATN_Type            LOFF_STATN;
  
// -----------------------------------------------------------------------------

// GPIO and OTHER Registers ----------------------------------------------------
  
  GPIO_Type                  GPIO;

#ifdef ADS129x

  PACE_Type                  PACE;
  
  RESP_Type                  RESP;
  
  WCT1_Type                  WCT1;
  
  WCT2_Type                  WCT2;
  
#else

  MISC1_Type                 MISC1;
  
  MISC2_Type                 MISC2;
  
#endif

  CONFIG4_Type               CONFIG4;
  
//------------------------------------------------------------------------------ 
  IPowerManager*             powerManager;
  ICommand*                  systemCommands;
  IReadData*                 readData;
    
} ADS_Type;

// Adress registers *************************************************************
// Device Settings (Read-only Registers)

#define ID_ADDRESS                       0x00 // ID

//Global Settings Across Channels

#define CONFIG1_ADDRESS                  0x01 // CONFIG1
#define CONFIG2_ADDRESS                  0x02 // CONFIG2
#define CONFIG3_ADDRESS                  0x03 // CONFIG3
#define CONFIG4_ADDRESS                  0x17 // CONFIG4
#define LOFF_ADDRESS                     0x04 // LOFF

//CHanel-Specific Settings

#define CH1SET_ADDRESS                   0x05 // CH1SET
#define CH2SET_ADDRESS                   0x06 // CH2SET
#define CH3SET_ADDRESS                   0x07 // CH3SET
#define CH4SET_ADDRESS                   0x08 // CH4SET
#define CH5SET_ADDRESS                   0x09 // CH5SET
#define CH6SET_ADDRESS                   0x0A // CH6SET
#define CH7SET_ADDRESS                   0x0B // CH7SET
#define CH8SET_ADDRESS                   0x0C // CH8SET

#ifdef ADS129x

  #define RLD_SENSP_ADDRESS                0x0D // RLD_SENSP
  #define RLD_SENSN_ADDRESS                0x0E // RLD_SENSN

#else

  #define BIAS_SENSP_ADDRESS               0x0D // BIAS_SENSP
  #define BIAS_SENSN_ADDRESS               0x0E // BIAS_SENSN

#endif

#define LOFF_SENSP_ADDRESS               0x0F // LOFF_SENSP
#define LOFF_SENSN_ADDRESS               0x10 // LOFF_SENSN
#define LOFF_FLIP_ADDRESS                0x11 // LOFF_FLIP

//Lead-Off Status Registers (Read-Only Registers)

#define LOFF_STATP_ADDRESS               0x12 // LOFF_STATP
#define LOFF_STATN_ADDRESS               0x13 // LOFF_STATN

//GPIO and Others Registers

#define GPIO_ADDRESS                     0x14 // GPIO

#ifdef ADS129x

  #define PACE_ADDRESS                     0x15 // PACE
  #define RESP_ADDRESS                     0x16 // RESP

  #define WCT1_ADDRESS                     0x18 // WCT1
  #define WCT2_ADDRESS                     0x19 // WCT2

#else

  #define MISC1_ADDRESS                    0x15 // BIAS_SENSP
  #define MISC2_ADDRESS                    0x16 // BIAS_SENSN

#endif


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Reset DATA value (HEX) *******************************************************
#define ID_RST_VALUE                    0x00 // ID
//Global Settings Across Channels
#define CONFIG1_RST_VALUE               0x06 // CONFIG1
#define CONFIG2_RST_VALUE               0x40 // CONFIG2
#define CONFIG3_RST_VALUE               0xC0 // CONFIG3
#define CONFIG4_RST_VALUE               0x00 // CONFIG4
#define LOFF_RST_VALUE                  0x00 // LOFF

//CHanel-Specific Settings
#define CHnSET_RST_VALUE                0x00 // CH1SET

#ifdef ADS129x

  #define RLD_SENSP_RST_VALUE            0x00 // RLD_SENSP
  #define RLD_SENSN_RST_VALUE            0x00 // RLD_SENSN

#else

  #define BIAS_SENSP_RST_VALUE           0x00 // BIAS_SENSP
  #define BIAS_SENSN_RST_VALUE           0x00 // BIAS_SENSN

#endif

#define LOFF_SENSP_RST_VALUE            0x00 // LOFF_SENSP
#define LOFF_SENSN_RST_VALUE            0x00 // LOFF_SENSN
#define LOFF_FLIP_RST_VALUE             0x00 // LOFF_FLIP

//Lead-Off Status Registers (Read-Only Registers)
#define LOFF_STATP_RST_VALUE            0x00 // LOFF_STATP
#define LOFF_STATN_RST_VALUE            0x00 // LOFF_STATN

//GPIO and Others Registers
#define GPIO_RST_VALUE                  0x0F // GPIO

#ifdef ADS129x

  #define PACE_RST_VALUE                 0x00 // PACE
  #define RESP_RST_VALUE                 0x00 // RESP

  #define WCT1_RST_VALUE                 0x00 // WCT1
  #define WCT2_RST_VALUE                 0x00 // WCT2

#else

  #define MISC1_RST_VALUE                0x00 // BIAS_SENSP
  #define MISC2_RST_VALUE                0x00 // BIAS_SENSN

#endif




//==============================================================================

//---------------- Global functions prototypes ---------------------------------//
public ADS_Type * GetInstance();
//------------------------------------------------------------------------------//
#endif