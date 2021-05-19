#include "ICommand.h"
#include "Utils.h"

ICommand commands;

static bool WakeUpFromStandlyMode(SPI_HandleTypeDef * hspi);
static bool EnterStandlyMode(SPI_HandleTypeDef * hspi);
static bool ResetTheDevice(SPI_HandleTypeDef * hspi);
static bool StartConversetion(SPI_HandleTypeDef * hspi);
static bool StopConversetion(SPI_HandleTypeDef * hspi);
static bool EnableReadDataContinuousMode(SPI_HandleTypeDef * hspi);
static bool DisableReadDataContinuousMode(SPI_HandleTypeDef * hspi);
static bool EnableReadDataByCommand(SPI_HandleTypeDef * hspi);
static HAL_StatusTypeDef SendComand (SPI_HandleTypeDef * hspi1, uint8_t comand);


ICommand* SystemCommands()
{
  commands.WakeUpFromStandlyMode = WakeUpFromStandlyMode;
  commands.EnableReadDataContinuousMode = EnableReadDataContinuousMode;
  commands.DisableReadDataContinuousMode = DisableReadDataContinuousMode;
  commands.EnableReadDataByCommand = EnableReadDataByCommand;
  commands.EnterStandlyMode = EnterStandlyMode;
  commands.ResetTheDevice = ResetTheDevice;
  commands.StartConversetion = StartConversetion;
  commands.StopConversetion = StopConversetion;
  
  return &commands;
}

/*
 * -----------------------------------------------------------------------------
 * Realisation functions of ICommand interfaces                         START
 * -----------------------------------------------------------------------------
 */
      
static bool WakeUpFromStandlyMode(SPI_HandleTypeDef * hspi)
{
  bool result = false;
  
  if( SendComand(hspi, WAKEUP) == HAL_OK )
  {
    result = true;
  }
  
  return result;
}

static bool EnterStandlyMode(SPI_HandleTypeDef * hspi)
{
  bool result = false;
  
  if( SendComand(hspi, STANDY) == HAL_OK )
  {
    result = true;
  }
  
  return result;
}

static bool ResetTheDevice(SPI_HandleTypeDef * hspi)
{
  bool result = false;
  
  if( SendComand(hspi, RST) == HAL_OK )
  {
    result = true;
  }
  
  return result;
}

static bool StartConversetion(SPI_HandleTypeDef * hspi)
{
  bool result = false;
  // MB Should add HAL_GPIO_WritePin(START_GPIO_Port, START_Pin,  GPIO_PIN_RESET);
  if( SendComand(hspi, START) == HAL_OK )
  {
    result = true;
  }
  
  return result;
}

static bool StopConversetion(SPI_HandleTypeDef * hspi)
{
  bool result = false;
  
  if( SendComand(hspi, STOP) == HAL_OK )
  {
    result = true;
  }
  
  return result;
}

static bool EnableReadDataContinuousMode(SPI_HandleTypeDef * hspi)
{
  bool result = false;
  
  if( SendComand(hspi, RDATAC) == HAL_OK )
  {
    result = true;
  }
  
  return result;
}

static bool DisableReadDataContinuousMode(SPI_HandleTypeDef * hspi)
{
  bool result = false;
  
  if( SendComand(hspi, SDATAC) == HAL_OK)
  {
    result = true;
  }
  
  return result;
}

static bool EnableReadDataByCommand(SPI_HandleTypeDef * hspi)
{
  bool result = false;
  
  if( SendComand(hspi, RDATA) == HAL_OK )
  {
    result = true;
  }
  
  return result;
}



/*
 * -----------------------------------------------------------------------------
 * Realisation functions of ICommand interfaces                         END
 * -----------------------------------------------------------------------------
 */