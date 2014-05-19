//*************//
// Define KEYS //
//*************//

enum WeatherKey {
	WEATHER_ICON_KEY = 0x0,        // TUPLE_INT
	WEATHER_TEMPERATURE_KEY = 0x1, // TUPLE_CSTRING
	WEATHER_CITY_KEY = 0x2,        //	TUPLE_CSTRING
	INVERT_COLOR_KEY = 0x3,  		 // TUPLE_INT
	language_key = 0x4, 			// TUPLE_INT
	VIBES_KEY = 0x5,  		 // TUPLE_INT
//Forecast for the day
	WEATHER_HIGH_KEY = 0x6,	//TUPLE_CSTRING
	WEATHER_LOW_KEY = 0x7,	//TUPLE_CSTRING
	SUNRISE_KEY = 0x8, //TUPLE_CSTRING
	SUNSET_KEY = 0x9, //TUPLE_CSTRING
	WIND_KEY = 0xa, //TUPLE_CSTRING
	WDIRECTION_KEY = 0xb, //TUPLE_INT
};

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
	const uint32_t timeout_ms = 1800000; //30min (1min = 60000)
	
	static AppTimer *weather;
	static AppTimer *accelerometer;
	static AppTimer *initialize;
	
	
	InverterLayer *inv_layer;
	
	//Date & Time        
	static char last_update[]="00:00 ";
	static int initial_minute;
	
	static char weekday_text[] = "XXXXXXXXXXXX";
	static char date_text[] = "XXX 00";
	static char month_text[] = "XXXXXXXXXXXXX";
	static char day_text[] = "1";
	static char day_month[]= "31 SEPTEMBER";
	static char time_text[] = "00:00";
	static char inverted[]="B";
	static char temperature[]="     ";
	static char high[]="     ";
	static char low[]="    ";
	static char sunrise[]="     ";
	static char sunset[]="     ";
	static char wind[]="     ";
	static int wdirection;
	static char strwdirection[100];
	static char city[100];
	
	int iHours;
	int iHours2;
	int iMinutes;
	int iMinutes2;
	
	int moonphase_number;
	int intday;
	int intmonth;
	int intyear;
	
	
	bool translate_sp = true;
	int language = 100;
	bool color_inverted;
	int ICON_CODE;
	bool batt_status = true; //If true, display the battery status all the time; if false, just when running low (<10%)
	
	bool blnvibes;
	bool blninverted =  false;
	bool blnForecast = false;