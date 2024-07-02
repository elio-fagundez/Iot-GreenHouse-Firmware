#include "main.h"
#include "src/TempHum/TempHum.h"
#include "src/LightSensor/LightSensor.h"
#include "src/CapSoil/CapSoil.h"
#include "src/CCS811/CCS811.h"

//MAIN
uint32_t stateVariables = 0;
// DHT22
DHT dht(DHTPIN, DHTTYPE);
float temperature;
float humidity;
// BH1750
BH1750 lightMeter;
float lux;
// MOISTURE
int moisture;
// CCS811
DFRobot_CCS811 CCS811;

void setup()
{
  SERIAL_MON.begin(SERIAL_BAUD);
  DEBUG_NL("[setup] Initializing sow device");

  DHT_init(&dht);
  DHTSensor(&dht);

  LightSensor_Init(&lightMeter);
  LightSensor_Read(0);

  CapSoil_init();
  moisture = Moisture_Read();

  CCS811_init(&CCS811);

}

void loop()
{


}
