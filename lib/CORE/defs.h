#ifndef DEFS_H_
#define DEFS_H_
#define STATUS_FAILED 0x00
#define STATUS_SUCCESS 0x01
#define STATUS_FLASHING 0x02

// STATES
#define STATE_OFF 0
#define STATE_IDLE 1
#define STATE_HEAT 2
#define STATE_COOL 3

// Weather Definitions
#define WEATHER_CLEAR_DAY 0x42
#define WEATHER_CLEAR_NIGHT 0x43
#define WEATHER_WIND 0x46
#define WEATHER_FOG 0x45
#define WEATHER_RAIN 0x52
#define WEATHER_SLEET 0x58
#define WEATHER_SNOW 0x57
#define WEATHER_CLOUDY 0x4e
#define WEATHER_THUNDERSTORM 0x30
#define WEATHER_PARTLY_CLOUDY_DAY 0x48
#define WEATHER_PARTLY_CLOUDY_NIGHT 0x49
#define WEATHER_OVERCAST 0x59
#define WEATHER_THERMOMOMETER 0x27
#define WEATHER_UNKNOWN 0x29

#endif // DEFS_H_