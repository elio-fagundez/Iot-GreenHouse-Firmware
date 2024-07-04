#include "CapSoil.h"

void CapSoil_init(void)
{
  return;
}

int Moisture_Read(void)
{
  return analogRead(CAP_SOIL_PIN);
}