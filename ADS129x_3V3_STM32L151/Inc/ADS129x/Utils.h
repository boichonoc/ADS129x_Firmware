#ifndef __Utils_H
#define __Utils_H

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stm32l1xx_hal.h"

//-- �������� ��� ������� ����������. �������� ��������. -----------------------

//#define TCLK       1      // Tclk = 420 ns
//#define TPOR       32768  // 110 // Tpor = 2^18 * Tclk   

//------------------------------------------------------------------------------

#define TCSH                            1               // 2 TCLKs
#define TCSSC                           1               // 6 ns
#define TSCCS                           2               // 4 TCLKs
#define TCMD                            2               // 4 TCLKs

#define CsSet()   HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)
#define CsReset() HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)

//SYSTEM COMMANDS  
typedef enum
{
  WAKEUP = 0x02,        // WAKE UP from standly mode
  STANDY = 0x04,        // STANDBY - Enter standly mode
  RST    = 0x06,        // RESET the device
  START  = 0x08,        // START/RESTART (synchronize) conversions
  STOP   = 0x0A         // STOP conversion
    
} ADS_SystemCommand;
//DATA READ MODE
typedef enum 
{
  RDATAC = 0x10,        // Enable Read Data Continuous mode(defaulte mode at power up)
  SDATAC = 0x11,        // Stop read Data Continuously mode
  RDATA  = 0x12         // Read data by command; supports multiple read back
    
} ADS_ReadDataMode;

// Low Layer Functions -------------------------------------------------------//
static HAL_StatusTypeDef SendComand (SPI_HandleTypeDef * hspi1, uint8_t comand)
{    
  HAL_StatusTypeDef result;
  CsSet();
  HAL_Delay(TCSH);
  
  result = HAL_SPI_Transmit( hspi1, &comand, 1, TCMD);
  (void)(SPI1->DR);
  HAL_Delay(TCSSC);
  
  HAL_Delay(TSCCS);
  CsReset();
  
  HAL_Delay(TCSSC);
  
  return result;
}

#define R_REG                           0x20 // Read from regist
static uint8_t RREG(SPI_HandleTypeDef * hspi1, uint8_t  address) 
{
  uint8_t result = 0; 
  uint8_t opcode1 = R_REG | address ;
  uint8_t opcode_x[2];
  opcode_x[0] = opcode1;
  opcode_x[1] = 0x00;
  uint8_t read = 0x00;
  
  CsSet();
  HAL_Delay(TCSH);
  
  HAL_SPI_Transmit(hspi1, &opcode_x[0], 1, 1);
  (void)(SPI1->DR);
  HAL_Delay(TCSSC);
  HAL_SPI_Transmit(hspi1, &opcode_x[1], 1, 1);
  (void)(SPI1->DR);
  HAL_Delay(TCSSC);
  HAL_SPI_Transmit(hspi1, &read, 1, 1);
  result = SPI1->DR;
  HAL_Delay(TCSSC);
  
  HAL_Delay(TSCCS);
  CsReset();
  
  HAL_Delay(TCSSC);
  return result;
}

#define W_REG                           0x40 // Write to regist
static void WREG(SPI_HandleTypeDef * hspi1, uint8_t address, uint8_t data) 
{
  uint8_t opcode1 =  W_REG | address;
  uint8_t opcode_x[2];
  
  opcode_x[0] = opcode1;
  opcode_x[1] = 0x00;
  CsSet();
  HAL_Delay(TCSH);
  
  HAL_SPI_Transmit(hspi1, &opcode_x[0], 1, 1);
  (void)(SPI1->DR);
  HAL_Delay(TCSSC);        
  HAL_SPI_Transmit(hspi1, &opcode_x[1], 1, 1);
  (void)(SPI1->DR);
  HAL_Delay(TCSSC);        
  HAL_SPI_Transmit(hspi1, &data, 1, 1);
  (void)(SPI1->DR);
  HAL_Delay(TCSSC); 
  
  HAL_Delay(TSCCS);
  CsReset();
  
  HAL_Delay(TCSSC);          
}


#endif
