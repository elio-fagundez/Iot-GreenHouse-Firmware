#include <stdint.h>
#include "TempHum.h"

extern float temperature;
extern float humidity;
extern uint32_t stateVariables;

void DHT_init(DHT *dht)
{
  dht->begin();
}

void DHTSensor(DHT *dht)
{
  temperature = dht->readTemperature();
  humidity = dht->readHumidity();
  if (isnan(humidity) || isnan(temperature))
  {
    stateVariables &= ~DHT22_ONE_DETECTED;
    DEBUG_NL("[SensorDHT] Error de sensor DHT11");
    return;
  }
  stateVariables |= DHT22_ONE_DETECTED;
}