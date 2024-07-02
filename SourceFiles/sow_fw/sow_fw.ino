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
// WIFI STATE
WiFiState wifiState = DISCONNECTED;
unsigned long lastAttemptTime = 0;
const unsigned long attemptInterval = 1000;
int connect_count = 0;

// Functions
void handleWiFiConnection(void);

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
  handleWiFiConnection();
}

void handleWiFiConnection()
{
  static uint8_t first_connect = 0;
  static unsigned long lastDisconnectTime = 0;

  switch (wifiState) {
    case DISCONNECTED:
    {
      DEBUG_NL("[handleWiFiConnection] \n   Connecting to:  %s with: %s", SSID, PASSWORD);
      WiFi.begin(SSID, PASSWORD);
      wifiState = CONNECTING;
      lastAttemptTime = millis();
    }
    break;

    case CONNECTING:
    {
      if (WiFi.status() == WL_CONNECTED)
      {
        wifiState = CONNECTED;
        DEBUG_NL("   WiFi connected");
        DEBUG_NL("   IP address: %d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
      } 
      else if (millis() - lastAttemptTime >= attemptInterval)
      {
        lastAttemptTime = millis();
        connect_count++;
        if (connect_count > 180)
        {
          wifiState = DISCONNECTED;  // Return to the DISCONNECTED state or handle the failure as you prefer
          DEBUG_NN("");
          connect_count = 0;
        }
      }
    }
    break;

    case CONNECTED:
    {
      // If you need to do something periodically when you're online, you can do it here.
      if (WiFi.status() != WL_CONNECTED && millis() - lastDisconnectTime > 30000)
      {
        DEBUG_NN("WiFi disconnected for more than 30 seconds. Reconnecting...");
        wifiState = DISCONNECTED;
        lastDisconnectTime = millis();  // Update disconnection time
      }

      if (!first_connect)
      {
        first_connect = 1;
      }
    }
    break;
  }
}
