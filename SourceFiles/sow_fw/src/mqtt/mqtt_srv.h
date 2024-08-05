#ifndef _MQTT_SRV_H
#define _MQTT_SRV_H
  #include "./main.h"

  void mqtt_srv_init(void);
  void mqtt_srv_reconnect(void);
  void mqtt_srv_loop(void);
  void mqtt_srv_publish(char* topic, char* payload);
#endif