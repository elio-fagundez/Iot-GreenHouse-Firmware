#ifndef __MAIN_H
#define __MAIN_H
#include <WiFi.h>
#include "LittleFS.h"
#include <WiFiClientSecure.h>
#include "DHT.h"
#include <Wire.h>
#include <BH1750.h>
#include "DFRobot_CCS811.h"


/* ========================== DEFINITIONS ==========================*/
enum StateVariables
{
  DHT22_ONE_DETECTED = BIT0,
  GPS_DATA_VALID = BIT1,
};

enum WiFiState
{
  DISCONNECTED,
  CONNECTING,
  CONNECTED
};

/* ========================== WIFI CREDENTIALS ==========================*/
#define SSID "Main_Program_24GHZ"
#define PASSWORD "nuncadigasnunca2007"

/* ==========================       MQTT        ==========================*/
#include <PubSubClient.h>
#define MQTT_SERVER           "servidor.amazonaws.com"            /* aws iot core endpoint */
#define MQTT_PORT             8883                                /* port aws iot core*/
/* This files must be in the data folder in the same root of the .ino file */
#define FILE__PEM             "/AmazonRootCA1.pem"                /* RSA 2048 bit key */
#define FILE__PEM__CRT        "/08e3be248a-certificate.pem.crt"   /* Public key file aws iot core */ 
#define FILE__PEM__KEY        "/08e3be248a-private.pem.key"       /* Privated key file aws iot core */ 
#define MQTT_TIME2PUBLISH_S   10

/* ========================== DEBUG ==========================*/
#define ENABLE_DEBUG        // Indicates whether serial debugging is enabled or not by default
#define SERIAL_MON Serial   // Serial output for debug console
#define SERIAL_BAUD 115200  // Data rate in bits per second (baud)
#ifdef ENABLE_DEBUG
#define DEBUG_NN(...) printf(__VA_ARGS__)
#define DEBUG_NT(...) print(__VA_ARGS__)
#define DEBUG_NL(...) \
  printf(__VA_ARGS__); \
  printf("\n")
#else
#define DEBUG_NN(...)
#define DEBUG_NL(...)
#define DEBUG_NT(...)
#endif

/* ========================== DHT22 ==========================*/
#if CONFIG_IDF_TARGET_ESP32C6
#define DHTPIN 01
#else
#define DHTPIN 27
#endif
#define DHTTYPE DHT22
/* ========================== BH1750 ==========================*/
#if CONFIG_IDF_TARGET_ESP32C6
#define SCLPIN 7
#define SDAPIN 6
#else
#define SCLPIN 22
#define SDAPIN 21
#endif
/* ========================== CAPACITIVE SOIL ==========================*/
#if CONFIG_IDF_TARGET_ESP32C6
#define MOISTUREPIN 2
#else
#define MOISTUREPIN 4
#endif

/* ========================== PH ==========================*/
#define ReceivedBufferLength      20
#define SCOUNT                    30
#define SLOPE_VALUE_ADDRESS       0
#define INTERCEPT_VALUE_ADDRESS   (SlopeValueAddress + 4)
#define VREF                      5000
#if CONFIG_IDF_TARGET_ESP32C6
#define SENSOR_PH_PIN             3
#else
#define SENSOR_PH_PIN             26
#endif

/* ========================== MQ-135 ==========================*/
#if CONFIG_IDF_TARGET_ESP32C6
#define MQ135_DO_PIN    4
#define MQ135_AO_PIN    5
#else
#define MQ135_DO_PIN    32
#define MQ135_AO_PIN    33
#endif
// Datos para lectura multiple
#define RL_VALUE                5       // Resistencia RL del modulo en Kilo ohms
#define R0                      10      // Resistencia R0 del sensor en Kilo ohms
#define READ_SAMPLE_INTERVAL    100     // Tiempo entre muestras
#define READ_SAMPLE_TIMES       5       // Numero muestras
// Ajustar estos valores para vuestro sensor según el Datasheet
#define X0    200
#define Y0    1.7
#define X1    10000
#define Y1    0.28

/* ========================== 320x240 TFT LCD ==========================*/
#include "DFRobot_UI.h"
#include "Arduino.h"
#include "DFRobot_GDL.h"
#include "DFRobot_Touch.h"
#if CONFIG_IDF_TARGET_ESP32C6
#define TFT_DC      12
#define TFT_CS      18
#define TFT_RST     22
#define TOUCH_CS    13
#else
#define TFT_DC      2
#define TFT_CS      15
#define TFT_RST     0
#define TOUCH_CS    25
#endif

/* ==========================    OUTPUTS    ==========================*/
#define FAN_PIN         21
#define HEATING_PIN     22
#define SUBMERSIBL_PIN  23
#define WATER_PUMP_PIN  20
#define RELAY_01_PIN    33
#define RELAY_02_PIN    32

extern DFRobot_ILI9341_240x320_HW_SPI  screen;
extern DFRobot_Touch_XPT2046 touch;
extern DFRobot_UI ui;
extern WiFiClientSecure espClient;
extern PubSubClient client;
#endif