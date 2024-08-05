#include "main.h"
#include <stdint.h>
#include "Ph.h"

float calibration = 0.0;
int sensorValue = 0;
unsigned long int avgValue;
float b;
uint16_t _buf[10];

void PH_init(void)
{
  return;
}

float PH_get(void)
{
  for (int i = 0; i < 10; i++)
  {
    _buf[i] = analogRead((uint8_t)SENSOR_PH_PIN);
    delay(30);
  }
  avgValue = 0;
  for (int i = 0; i < 10; i++)
    avgValue += _buf[i];
  float pHVol = (float)avgValue * 3.3 / 400.0 /10.0;
  float phValue = -5.70 * pHVol + calibration;
  SERIAL_MON.print("[PH_get] Ph = ");
  SERIAL_MON.println(phValue);
  
  return phValue;
}