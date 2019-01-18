#include <Arduino.h>
#include <configuration.h>
#include <mqtt.h>
#include <structs.h>
#include <screen.h>
#include <device.h>
#ifdef DEBUG_ENABLED
#include <debugger.h>
#endif

// Setup global variables
#ifdef DEBUG_ENABLED
DEBUGGER *dbg = new DEBUGGER();
#endif
THERMOSTAT *thermostat = new THERMOSTAT();
SCREEN *screen = new SCREEN();
MQTT *mqtt = new MQTT();
DEVICE device;

void setup()
{
    device.setup();
}
void loop()
{
    device.run();
}