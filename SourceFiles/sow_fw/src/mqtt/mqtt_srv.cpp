#include "mqtt_srv.h"

void callback(char* topic, byte* message, unsigned int length)
{
  SERIAL_MON.print("Message arrived on topic: ");
  SERIAL_MON.print(topic);
  SERIAL_MON.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++)
  {
    SERIAL_MON.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  SERIAL_MON.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "esp32/output")
  {
    SERIAL_MON.print("Changing output to ");
    if(messageTemp == "on")
    {
      SERIAL_MON.println("on");
    }
    else if(messageTemp == "off")
    {
      SERIAL_MON.println("off");
    }
  }
}

void mqtt_srv_init(void)
{
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
}

void mqtt_srv_reconnect(void)
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    SERIAL_MON.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32-C6 Client"))
    {
      SERIAL_MON.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else
    {
      SERIAL_MON.print("failed, rc=");
      SERIAL_MON.print(client.state());
      SERIAL_MON.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqtt_srv_loop(void)
{
  if (!client.connected())
  {
    mqtt_srv_reconnect();
  }
  client.loop();
}

void mqtt_srv_publish(char* topic, char* payload)
{
  if (!client.connected())
  {
    mqtt_srv_reconnect();
  }
  client.publish(topic, payload);
}
