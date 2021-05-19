#ifndef __StatusLed_H
#define __StatusLed_H

#include "stdint.h"
#include "stm32l1xx_hal.h"

typedef struct
{

  GPIO_TypeDef* port;

  uint16_t pin;

} StatusLed;

void InitBlink(StatusLed* led, uint8_t n_repetitions, volatile uint32_t delay);

#endif