#include "mqtt_srv.h"

String Read_rootca;
String Read_cert;
String Read_privatekey;

byte mac[6];
char mac_Id[18];

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
  if (!LittleFS.begin(true))
  {
    SERIAL_MON.println("Se ha producido un error al montar LittleFS");
    return;
  }

  //**********************
  //Root CA leer archivo.
  File file2 = LittleFS.open(FILE__PEM, "r");
  if (!file2)
  {
    SERIAL_MON.println("No se pudo abrir el archivo para leerlo");
    return;
  }
  SERIAL_MON.println("Root CA File Content:");
  while (file2.available())
  {
    Read_rootca = file2.readString();
    SERIAL_MON.println(Read_rootca);
  }
  //*****************************
  // Cert leer archivo
  File file4 = LittleFS.open(FILE__PEM__CRT, "r");
  if (!file4)
  {
    SERIAL_MON.println("No se pudo abrir el archivo para leerlo");
    return;
  }
  SERIAL_MON.println("Cert File Content:");
  while (file4.available())
  {
    Read_cert = file4.readString();
    SERIAL_MON.println(Read_cert);
  }
  //***************************************
  //Privatekey leer archivo
  File file6 = LittleFS.open(FILE__PEM__KEY, "r");
  if (!file6)
  {
    SERIAL_MON.println("No se pudo abrir el archivo para leerlo");
    return;
  }
  SERIAL_MON.println("privateKey contenido:");
  while (file6.available())
  {
    Read_privatekey = file6.readString();
    SERIAL_MON.println(Read_privatekey);
  }
  //=====================================================

  char* pRead_rootca;
  pRead_rootca = (char *)malloc(sizeof(char) * (Read_rootca.length() + 1));
  strcpy(pRead_rootca, Read_rootca.c_str());

  char* pRead_cert;
  pRead_cert = (char *)malloc(sizeof(char) * (Read_cert.length() + 1));
  strcpy(pRead_cert, Read_cert.c_str());

  char* pRead_privatekey;
  pRead_privatekey = (char *)malloc(sizeof(char) * (Read_privatekey.length() + 1));
  strcpy(pRead_privatekey, Read_privatekey.c_str());

  SERIAL_MON.println("================================================================================================");
  SERIAL_MON.println("Certificados que pasan adjuntan al espClient");
  SERIAL_MON.println();
  SERIAL_MON.println("Root CA:");
  SERIAL_MON.write(pRead_rootca);
  SERIAL_MON.println("================================================================================================");
  SERIAL_MON.println();
  SERIAL_MON.println("Cert:");
  SERIAL_MON.write(pRead_cert);
  SERIAL_MON.println("================================================================================================");
  SERIAL_MON.println();
  SERIAL_MON.println("privateKey:");
  SERIAL_MON.write(pRead_privatekey);
  SERIAL_MON.println("================================================================================================");

  espClient.setCACert(pRead_rootca);
  espClient.setCertificate(pRead_cert);
  espClient.setPrivateKey(pRead_privatekey);

  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  WiFi.macAddress(mac);
  snprintf(mac_Id, sizeof(mac_Id), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  SERIAL_MON.println(mac_Id);
  delay(2000);
}

void mqtt_srv_reconnect(void)
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    SERIAL_MON.print("Attempting MQTT connection...");
    // Attempt to connect
    // Creando un ID como ramdon
    String clientId = "ESP32-C6-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str()))
    {
      SERIAL_MON.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
      client.publish("ei_out", "hello world");
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
