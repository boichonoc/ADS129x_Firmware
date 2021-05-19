#include "StatusLed.h"

void InitBlink(StatusLed* led, uint8_t n_repetitions, volatile uint32_t delay)
{
    for(uint8_t i = 0; i < n_repetitions; i++)
    {
        HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
        HAL_Delay(delay);
        HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
        HAL_Delay(delay);
    }
}