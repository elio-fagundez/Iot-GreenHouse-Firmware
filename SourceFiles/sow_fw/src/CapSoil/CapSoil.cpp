#include "CapSoil.h"

void CapSoil_init(void)
{
  return;
}

uint16_t Moisture_Read(uint8_t sensorPin)
{
  return analogRead(sensorPin);
}