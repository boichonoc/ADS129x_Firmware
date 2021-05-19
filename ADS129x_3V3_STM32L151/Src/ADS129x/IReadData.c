#include "IReadData.h"
#include "Utils.h"

private IReadData readData = { 0 };
private OutData data = { .PACKAGE = 0x00 };

private OutData* _OutData (SPI_HandleTypeDef *  hspi);

IReadData* ReadData()
{
    readData.ReadData = _OutData;
    readData.pkgSize = PACKAGE_SIZE;

    return &readData;
}

private OutData* _OutData (SPI_HandleTypeDef *  hspi)
{  
  CsSet();
  for( int i = 0; i < PACKAGE_SIZE; i++)
  {
    HAL_SPI_Transmit(hspi, (uint8_t*)0x23, 1, 1);
    data.PACKAGE[i] = SPI1->DR;
  }
  CsReset();
  
  return &data;
}
