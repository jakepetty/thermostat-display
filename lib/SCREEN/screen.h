#ifndef SCREEN_H_
#define SCREEN_H_

#include <configuration.h>
#include <TimeLib.h>
#include <SH1106.h>
#include <fonts.h>
#include <images.h>
#include <icons.h>
#include <structs.h>
#include <OLEDDisplayUi.h>
#include <interface.h>
#include <pin_mapping.h>
class SCREEN
{
public:
  SCREEN();
  void setup();
  uint8_t run();
  void on();
  void off();
  bool isLoaded();
  void startDisplay();
  void awaken();
  void progress(uint8_t, uint8_t, uint8_t);
  void statusIcon(const __FlashStringHelper *, uint8_t);
  void message(const __FlashStringHelper *);
  void message(const __FlashStringHelper *, int8_t);
  void setBrightness(uint8_t);
  SH1106 *display;

private:
  unsigned long last_ms;
  bool awake = false;
  bool showMessage = false;
  bool loaded = false;
  OLEDDisplayUi *ui;
};
extern SCREEN *screen;
#endif // SCREEN_H_
