#ifndef __LightSensor_H
#define __LightSensor_H
  #include "main.h"

  void LightSensor_Init(BH1750 *sensor);
  void LightSensor_Read(int address);
#endif