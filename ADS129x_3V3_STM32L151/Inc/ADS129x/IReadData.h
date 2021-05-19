#ifndef __IReadData_H
#define __IReadData_H

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stm32l1xx_hal.h"

#define PACKAGE_SIZE                  27
#define PART_PACKAGE_SIZE             3

typedef struct 
{

  union
  {

    volatile uint8_t PACKAGE[PACKAGE_SIZE];

    struct
    {
      uint8_t STATUS[PART_PACKAGE_SIZE];
      uint8_t CHN1[PART_PACKAGE_SIZE];
      uint8_t CHN2[PART_PACKAGE_SIZE];
      uint8_t CHN3[PART_PACKAGE_SIZE];
      uint8_t CHN4[PART_PACKAGE_SIZE];
      uint8_t CHN5[PART_PACKAGE_SIZE];
      uint8_t CHN6[PART_PACKAGE_SIZE];
      uint8_t CHN7[PART_PACKAGE_SIZE];
      uint8_t CHN8[PART_PACKAGE_SIZE];
    };

  };

} OutData;

typedef struct  
{

  uint8_t pkgSize;

  OutData* (*ReadData) (SPI_HandleTypeDef *  hspi);
  
}IReadData;

IReadData* ReadData();

#endif