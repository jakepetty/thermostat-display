#include "screen.h"
SCREEN::SCREEN()
{
    display = new SH1106(SCREEN_ADDR, PIN_SDA, PIN_SCL);
    ui = new OLEDDisplayUi(display);
}
void SCREEN::setup()
{
    // Set up the GUI
    ui->setTargetFPS(SCREEN_FPS);
    ui->setFrameAnimation(SLIDE_LEFT);
    ui->setFrames(frames, frameCount);
    ui->setOverlays(overlays, overlaysCount);
    ui->disableAllIndicators();
    ui->init();
#ifdef SCREEN_FLIP
    display->flipScreenVertically();
#endif
    // Display Logo
    display->drawXbm(0, 0, display->width(), display->height(), logo);

    // Display Firmware Version
    display->setFont(ArialMT_Plain_10);
    uint8_t w = display->getStringWidth(VERSION);
    display->drawString(display->width() - w - 4, display->height() - 10, VERSION);
    display->display();
}
void SCREEN::progress(uint8_t _progress, uint8_t _icon, uint8_t _offset)
{
    switch (_icon)
    {
    case STATUS_FLASHING:
        display->drawXbm(0, 0, display->width(), display->height(), caution);
        break;
    }
    display->drawProgressBar(4, (display->height() / 2) + _offset, 120, 8, _progress);
    display->display();
}
void SCREEN::setBrightness(uint8_t _level)
{
    display->setBrightness(_level);
}
void SCREEN::on()
{
    display->displayOn();
}
void SCREEN::off()
{
    display->displayOff();
}
void SCREEN::awaken()
{
    display->setBrightness(SCREEN_MAX_BRIGHTNESS);
    last_ms = millis();
    awake = true;
}
bool SCREEN::isLoaded()
{
    return loaded;
}
void SCREEN::startDisplay()
{
    loaded = true;
}
void SCREEN::statusIcon(const __FlashStringHelper *_msg, uint8_t _state)
{
    setBrightness(SCREEN_MAX_BRIGHTNESS);
    showMessage = true;
    last_ms = millis();
    display->clear();
    switch (_state)
    {
    case STATUS_SUCCESS:
        display->drawXbm(0, 0, display->width(), display->height(), success);
        break;
    case STATUS_FAILED:
        display->drawXbm(0, 0, display->width(), display->height(), failed);
        break;
    }
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    display->drawString(display->width() / 2, (display->height() / 2) + 15, _msg);
    display->display();
}
void SCREEN::message(const __FlashStringHelper *_msg, int8_t _voffset)
{
    setBrightness(SCREEN_MAX_BRIGHTNESS);
    showMessage = true;
    last_ms = millis();
    display->clear();
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
    display->drawString(display->width() / 2, (display->height() / 2) + _voffset, _msg);
    display->display();
}
void SCREEN::message(const __FlashStringHelper *_msg)
{
    message(_msg, 0);
}
uint8_t SCREEN::run()
{
    unsigned long ms = millis();
    if (showMessage)
    {
        // Return screen to normal operation afer X milliseconds
        if (ms - SCREEN_MSG_DURATION > last_ms)
        {
            setBrightness(SCREEN_MIN_BRIGHTNESS);
            showMessage = false;
        }
    }
    else
    {
        if (awake)
        {
            // Return screen to minimum brightness after X milliseconds
            if (ms - SCREEN_AWAKE_DURATION > last_ms)
            {
                display->setBrightness(SCREEN_MIN_BRIGHTNESS);
                awake = false;
            }
        }
        if (loaded)
        {
            return ui->update();
        }
    }
    return 0;
}
