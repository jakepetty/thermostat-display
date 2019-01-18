#ifndef STRUCTS_H
#define STRUCTS_H
#include <defs.h>
#include <Arduino.h>
struct THERMOSTAT
{
    uint8_t target;
    uint8_t status = STATE_IDLE;
    uint8_t mode = MODE_OFF;
    uint8_t indoor_temp;
    int8_t outdoor_temp;
    uint8_t condition_icon = WEATHER_CLEAR_DAY;
    uint8_t brightness;
    unsigned long last_ms;
};
extern THERMOSTAT *thermostat;
#endif // STRUCTS_H