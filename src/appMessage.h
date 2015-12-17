#pragma once
#include <pebble.h>

#define MyTupletCString(_key, _cstring) ((const Tuplet) { .type = TUPLE_CSTRING, .key = _key, .cstring = { .data = _cstring, .length = strlen(_cstring) + 1 }})

enum WeatherKey {
	WEATHER_ICON_KEY = 0,         	//TUPLE_INT
	WEATHER_TEMPERATURE_KEY = 1,  	//TUPLE_CSTRING
	WEATHER_CITY_KEY = 2, 			//TUPLE_CSTRING
	WEATHER_LAST_UPDATE = 33,		//CSTRING
	INVERT_COLOR_KEY = 3, 			//TUPLE_INT
	language_key = 4, 				//TUPLE_INT
	VIBES_KEY = 5, 					//TUPLE_INT
//Forecast for the day
	WEATHER_HIGH_KEY = 6, 			//TUPLE_CSTRING
	WEATHER_LOW_KEY = 7, 			//TUPLE_CSTRING
	SUNRISE_KEY = 8, 				//TUPLE_CSTRING
	SUNSET_KEY = 9, 				//TUPLE_CSTRING
	WIND_KEY = 10, 					//TUPLE_CSTRING
	WDIRECTION_KEY = 11, 			//TUPLE_INT
//3 day forecast
	FORECAST_CODE1_KEY = 12, 		//TUPLE_INT
	FORECAST_HIGH1_KEY = 13, 		//TUPLE_CSTRING
	FORECAST_LOW1_KEY = 14, 		//TUPLE_CSTRINT
	FORECAST_CODE2_KEY = 15, 		//TUPLE_INT
	FORECAST_HIGH2_KEY = 16, 		//TUPLE_CSTRING
	FORECAST_LOW2_KEY = 17, 		//TUPLE_CSTRING
	FORECAST_CODE3_KEY = 18, 		//TUPLE_INT
	FORECAST_HIGH3_KEY = 19, 		//TUPLE_CSTRING
	FORECAST_LOW3_KEY = 20, 		//TUPLE_CSTRING
//Extra Features
	EXTRA_ESDURATION_KEY = 21, 		//TUPLE_INT
	EXTRA_TIMER_KEY = 22, 			//TUPLE_INT
	EXTRA_FORECAST_KEY = 23, 		//TUPLE_INT
	DISPLAY_SECONDS_KEY = 24, 		//TUPLE_INT
	HOURLY_VIBE_KEY = 25, 			//TUPLE_INT
	HOURLY_VIBE_START_KEY = 26, 	//INT
	HOURLY_VIBE_END_KEY = 27, 		//INT
	HIDE_BAT_KEY = 28, 				//INT
	FONT_KEY = 29, 					//INT
	BACKLIGHT_KEY = 30, 			//INT
	POP_KEY = 31, 					//CSTRING
	THEME_KEY = 32, 				//INT
};

static void sync_tuple_changed_callback(const uint32_t key,
                                        const Tuple* new_tuple,
                                        const Tuple* old_tuple,
                                        void* context);
void SetupMessages();
void loadInitialTuples();
void unloadInitialTuples();