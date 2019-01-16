/**
 * DO NOT MODIFY THIS FILE
*/
#ifndef MQTT_H_
#define MQTT_H_
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <configuration.h>
#include <ArduinoJson.h>
#include <helpers.h>
#include <discovery.h>
class MQTT : PubSubClient
{
public:
  MQTT();
  void setup();
  bool run();
  WiFiClient espClient;
  PubSubClient client;

private:
  void setupDiscovery();
};
extern MQTT *mqtt;
#endif // MQTT_H_