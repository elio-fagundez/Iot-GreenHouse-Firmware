#ifndef _OUTPUTS_H
#define _OUTPUTS_H
  #include "./main.h"
  void outputs_init(void);
  void fan_set(uint8_t state);
  void heating_set(uint8_t state);
  void sumersibl_set(uint8_t state);
  void water_pump_set(uint8_t state);
  void relay01_set(uint8_t state);
  void relay02_set(uint8_t state);
  void test_all_outputs(void);
#endif