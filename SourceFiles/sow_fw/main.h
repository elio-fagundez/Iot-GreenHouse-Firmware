#ifndef __MAIN_H
#define __MAIN_H
#include <WiFi.h>
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
#define SSID "network"
#define PASSWORD "password_default"

/* ========================== DEBUG ==========================*/
#define ENABLE_DEBUG        // Indicates whether serial debugging is enabled or not by default
#define SERIAL_MON Serial   // Serial output for debug console
#define SERIAL_BAUD 115200  // Data rate in bits per second (baud)
#ifdef ENABLE_DEBUG
#define DEBUG_NN(...) printf(__VA_ARGS__)
#define DEBUG_NL(...) \
  printf(__VA_ARGS__); \
  printf("\n")
#else
#define DEBUG_NN(...)
#define DEBUG_NL(...)
#endif

/* ========================== DHT22 ==========================*/
#define DHTPIN 15
#define DHTTYPE DHT22

/* ========================== CAPACITIVE SOIL ==========================*/
#define CAP_SOIL_PIN 32
#endif