#ifndef __IPowerManager_H
#define __IPowerManager_H

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stm32l1xx_hal.h"

typedef struct  
{
  
  void (*PowerUp)       (SPI_HandleTypeDef * hspi, bool (*ResetTheDevice)(SPI_HandleTypeDef * hspi));
  void (*PowerDown)     ();
  
}IPowerManager;

IPowerManager* PowerManager();

#endif