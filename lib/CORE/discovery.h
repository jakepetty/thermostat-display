#ifndef DISCOVERY_H_
#define DISCOVERY_H_
#include <Arduino.h>
#include <helpers.h>
#include <configuration.h>
const String MQTT_DEVICE_NAME = getUniqueID();

// Backlight
const String MQTT_BACKLIGHT_BASE = MQTT_DISCOVERY_PREFIX "/light/" + MQTT_DEVICE_NAME;
const String MQTT_BACKLIGHT_COMMAND_TOPIC = MQTT_BACKLIGHT_BASE + "/command";
const String MQTT_BACKLIGHT_STATE_TOPIC = MQTT_BACKLIGHT_BASE + "/state";
const String MQTT_BACKLIGHT_CONFIG_TOPIC = MQTT_BACKLIGHT_BASE + "/config";
const String MQTT_AVAILABILITY_TOPIC = MQTT_BACKLIGHT_BASE + "/status";

// Home Assistant Automation
const String MQTT_HOME_ASSISTANT_COMMAND = MQTT_DEVICE_NAME + "/command";

#endif // DISCOVERY_H_