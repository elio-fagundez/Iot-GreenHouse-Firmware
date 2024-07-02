#include "main.h"
#include "src/TempHum/TempHum.h"
#include "src/LightSensor/LightSensor.h"

//MAIN
uint32_t stateVariables = 0;
// DHT22
DHT dht(DHTPIN, DHTTYPE);
float temperature;
float humidity;
// BH1750
BH1750 lightMeter;
float lux;


void setup()
{
  SERIAL_MON.begin(SERIAL_BAUD);
  DEBUG_NL("[setup] Initializing sow device");

  initDht22(&dht);
  DHTSensor(&dht);

  LightSensor_Init(&lightMeter);
  LightSensor_Read(0);

}

void loop()
{


}
