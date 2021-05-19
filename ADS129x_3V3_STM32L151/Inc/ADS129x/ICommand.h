#ifndef __ICommand_H
#define __ICommand_H

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stm32l1xx_hal.h"


typedef struct  
{
  bool          (*WakeUpFromStandlyMode)         (SPI_HandleTypeDef * hspi);
  bool          (*EnterStandlyMode)              (SPI_HandleTypeDef * hspi);
  bool          (*ResetTheDevice)                (SPI_HandleTypeDef * hspi);
  bool          (*StartConversetion)             (SPI_HandleTypeDef * hspi);
  bool          (*StopConversetion)              (SPI_HandleTypeDef * hspi);
  
  bool          (*EnableReadDataContinuousMode)  (SPI_HandleTypeDef * hspi);
  bool          (*DisableReadDataContinuousMode) (SPI_HandleTypeDef * hspi);
  bool          (*EnableReadDataByCommand)       (SPI_HandleTypeDef * hspi);
  
}ICommand;

ICommand* SystemCommands();

#endif