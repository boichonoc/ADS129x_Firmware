#ifndef __DevicePresenter_H
#define __DevicePresenter_H

#include "StatusLed.h"
#include "stdint.h"
#include "stdbool.h"

public typedef struct
{

    bool (*Initialize)(void);
    void (*CustomConfiguration)(SPI_HandleTypeDef * hspi);
    void (*ReadData)(SPI_HandleTypeDef * hspi, UART_HandleTypeDef * huart);

} DevicePresenter;

DevicePresenter* _DevicePresenter(StatusLed * statusLed);

#endif