/**
 * DO NOT MODIFY THIS FILE
*/
#include <mqtt.h>
MQTT::MQTT() : client(espClient)
{
}
void MQTT::setup()
{
    client.setServer(MQTT_HOST, MQTT_PORT);
}
void MQTT::setupDiscovery()
{
    DynamicJsonBuffer buffer;
    JsonObject &data = buffer.createObject();
    // Light
    data["name"] = MQTT_DEVICE_NAME;
    data["schema"] = "json";
    data["command_topic"] = MQTT_BACKLIGHT_COMMAND_TOPIC;
    data["state_topic"] = MQTT_BACKLIGHT_STATE_TOPIC;
    data["availability_topic"] = MQTT_AVAILABILITY_TOPIC;
    data["state_on"] = MQTT_STATE_ON;
    data["state_off"] = MQTT_STATE_OFF;
    data["payload_on"] = MQTT_STATE_ON;
    data["payload_off"] = MQTT_STATE_OFF;
    data["brightness"] = true;
    data["brightness_scale"] = SCREEN_MAX_BRIGHTNESS;
    data["retain"] = MQTT_RETAIN;
    data["qos"] = MQTT_QOS;

    String config;
    data.printTo(config);
    if (client.publish(MQTT_BACKLIGHT_CONFIG_TOPIC.c_str(), config.c_str(), MQTT_RETAIN)) // Publish Discoery Configuration
    {
        DEBUG_PRINT(F("[OK] Entity ID: light."), false);
        DEBUG_PRINT(MQTT_DEVICE_NAME, false);
        DEBUG_PRINT(F(" has been setup"), true);
        DEBUG_PRINT(F("[OK] Published to: "), false);
    }
    else
    {
        DEBUG_PRINT(F("[ERROR] Unable to publish to: "), false);
    }
    DEBUG_PRINT(MQTT_BACKLIGHT_CONFIG_TOPIC, true);
    if (!MQTT_RETAIN)
    {
        DynamicJsonBuffer buf;
        JsonObject &obj = buf.createObject();
        obj["state"] = MQTT_STATE_ON;
        obj["brightness"] = SCREEN_MIN_BRIGHTNESS;
        String pl;
        obj.printTo(pl);
        if (client.publish(MQTT_BACKLIGHT_STATE_TOPIC.c_str(), pl.c_str()))
        {
            DEBUG_PRINT(F("[OK] Published to: "), false);
        }
        else
        {
            DEBUG_PRINT(F("[ERROR] Unable to publish to: "), false);
        }
        DEBUG_PRINT(MQTT_BACKLIGHT_STATE_TOPIC, true);
    }

    if (client.subscribe(MQTT_BACKLIGHT_COMMAND_TOPIC.c_str(), MQTT_QOS)) // Subscribe to Command Topic
    {
        DEBUG_PRINT(F("[OK] Subscribed to: "), false);
    }
    else
    {
        DEBUG_PRINT(F("[ERROR] Unable to subscribe to: "), false);
    }
    DEBUG_PRINT(MQTT_BACKLIGHT_COMMAND_TOPIC, true);
}

bool MQTT::run()
{
    bool connected = client.connected();
    if (!connected)
    {
        if (client.connect(MQTT_DEVICE_NAME.c_str(), MQTT_USER, MQTT_PASS, MQTT_AVAILABILITY_TOPIC.c_str(), MQTT_QOS, MQTT_RETAIN, MQTT_WILL_OFFLINE, MQTT_CLEAN_SESSION))
        {
            DEBUG_PRINT(F("[OK] Connected to MQTT Server"), true);
            if (!client.publish(MQTT_AVAILABILITY_TOPIC.c_str(), MQTT_WILL_ONLINE, MQTT_RETAIN))
            {
                DEBUG_PRINT(F("[ERROR] Unable to publish to: "), false);
                DEBUG_PRINT(MQTT_AVAILABILITY_TOPIC, true);
            }
            // Setup MQTT Discovery Configurations
            setupDiscovery();
            if (client.subscribe(MQTT_HOME_ASSISTANT_COMMAND.c_str(), MQTT_QOS)) // Subscribe to Command Topic
            {
                DEBUG_PRINT(F("[OK] Subscribed to: "), false);
            }
            else
            {
                DEBUG_PRINT(F("[ERROR] Unable to subscribe to: "), false);
            }
            DEBUG_PRINT(MQTT_HOME_ASSISTANT_COMMAND, true);
        }
        else
        {
            DEBUG_PRINT(F("[ERROR] Unable to connect to MQTT Server"), true);
        }
    }
    client.loop();
    return connected;
}