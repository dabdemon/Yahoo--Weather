#define MyTupletCString(_key, _cstring) ((const Tuplet) { .type = TUPLE_CSTRING, .key = _key, .cstring = { .data = _cstring, .length = strlen(_cstring) + 1 }})
	
#define WEEKDAY_FRAME    (GRect(5, 2, 102, 168-145)) //,,95,
#define BATT_FRAME       (GRect(103, 3, 40, 168-146)) //98,,
#define BT_FRAME         (GRect(127, 3, 23, 168-146))
#define TIME_FRAME       (GRect(0, 15, 144, 168-16))
#define DATE_FRAME       (GRect(1, 70, 139, 168-62))
	//YWeather 2.3 - REQ01. Display Seconds - START
#define TIME_FRAME2      (GRect(0, 15, 116, 168-16))
#define SECONDS_FRAME    (GRect(117, 50, 32, 22))
#define AMPM_FRAME    (GRect(117, 40, 32, 22))
	//YWeather 2.3 - REQ01. Display Seconds - END
	//YWeather 2.3 - REQ02. Hourly Vibe - START
//#define HourlyVibe_FRAME    (GRect(120, 28, 15, 9))
	//YWeather 2.3 - REQ02. Hourly Vibe - END

	
//#define CHIN_WEEKDAY_FRAME    (GRect(5, 2, 60, 168-145)) //,,95,
#define CHIN_WEEKDAY_FRAME    (GRect(5, 2, 110, 168-145)) //,,95,
/*
#define MAX_FRAME (GRect(65, 90, 40, 168-145))
#define MIN_FRAME (GRect(105, 90, 40, 168-145))
*/
        
#define LAST_UPDATE_FRAME (GRect(110, 148, 34, 168-145)) //xStart, yStart, xLength, yLength
#define LOCATION_FRAME    (GRect(1, 148, 110, 168-145))
#define WEATHER_FRAME     (GRect(5, 90, 60, 60))
#define TEMPERATURE_FRAME (GRect(58, 95, 94, 60))
	
//#define HIGH_FRAME (GRect(40, 95, 41, 168-108))
#define LOW_FRAME (GRect(100, 93, 47, 168-108))
#define LOW_ICON_FRAME (GRect(81, 92, 26, 26))
	
#define HIGH_FRAME (GRect(100, 115, 47, 168-108))
#define HIGH_ICON_FRAME (GRect(81, 115, 26, 26))

#define SUNRISE_FRAME (GRect(30, 95, 50, 168-108))
#define SUNRISE_ICON_FRAME (GRect(1, 98, 26, 17))

#define SUNSET_FRAME (GRect(30, 115, 50, 168-108))
#define SUNSET_ICON_FRAME (GRect(1, 118, 26, 17))
	
#define WIND_FRAME (GRect(30, 135, 50, 168-108))
#define WIND_ICON_FRAME (GRect(1, 138, 26, 26))
	
#define WDIRECTION_FRAME (GRect(30, 155, 50, 168-108))
        
#define TOTAL_MOON_DIGITS 1
#define MOON_ICON_FRAME (GRect(106, 138, 26, 26))
	
#define POP_FRAME (GRect(100, 135, 45, 168-108))
#define RAIN_ICON_FRAME (GRect(81, 135, 26, 26))	

//define 3 days forecast
#define FORECAST_DAY1_FRAME (GRect(5, 93, 92, 23))
#define FORECAST_DAY2_FRAME (GRect(5, 114, 92, 23))
#define FORECAST_DAY3_FRAME (GRect(5, 135, 92, 23))	
	
#define FORECAST_CODE1_FRAME (GRect(97, 93, 22, 22))
#define FORECAST_CODE2_FRAME (GRect(97, 114, 22, 22))
#define FORECAST_CODE3_FRAME (GRect(97, 135, 22, 22))

//#define FORECAST_HIGH1_FRAME (GRect(81, 93, 47, 60))
//#define FORECAST_HIGH2_FRAME (GRect(81, 115, 47, 60))
//#define FORECAST_HIGH3_FRAME (GRect(81, 135, 47, 60))
#define FORECAST_HIGH1_FRAME (GRect(100, 103, 45, 60))
#define FORECAST_HIGH2_FRAME (GRect(100, 125, 45, 60))
#define FORECAST_HIGH3_FRAME (GRect(100, 145, 45, 60))	

//#define FORECAST_LOW1_FRAME (GRect(100, 93, 47, 60))
#define FORECAST_LOW1_FRAME (GRect(100, 93, 45, 60))
#define FORECAST_LOW2_FRAME (GRect(100, 115, 45, 60))
#define FORECAST_LOW3_FRAME (GRect(100, 135, 45, 60))