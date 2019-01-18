#include "device.h"

void DEVICE::setup()
{
#ifdef DEBUG_ENABLED
    delay(2000);
    Serial.begin(SERIAL_BAUD);
    Serial.println();
#endif
    screen->setup();
    wifi.setup();
    mqtt->setup();
    mqtt->client.setCallback([this](char *_topic, byte *_payload, unsigned int _length) {
        mqttCallback(_topic, _payload, _length);
    });
}
void DEVICE::mqttCallback(char *topic, byte *payload, unsigned int length)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &data = jsonBuffer.parseObject(payload);
    DEBUG_PRINT(F("[OK] Received payload from: "), false);
    DEBUG_PRINT(topic, true);

    // Validate the JSON
    if (data.success())
    {
        String callback;
        data.printTo(callback);
#ifdef DEBUG_ENABLED
        DEBUG_PRINT(F("[INFO] "), false);
        DEBUG_PRINT(callback, true);
#endif
        if (strcmp(topic, MQTT_BACKLIGHT_COMMAND_TOPIC.c_str()) == 0) // MQTT Light topic
        {

            // Turns display on or off
            if (data.containsKey("state"))
            {
                if (data["state"] == MQTT_STATE_ON)
                {
                    screen->on();
                }
                if (data["state"] == MQTT_STATE_OFF)
                {
                    screen->off();
                }
            }

            // Sets display brightness
            if (data.containsKey("brightness"))
            {
                screen->setBrightness(data["brightness"]);
            }

            // Sends payload back to HA as confirmation the packet was received
            if (mqtt->client.publish(MQTT_BACKLIGHT_STATE_TOPIC.c_str(), callback.c_str(), MQTT_RETAIN))
            {
                DEBUG_PRINT(F("[OK] Published to: "), false);
            }
            else
            {
                DEBUG_PRINT(F("[ERROR] Failed to publish to: "), false);
            }
            DEBUG_PRINT(MQTT_BACKLIGHT_STATE_TOPIC, true);
        }
        else if (strcmp(topic, MQTT_HOME_ASSISTANT_COMMAND.c_str()) == 0) // Device topic
        {
            // Sets indoor temperature
            if (data.containsKey("indoor_temp"))
            {
                thermostat->indoor_temp = data["indoor_temp"];
            }

            // Sets operational status
            if (data.containsKey("status"))
            {
                uint8_t status = STATE_IDLE;
                if (data["status"] == F("off"))
                {
                    status = STATE_OFF;
                }
                else if (data["status"] == F("idle"))
                {
                    status = STATE_IDLE;
                }
                else if (data["status"] == F("heat"))
                {
                    status = STATE_HEAT;
                }
                else if (data["status"] == F("cool"))
                {
                    status = STATE_COOL;
                }
                if (status != thermostat->status)
                {
                    if (screen->isLoaded())
                    {
                        screen->awaken();
                    }
                    thermostat->status = status;
                }
            }

            // Sets Current Mode
            if (data.containsKey("mode"))
            {
                uint8_t mode = MODE_OFF;
                if (data["mode"] == F("heat"))
                {
                    mode = MODE_HEAT;
                }
                else if (data["mode"] == F("cool"))
                {
                    mode = MODE_COOL;
                }
                if (mode != thermostat->mode)
                {
                    thermostat->mode = mode;
                }
            }

            // Sets target temperature
            if (data.containsKey("target_temp"))
            {
                thermostat->target = data["target_temp"];
            }

            // Sets outdoor temperature
            if (data.containsKey("outdoor_temp"))
            {
                thermostat->outdoor_temp = data["outdoor_temp"];
            }

            // Sets Weather Icon
            if (data.containsKey("condition_icon"))
            {
                String ico = data["condition_icon"];
                char condition_icon = WEATHER_UNKNOWN;
                if (ico == F("clear-day"))
                {
                    condition_icon = WEATHER_CLEAR_DAY;
                }
                else if (ico == F("clear-night"))
                {
                    condition_icon = WEATHER_CLEAR_NIGHT;
                }
                else if (ico == F("snow"))
                {
                    condition_icon = WEATHER_SNOW;
                }
                else if (ico == F("sleet") || ico == F("hail"))
                {
                    condition_icon = WEATHER_SLEET;
                }
                else if (ico == F("rain"))
                {
                    condition_icon = WEATHER_RAIN;
                }
                else if (ico == F("fog"))
                {
                    condition_icon = WEATHER_FOG;
                }
                else if (ico == F("cloudy"))
                {
                    condition_icon = WEATHER_CLOUDY;
                }
                else if (ico == F("partly-cloudy-day"))
                {
                    condition_icon = WEATHER_PARTLY_CLOUDY_DAY;
                }
                else if (ico == F("partly-cloudy-night"))
                {
                    condition_icon = WEATHER_PARTLY_CLOUDY_NIGHT;
                }
                else if (ico == F("thunderstorm"))
                {
                    condition_icon = WEATHER_THUNDERSTORM;
                }
                else if (ico == F("wind"))
                {
                    condition_icon = WEATHER_WIND;
                }
                thermostat->condition_icon = condition_icon;
            }

            // Sets clock
            if (data.containsKey("time"))
            {
                if (timeStatus() != timeSet)
                {
                    setTime(data["time"]);
                }
            }

            // Reboots Device
            if (data.containsKey("restart"))
            {
                screen->message(F("Rebooting"));
                ESP.restart();
            }

            // Initiates the display
            if (!screen->isLoaded())
            {
                screen->startDisplay();
                screen->awaken();
            }
        }
    }
    else
    {
        DEBUG_PRINT(F("[ERROR] Invalid JSON payload"), true);
    }
}
void DEVICE::run()
{
    if (wifi.run())
    {
        mqtt->run();
    }
    screen->run();
#ifdef DEBUG_ENABLED
    dbg->run();
#endif
}