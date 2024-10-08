#include "main.h"
#include "src/TempHum/TempHum.h"
#include "src/LightSensor/LightSensor.h"
#include "src/CapSoil/CapSoil.h"
#include "src/CCS811/CCS811.h"
#include "src/Ph/Ph.h"
#include "src/MQ135/MQ135.h"
#include "src/mqtt/mqtt_srv.h"
#include "src/Display_tft/Display_tft.h"
#include "src/outputs/outputs.h"

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
uint16_t moisture = 0;
// CCS811
DFRobot_CCS811 CCS811;
// MQ135
float rs_med;
float concentration;
// PH
float ph = 0.0;
// DISPLAY
DFRobot_Touch_XPT2046 touch(/*cs=*/TOUCH_CS);
DFRobot_ILI9341_240x320_HW_SPI  screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
DFRobot_UI ui(&screen, &touch);
// MQTT
WiFiClientSecure espClient;
PubSubClient client(espClient);
char payload_msg[256];
// WIFI STATE
WiFiState wifiState = DISCONNECTED;
unsigned long lastAttemptTime = 0;
const unsigned long attemptInterval = 1000;
int connect_count = 0;
// timers
uint8_t t_printData = 0, t_publishData = 0;

// Functions
void handleWiFiConnection(void);
void printData(void);
void processTime(void);

void setup()
{
  SERIAL_MON.begin(SERIAL_BAUD);
  DEBUG_NL("[setup] Initializing sow device");
  analogReadResolution(9);
  outputs_init();
  DHT_init(&dht);
  DHTSensor(&dht);

  LightSensor_Init(&lightMeter);
  LightSensor_Read(0);

  CapSoil_init();
  moisture = Moisture_Read((uint8_t)MOISTUREPIN);

  CCS811_init(&CCS811);

  mq135_init(MQ135_DO_PIN, MQ135_AO_PIN);

  PH_init();

  display_tft_init();

  mqtt_srv_init();

  test_all_outputs();
}

void loop()
{
  handleWiFiConnection();
  mqtt_srv_loop();
  processTime();
  display_tft_loop();

  if(t_printData >= 5)
  {
    printData();
    t_printData = 0;
  }

  if (t_publishData >= MQTT_TIME2PUBLISH_S)
  {
    memset(payload_msg, 0, sizeof(payload_msg));
    sprintf(payload_msg, "{\"temp\": %.2f, \"hum\": %.2f, \"lum\": %.2f, \"moi\": %d, \"rs_med\": %.2f, \"conc\": %.2f, \"volts\": %.2f, \"Ph\": %.2f}", temperature, humidity, lux, moisture, rs_med, concentration, mq135_ao_get(), ph);
    mqtt_srv_publish("topic/example/sow", payload_msg);
    t_publishData = 0;
  }
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
        first_connect = 0;
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
          mqtt_srv_reconnect();
        }
      }
      break;
  }
}

void printData(void)
{
  char aux[255];
  memset(aux, 0, sizeof(aux));

  rs_med = mq135_readMQ();    // Obtener la Rs promedio
  concentration = mq135_getConcentration(rs_med/R0);
  moisture = Moisture_Read((uint8_t)MOISTUREPIN);
  ph = PH_get();
  sprintf(aux, "[loop] temp: %.2f hum: %.2f lum: %.2f moi: %d rs_med: %.2f conc: %.2f volts: %.2f Ph: %.2f", temperature, humidity, lux, moisture, rs_med, concentration, mq135_ao_get(), ph);
  DEBUG_NL(aux);
  DHTSensor(&dht);
  LightSensor_Read(0);

}

void processTime(void)
{
  static uint32_t lastAttemptTime = 0; 
  uint32_t attemptInterval = 1000;

  if (millis() - lastAttemptTime >= attemptInterval)
  {
    lastAttemptTime = millis();
    t_printData++;
    t_publishData++;
  }
}
