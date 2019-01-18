/**
 * DO NOT MODIFY THIS FILE
*/
#include "wifi.h"
void WIFI::setup()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    WiFi.setAutoReconnect(true);
}
bool WIFI::run()
{
    uint8_t status = WiFi.status();
    if (last_status != status)
    {
        switch (status)
        {
        case WL_NO_SSID_AVAIL:
            DEBUG_PRINT(F("[ERROR] Unable to reach SSID"), true);
            break;
        case WL_CONNECT_FAILED:
            DEBUG_PRINT(F("[ERROR] WIFI Connection Failed"), true);
            break;
        case WL_CONNECTED:
#ifdef DEBUG_ENABLED
            dbg->setup();
#endif
            DEBUG_PRINT(F("[OK] WIFI Connected: "), false);
            DEBUG_PRINT(WiFi.localIP(), true);
#ifdef OTA_ENABLED
            ota.setup();
#endif
            if (MDNS.begin(MQTT_DEVICE_NAME.c_str()))
            {
                MDNS.addService("_rdebug", "_udp", 8461);
                DEBUG_PRINT(F("[OK] MDNS responder started"), true);
            }
            else
            {
                DEBUG_PRINT(F("[ERROR] Unable to start MDNS responder"), true);
            }
            break;
        case WL_DISCONNECTED:
            DEBUG_PRINT(F("[WARN] WIFI Disconnected"), true);
            break;
        case WL_CONNECTION_LOST:
            DEBUG_PRINT(F("[WARN] WIFI signal lost"), true);
            WiFi.reconnect();
            break;
        }
        last_status = status;
    }
#ifdef OTA_ENABLED
    ota.run();
#endif
    return status == WL_CONNECTED;
}