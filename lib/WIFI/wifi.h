/**
 * DO NOT MODIFY THIS FILE
*/
#ifndef WIFI_H_
#define WIFI_H_
#include <Arduino.h>
#include <helpers.h>
#include <discovery.h>
#include <ESP8266WiFi.h>
#include <configuration.h>
#include <ESP8266mDNS.h>
#ifdef DEBUG_ENABLED
#include <debugger.h>
#endif
#ifdef OTA_ENABLED
#include <ota.h>
#endif
class WIFI
{
public:
  void setup();
  bool run();

private:
  uint8_t last_status;

#ifdef OTA_ENABLED
  OTA ota;
#endif
};
#endif // WIFI_H_