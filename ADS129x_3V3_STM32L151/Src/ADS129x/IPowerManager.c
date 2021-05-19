#include "IPowerManager.h"
#include "Utils.h"

#define TPOR                            110             // 2^16 TCLKs
#define TRST                            2               // 2 TCLKs 
#define TRST2                           15              // 18 TCLKs

IPowerManager manager;

static void PowerUpSequencing(SPI_HandleTypeDef * hspi, bool (*ResetTheDevice)(SPI_HandleTypeDef * hspi));
static void PowerDownSequencing();

IPowerManager* PowerManager()
{
  manager.PowerUp = PowerUpSequencing;
  manager.PowerDown = PowerDownSequencing;
  
  return &manager;
}

/*
 * -----------------------------------------------------------------------------
 * Realisation functions of IPowerManager interfaces                    START
 * -----------------------------------------------------------------------------
 */
static void PowerUpSequencing(SPI_HandleTypeDef * hspi, bool (*ResetTheDevice)(SPI_HandleTypeDef * hspi))
{
  CsReset();
  HAL_GPIO_WritePin(START_GPIO_Port, START_Pin,  GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(PWDN_GPIO_Port, PWDN_Pin,  GPIO_PIN_SET);
  HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_SET);
  
  ResetTheDevice(hspi);
  HAL_Delay(TPOR);
  
  HAL_GPIO_WritePin(PWDN_GPIO_Port, PWDN_Pin,  GPIO_PIN_RESET);
  ResetTheDevice(hspi);
  HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_RESET);
  HAL_Delay(TRST);
  HAL_GPIO_WritePin(PWDN_GPIO_Port, PWDN_Pin,  GPIO_PIN_SET); 
  ResetTheDevice(hspi);
  HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_SET);
  HAL_Delay(TRST2);
    
  CsSet();
  HAL_Delay(TCSH);
  CsReset();    
}   

static void PowerDownSequencing() 
{
  HAL_GPIO_WritePin(START_GPIO_Port, START_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(PWDN_GPIO_Port,  PWDN_Pin,  GPIO_PIN_RESET);
  HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_RESET);
}
/*
 * -----------------------------------------------------------------------------
 * Realisation functions of IPowerManager interfaces                    END
 * -----------------------------------------------------------------------------
 */