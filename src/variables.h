//*************//
// Define KEYS //
//*************//

enum WeatherKey {
	WEATHER_ICON_KEY = 0, // 0x0,        // TUPLE_INT
	WEATHER_TEMPERATURE_KEY = 1, // 0x1, // TUPLE_CSTRING
	WEATHER_CITY_KEY = 2, //0x2,        //	TUPLE_CSTRING
	INVERT_COLOR_KEY = 3, //0x3,  		 // TUPLE_INT
	language_key = 4, //0x4, 			// TUPLE_INT
	VIBES_KEY = 5, //0x5,  		 // TUPLE_INT
//Forecast for the day
	WEATHER_HIGH_KEY = 6, //0x6,	//TUPLE_CSTRING
	WEATHER_LOW_KEY = 7, //0x7,	//TUPLE_CSTRING
	SUNRISE_KEY = 8, //0x8, //TUPLE_CSTRING
	SUNSET_KEY = 9, //0x9, //TUPLE_CSTRING
	WIND_KEY = 10, //0xa, //TUPLE_CSTRING
	WDIRECTION_KEY = 11, //0xb, //TUPLE_INT
//3 day forecast
	FORECAST_CODE1_KEY = 12, //0xc, //TUPLE_INT
	FORECAST_HIGH1_KEY = 13, //0xd, //TUPLE_CSTRING
	FORECAST_LOW1_KEY = 14, //0xe, //TUPLE_CSTRINT
	FORECAST_CODE2_KEY = 15, //0xf, //TUPLE_INT
	FORECAST_HIGH2_KEY = 16, //0x10, //TUPLE_CSTRING
	FORECAST_LOW2_KEY = 17, //0x11, //TUPLE_CSTRING
	FORECAST_CODE3_KEY = 18, //0x12, //TUPLE_INT
	FORECAST_HIGH3_KEY = 19, //0x13, //TUPLE_CSTRING
	FORECAST_LOW3_KEY = 20, //0x14, //TUPLE_CSTRING
//Extra Features
	EXTRA_ESDURATION_KEY = 21, //0x15, //TUPLE_INT
	EXTRA_TIMER_KEY = 22, //0x16, //TUPLE_INT
	EXTRA_FORECAST_KEY = 23, //0x17, //TUPLE_INT
	//YWeather 2.3 - REQ01. Display Seconds - START
	DISPLAY_SECONDS_KEY = 24, //0x18, //TUPLE_INT
	//YWeather 2.3 - REQ01. Display Seconds - START
	//YWeather 2.3 - REQ02. Hourly Vibe - START
	HOURLY_VIBE_KEY = 25, //0x19, //TUPLE_INT
	//YWeather 2.3 - REQ02. Hourly Vibe - END
	HOURLY_VIBE_START_KEY = 26, //INT
	HOURLY_VIBE_END_KEY = 27, //INT
	HIDE_BAT_KEY = 28, //INT
	FONT_KEY = 29, //INT
};

	#define TAP_TIME 2000
	bool is_tapped_waiting = false;
	int TapCount = 0;

//Define and initialize variables
	//FONTS
	GFont font_date; // Font for date
	GFont font_time; // Font for time
	GFont font_update; // Font for last update
	GFont font_temperature;        // Font for the temperature
	
	//Vibe Control
	bool BTConnected = true;
	
	// Setup messaging
	const int inbound_size = 512;
	const int outbound_size = 512;
	
	//Time control for weather refresh
	static AppTimer *timer;
	uint32_t timeout_ms = 1800000; //30min (1min = 60000)
	uint32_t ESDuration_ms = 5000; //5sec (1min = 60000)

	int init_timeout_ms;
	int init_ESDuration_ms;
	
	static AppTimer *weather;
	//static AppTimer *accelerometer;
	static AppTimer *initialize;
	//static AppTimer *tap_timer;
	
	
	InverterLayer *inv_layer;
	
	//Date & Time        
	static char last_update[]="00:00 ";
	//static int initial_minute;
	
	static char weekday_text[] = "XXXXXXXXXXXX";
	//static char date_text[] = "XXX 00";
	static char month_text[] = "XXXXXXXXXXXXX";
	//static char day_text[] = "1";
	static char day_month[]= "31 SEPTEMBER";
	static char time_text[] = "00:00";
//YWeather 2.3 - REQ01. Display Seconds - START
	static char seconds_text[] = "00";
	static char ampm_text[] = "   ";
//YWeather 2.3 - REQ01. Display Seconds - END
	//static char inverted[]="B";
	//static char temperature[]="     ";
	static char high[]="     ";
	static char low[]="    ";
	static char sunrise[]="     ";
	static char sunset[]="     ";
	static char wind[]="     ";
	static int wdirection;
	static char strwdirection[100];
	static char city[100];
	static char temp[]="     ";

	static char version[]="2.5";

	static char weekday1_text[] = "XXXXXXXXXXXXX";
	static char weekday2_text[] = "XXXXXXXXXXXXX";
	static char weekday3_text[] = "XXXXXXXXXXXXX";

	static char day1H[] = "      ";
	static char day1L[] = "      ";
	static char day2H[] = "      ";
	static char day2L[] = "      ";
	static char day3H[] = "      ";
	static char day3L[] = "      ";

	int code1;
	int code2;
	int code3;

	//static uint8_t *resized_data;
	//static uint8_t *resized_data2;
	//static uint8_t *resized_data3;
	int iHours;
	int iHours2;
	int iMinutes;
	int iMinutes2;



	int moonphase_number;
	int intday;
	int intmonth;
	int intyear;

	//variable to avoid the app crashing when adding new languages
	int intLangCounter = 16;
	
	
	bool translate_sp = true;
	int language = 100;
	bool color_inverted;
	int ICON_CODE;
	bool batt_status = false; //If true, display the battery status all the time; if false, just when running low (<10%)
	
	bool blnvibes;
	bool blninverted =  false;
	bool blnForecast = false;
	bool bln3daysForecast = false;
	//YWeather 2.3 - REQ01. Display Seconds - START
	bool blnseconds = false;
	//YWeather 2.3 - REQ01. Display Seconds - END
	//YWeather 2.3 - REQ02. Hourly Vibe - START
	bool blnhourly_vibe = false;
	//YWeather 2.3 - REQ02. Hourly Vibe - END
    
//Load the custom fonts
	int intUI = 0; //0 = Classic, 1 = Modern
