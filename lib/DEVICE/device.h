#ifndef DEVICE_H_
#define DEVICE_H_

#include <configuration.h>
#include <helpers.h>
#include <mqtt.h>
#include <wifi.h>
#include <TimeLib.h>
#include <structs.h>
#include <ArduinoJson.h>
#ifdef DEBUG_ENABLED
#include <debugger.h>
#endif

class DEVICE
{
public:
  void setup();
  void run();

private:
  WIFI wifi;
  void mqttCallback(char *topic, byte *payload, unsigned int length);
};
#endif // DEVICE_H_
