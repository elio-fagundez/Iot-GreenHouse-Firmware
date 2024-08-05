#include "main.h"
#include "esp32-hal-gpio.h"
#include "outputs.h"

void outputs_init(void)
{
  pinMode((uint8_t) FAN_PIN, OUTPUT);
  pinMode((uint8_t) HEATING_PIN, OUTPUT);
  pinMode((uint8_t) SUBMERSIBL_PIN, OUTPUT);
  pinMode((uint8_t) WATER_PUMP_PIN, OUTPUT);

  digitalWrite((uint8_t) FAN_PIN, LOW);
  digitalWrite((uint8_t) HEATING_PIN, LOW);
  digitalWrite((uint8_t) SUBMERSIBL_PIN, LOW);
  digitalWrite((uint8_t) WATER_PUMP_PIN, LOW);

}

void fan_set(uint8_t state)
{
  digitalWrite(FAN_PIN, state);
}

void heating_set(uint8_t state)
{
  digitalWrite(HEATING_PIN, state);
}

void sumersibl_set(uint8_t state)
{
  digitalWrite(SUBMERSIBL_PIN, state);
}

void water_pump_set(uint8_t state)
{
  digitalWrite(WATER_PUMP_PIN, state);
}

void test_all_outputs(void)
{
  fan_set(1);
  heating_set(1);
  sumersibl_set(1);
  water_pump_set(1);
  delay(2000);
  fan_set(0);
  heating_set(0);
  sumersibl_set(0);
  water_pump_set(0);
}