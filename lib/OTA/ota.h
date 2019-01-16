#ifndef OTA_H_
#define OTA_H_

#include <configuration.h>
#include <helpers.h>
#include <discovery.h>
#include <screen.h>
#include <ArduinoOTA.h>
class OTA
{
public:
  void run();
  void setup();

private:
  int8_t _err = -1;
};
#endif // OTA_H_
