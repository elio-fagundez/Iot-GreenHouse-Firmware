#include "LightSensor.h"

const int LightSensoraddress = 0x23;
byte buffer[2];

extern BH1750 lightMeter;
extern float lux;

void LightSensor_Init(BH1750 *sensor)
{
  Wire.begin(SDAPIN,SCLPIN);
  sensor->begin();
  DEBUG_NL("[LightSensor_Init] BH1750 Test begin");
}

void LightSensor_Read(int address)
{
  lux = lightMeter.readLightLevel();
}