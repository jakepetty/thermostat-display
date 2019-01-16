#include <Arduino.h>
#include <mqtt.h>
#include <structs.h>
#include <screen.h>
#include <device.h>

// Setup global variables
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