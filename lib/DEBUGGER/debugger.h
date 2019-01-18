#ifndef DEBUGGER_H_
#define DEBUGGER_H_
#include <configuration.h>
#ifdef DEBUG_ENABLED
#include <Arduino.h>
#include <WiFiUdp.h>
#include <helpers.h>
#include <ESP8266WiFi.h>
class DEBUGGER
{
  public:
    void setup();
    void run();
    void setIgnore(bool);
    void send(int &, bool);
    void send(IPAddress &, bool);
    void send(IPAddress, bool);
    void send(const char *, bool);
    void send(const String &, bool);
    void send(const __FlashStringHelper *, bool);

  private:
    String payload;
    WiFiUDP server;
    bool init;
    bool ignore;
};
extern DEBUGGER *dbg;
#endif
#endif // DEBUGGER_H_