#include "ota.h"

void OTA::setup()
{
    ArduinoOTA.setPort(OTA_PORT);
    ArduinoOTA.setHostname(MQTT_DEVICE_NAME.c_str());
    ArduinoOTA.setPassword(OTA_PASS);
    ArduinoOTA.onStart([this]() {
        DEBUG_PRINT(F("Beginning OTA"), true);
        screen->message(F("Updating Firmware"), 0);
    });
    ArduinoOTA.onEnd([this]() {
        DEBUG_PRINT(F("OTA Complete"), true);
        screen->statusIcon(F("Rebooting"), STATUS_SUCCESS);
    });
    ArduinoOTA.onProgress([this](unsigned int _progress, unsigned int _total) {
        int prog = (_progress / (_total / 100));
        DEBUG_PRINT(F("Uploading... "), false);
        DEBUG_PRINT(prog, false);
        DEBUG_PRINT(F("%"), true);
        screen->progress(prog, STATUS_FLASHING, 10);
    });
    ArduinoOTA.onError([this](ota_error_t _error) {
        // BUG: Unable to access SCREEN class within this function so we define a variable instead for later use
        _err = _error;
    });
    ArduinoOTA.begin();
}
void OTA::run()
{
    // onError Workaround
    switch (_err)
    {
    case OTA_AUTH_ERROR:
        screen->statusIcon(F("Authentication failed"), STATUS_FAILED);
        break;
    case OTA_BEGIN_ERROR:
        screen->statusIcon(F("Data Failed"), STATUS_FAILED);
        break;
    case OTA_CONNECT_ERROR:
        screen->statusIcon(F("Connection Failed"), STATUS_FAILED);
        break;
    case OTA_RECEIVE_ERROR:
        screen->statusIcon(F("Communication Failed"), STATUS_FAILED);
        break;
    case OTA_END_ERROR:
        screen->statusIcon(F("Transfer Failed"), STATUS_FAILED);
        break;
    }
    _err = -1;
    ArduinoOTA.handle();
}