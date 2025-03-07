#include "MQ135.h"

int _do_pin, _ao_pin;
// Puntos de la curva de concentración {X, Y}
const float punto0[] = { log10(X0), log10(Y0) };
const float punto1[] = { log10(X1), log10(Y1) };

// Calcular pendiente y coordenada abscisas
const float scope = (punto1[1] - punto0[1]) / (punto1[0] - punto0[0]);
const float coord = punto0[1] - punto0[0] * scope;

void mq135_init(int do_pin, int ao_pin)
{
  _do_pin = do_pin;
  _ao_pin = ao_pin;
}

bool mq135_do_get(void)
{
  return digitalRead(_do_pin);
}

float mq135_ao_get(void)
{
  int raw_adc = analogRead(_ao_pin);
  Serial.println(raw_adc);
  float value_adc = raw_adc * (5.0 / 4095.0);
  return value_adc;
}

float mq135_readMQ(void)
{
  float rs = 0;
  for (int i = 0; i < READ_SAMPLE_TIMES;i++)
  {
    rs += mq135_getMQResistance(analogRead(_ao_pin));
    delay(READ_SAMPLE_INTERVAL);
  }
  return rs / READ_SAMPLE_TIMES;
}

// Obtener resistencia a partir de la lectura analogica
float mq135_getMQResistance(int raw_adc)
{
  return (((float)RL_VALUE / 1000.0*(4095.0 - raw_adc) / raw_adc));
}

// Obtener concentracion 10^(coord + scope * log (rs/r0)
float mq135_getConcentration(float rs_ro_ratio)
{
  return pow(10, coord + scope * log(rs_ro_ratio));
}