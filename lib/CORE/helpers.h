/**
 * DO NOT MODIFY THIS FILE
*/
#ifndef HELPERS_H_
#define HELPERS_H_
#pragma GCC diagnostic ignored "-Wunused-function"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <configuration.h>
#include <debugger.h>
// Generates a unique ID using devices MAC Address
static String getUniqueID()
{
    String callback = WiFi.macAddress(); // Format: XX:XX:XX:XX:XX:XX
    callback.replace(":", "");           // Converts XX:XX:XX:XX:XX:XX to XXXXXXXXXXXX
    callback.toLowerCase();              // Converts XXXXXXXXXXXX to xxxxxxxxxxxx
    return callback;                     // Returns xxxxxxxxxxxx
}

// Debugging functions
#ifdef DEBUG_ENABLED
#define DEBUG_PRINT_S(a, b) b ? Serial.println(a) : Serial.print(a)
#define DEBUG_PRINT(a, b) dbg->send(a, b)
#else
#define DEBUG_PRINT_S(a, b)
#define DEBUG_PRINT(a, b)
#endif

// MQTT Payload to String converter
static String payload2string(byte *payload, unsigned int len)
{
    payload[len] = '\0';
    return String((char *)payload);
}

#endif // HELPERS_H_
