#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <OLEDDisplayUi.h>
#include "ESP8266Wifi.h"
#include "structs.h"
#include "configuration.h"
#include "defs.h"
#include "icons.h"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-function"

static void overlay(OLEDDisplay *display, OLEDDisplayUiState *state)
{
    // Setup backdrop
    display->drawXbm(0, 0, display->width(), display->height(), background);

    // Signol Strength Indicator
    uint8_t rssi = abs(WiFi.RSSI());
    const unsigned char *icon;
    if (rssi >= 90)
    {
        icon = ICON_WIFI_0;
    }
    else if (rssi >= 80)
    {
        icon = ICON_WIFI_20;
    }
    else if (rssi >= 75)
    {
        icon = ICON_WIFI_40;
    }
    else if (rssi >= 70)
    {
        icon = ICON_WIFI_60;
    }
    else if (rssi >= 65)
    {
        icon = ICON_WIFI_80;
    }
    else if (rssi < 65)
    {
        icon = ICON_WIFI_100;
    }
    display->drawXbm(WIFI_ICON_OFFSET_X, WIFI_ICON_OFFSET_Y, WIFI_ICON_WIDTH, WIFI_ICON_HEIGHT, icon);

    // Weather Icon
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->setFont(Meteocons_Regular_8);
    display->drawString(display->width() - WEATHER_ICON_OFFSET_X, WEATHER_ICON_OFFSET_Y, String((char)thermostat->condition_icon));

    // Outdoor Temperature
    display->setFont(Open_Sans_Regular_12);
    display->drawString(display->width() - OUTDOOR_TEMP_OFFSET_X, OUTDOOR_TEMP_OFFSET_Y, String(thermostat->outdoor_temp));

    // Target Temperature
    display->setFont(Open_Sans_Regular_12);
    display->drawString(TARGET_TEMP_OFFSET_X, display->height() - TARGET_TEMP_OFFSET_Y, String(thermostat->target));

    // Thermostat Mode
    switch (thermostat->status)
    {
    case STATE_HEAT:
        display->drawXbm(display->width() - HEAT_ICON_WIDTH - HEAT_ICON_OFFSET, display->height() - HEAT_ICON_HEIGHT - HEAT_ICON_OFFSET, HEAT_ICON_WIDTH, HEAT_ICON_HEIGHT, ICON_HEAT);
        break;
    case STATE_COOL:
        display->drawXbm(display->width() - COOL_ICON_WIDTH - COOL_ICON_OFFSET, display->height() - COOL_ICON_HEIGHT - COOL_ICON_OFFSET, COOL_ICON_WIDTH, COOL_ICON_HEIGHT, ICON_COOL);
        break;
    case STATE_IDLE:
        display->drawXbm(display->width() - IDLE_ICON_WIDTH - IDLE_ICON_OFFSET, display->height() - IDLE_ICON_HEIGHT - IDLE_ICON_OFFSET, IDLE_ICON_WIDTH, IDLE_ICON_HEIGHT, ICON_IDLE);
        break;
    }
}
static void indoor(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    // Indoor Temperature
    display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    display->setFont(Open_Sans_Regular_32);
    display->drawString((display->width() / 2) + x, (display->height() / 2) + y, String(thermostat->indoor_temp));
}

static void digital_clock(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    display->setFont(Open_Sans_Regular_32);
    uint8_t m = minute();
    uint8_t h = hourFormat12();
    display->drawString((display->getWidth() / 2) + x, (display->getHeight() / 2) + y, String(h) + ":" + String(m < 10 ? "0" + String(m) : m));
}
static int overlaysCount = 1;
static int frameCount = 2;
static FrameCallback frames[] = {digital_clock, indoor};
static OverlayCallback overlays[] = {overlay};
#endif // INTERFACE_H_