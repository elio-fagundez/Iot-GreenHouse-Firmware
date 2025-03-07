#ifndef _MQ135_H
#define _MQ135_H
#include "./main.h"

void mq135_init(int do_pin, int ao_pin);
float mq135_ao_get(void);
bool mq135_do_get(void);
float mq135_readMQ(void);
float mq135_getMQResistance(int raw_adc);
float mq135_getConcentration(float rs_ro_ratio);

#endif