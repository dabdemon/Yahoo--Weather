#include <appMessage.h>
#include <main.h>


//*****************//
// AppSync options //
//*****************//
static AppSync sync;
//uint8_t sync_buffer[PBL_IF_BW_ELSE(350,512)];
uint8_t sync_buffer[512];
static char update_text[] = "00:00";

//Initial Tuples
static char initial_temp[]="     ";
int initial_ICON_CODE = 16;
static char initial_city[100];
uint32_t initial_timeout_ms = 180000; 
bool initial_HourlyVibe = false;
uint32_t initial_ESDuration_ms = 5000; //5sec (1min = 60000)
int initial_Language = 100;
bool initial_blnseconds = false;
static char initial_high[6];
static char initial_low[6];
static char initial_sunrise[6];
static char initial_sunset[6];
static char initial_wind[6];
static int initial_wdirection;
static char initial_strwdirection[100];
static char initial_city[100];
static char initial_PoP[] = "    ";
bool initial_bln3daysForecast = false;
bool initial_blnBacklight = false;
static char initial_day1H[7];
static char initial_day1L[7];
static char initial_day2H[7];
static char initial_day2L[7];
static char initial_day3H[7];
static char initial_day3L[7];
int oldLanguage;
int initial_day1_code = 18;
int initial_day2_code = 18;
int initial_day3_code = 18;


static void sync_tuple_changed_callback(const uint32_t key,
                                        const Tuple* new_tuple,
                                        const Tuple* old_tuple,
                                        void* context) {

	//On initial load, DO NOT run the Tuple changes (they are the persistently saved data, so make no sense)
		  // App Sync keeps new_tuple in sync_buffer, so we may use it directly
		switch (key) {

		  case WEATHER_ICON_KEY:
				persist_write_int(WEATHER_ICON_KEY, new_tuple->value->uint8);
				refreshLayers(WEATHER_ICON_KEY, new_tuple);
				break;

		  case WEATHER_TEMPERATURE_KEY:
				//Save the temperature
				persist_write_string(WEATHER_TEMPERATURE_KEY, new_tuple->value->cstring);
				//Save the last update
				clock_copy_time_string(update_text, sizeof(update_text));
				persist_write_string(WEATHER_LAST_UPDATE, update_text);
				//Reload data
				refreshLayers(WEATHER_TEMPERATURE_KEY,new_tuple);
				break;

		  case WEATHER_CITY_KEY:
				persist_write_string(WEATHER_CITY_KEY, new_tuple->value->cstring);
				refreshLayers(WEATHER_CITY_KEY,new_tuple);
				break;

		  case INVERT_COLOR_KEY:
			  persist_write_bool(INVERT_COLOR_KEY, new_tuple->value->uint8 != 0);
			  break;

		  case language_key:
			  oldLanguage = persist_read_int(language_key);
			 
			  if (oldLanguage != new_tuple->value->uint8){
				 persist_write_int(language_key, new_tuple->value->uint8);
				 refreshLayers(language_key,new_tuple);  
			  }

			  break;

		  case VIBES_KEY:
			  persist_write_int(VIBES_KEY, new_tuple->value->uint8);
			  break;

		  //Forecast for the day

		  case WEATHER_HIGH_KEY: 
				//check that sync is getting something different than default value before saving
				if (strcmp(new_tuple->value->cstring,"999") != 0){
					//Save the High temperature
					persist_write_string(WEATHER_HIGH_KEY, new_tuple->value->cstring);
					//refresh the local variable
					//refreshLayers(WEATHER_HIGH_KEY,new_tuple);
				}
				break;

		  case WEATHER_LOW_KEY:
				//check that sync is getting something different than default value before saving
				if (strcmp(new_tuple->value->cstring,"999") != 0){
					//Save the Low temperature
					persist_write_string(WEATHER_LOW_KEY, new_tuple->value->cstring);
					//refresh the local variable
					//refreshLayers(WEATHER_LOW_KEY,new_tuple);
				}
				break;

		  case SUNRISE_KEY:
				//check that sync is getting something different than default value before saving
				if (strcmp(new_tuple->value->cstring,"99:99") != 0){
					//Save the Sunrise Time
					persist_write_string(SUNRISE_KEY, new_tuple->value->cstring);
					//refresh the local variable
					//refreshLayers(SUNRISE_KEY,new_tuple);
				}
				break;

		  case SUNSET_KEY:
				//check that sync is getting something different than default value before saving
				if (strcmp(new_tuple->value->cstring,"99:99") != 0){
					//Save the Sunset Time
					persist_write_string(SUNSET_KEY, new_tuple->value->cstring);
					//refresh the local variable
					//refreshLayers(SUNSET_KEY,new_tuple);
				}
				break;

		  case WIND_KEY:
				//check that sync is getting something different than default value before saving
				if (strcmp(new_tuple->value->cstring,"999") != 0){
					 //Save the Wind Speed
					persist_write_string(WIND_KEY, new_tuple->value->cstring);
					//refresh the local variable
					//refreshLayers(WIND_KEY,new_tuple);
				}
				break;

		  case WDIRECTION_KEY:
				//check that sync is getting something different than default value before saving
				if (strcmp(new_tuple->value->cstring,"999") != 0){
					//Save the Wind Direction
					persist_write_string(WDIRECTION_KEY, new_tuple->value->cstring);
					//refresh the local variable
					//refreshLayers(WDIRECTION_KEY,new_tuple);
				}
				break;

		  case FORECAST_CODE1_KEY:
				if (new_tuple->value->uint8 != 18){
					//Saves de weather condition
					persist_write_int(FORECAST_CODE1_KEY, new_tuple->value->uint8);
				}
				break;

		  case FORECAST_HIGH1_KEY:
				//check that sync is getting something different than default value before saving
				if (strcmp(new_tuple->value->cstring,"999") != 0){
					//Saves the high for the day
					persist_write_string(FORECAST_HIGH1_KEY, new_tuple->value->cstring);
				}
				break;

		  case FORECAST_LOW1_KEY:
				//check that sync is getting something different than default value before saving
				if (strcmp(new_tuple->value->cstring,"999") != 0){
					//Saves the low for the day
					persist_write_string(FORECAST_LOW1_KEY, new_tuple->value->cstring);
				}
				break;	 

		  case FORECAST_CODE2_KEY:
				if (new_tuple->value->uint8 != 18){
					//Saves de weather condition
					persist_write_int(FORECAST_CODE2_KEY, new_tuple->value->uint8);
				}
				break;

		  case FORECAST_HIGH2_KEY:
				//check that sync is getting something different than default value before saving
				if (strcmp(new_tuple->value->cstring,"999") != 0){
					//Saves the high for the day
					persist_write_string(FORECAST_HIGH2_KEY, new_tuple->value->cstring);
				}
				break;

		  case FORECAST_LOW2_KEY:
				//check that sync is getting something different than default value before saving
				if (strcmp(new_tuple->value->cstring,"999") != 0){
					//Saves the low for the day
					persist_write_string(FORECAST_LOW2_KEY, new_tuple->value->cstring);
				}
				break;

		  case FORECAST_CODE3_KEY:
				if (new_tuple->value->uint8 != 18){
					//Saves the weather condition
					persist_write_int(FORECAST_CODE3_KEY, new_tuple->value->uint8);
				}
				break;

		  case FORECAST_HIGH3_KEY:
				//check that sync is getting something different than default value before saving
				if (strcmp(new_tuple->value->cstring,"999") != 0){
					//Saves the high for the day
					persist_write_string(FORECAST_HIGH3_KEY, new_tuple->value->cstring);
				}
				break;

		  case FORECAST_LOW3_KEY:
				//check that sync is getting something different than default value before saving
				if (strcmp(new_tuple->value->cstring,"999") != 0){
					persist_write_string(FORECAST_LOW3_KEY, new_tuple->value->cstring);
				}
				break;

		  case EXTRA_ESDURATION_KEY:
				persist_write_int(EXTRA_ESDURATION_KEY, new_tuple->value->uint8*1000);
				refreshLayers(EXTRA_ESDURATION_KEY, new_tuple);
				break;

		  case EXTRA_TIMER_KEY:
				persist_write_int(EXTRA_TIMER_KEY,new_tuple->value->uint8 * 60000);
				refreshLayers(EXTRA_TIMER_KEY, new_tuple);
				break;

		  case EXTRA_FORECAST_KEY:
				persist_write_int(EXTRA_FORECAST_KEY, new_tuple->value->uint8);
				refreshLayers(EXTRA_FORECAST_KEY, new_tuple);
				break;

		  case DISPLAY_SECONDS_KEY:
				//Saves the display seconds toggle
				persist_write_int(DISPLAY_SECONDS_KEY, new_tuple->value->uint8);
				refreshLayers(DISPLAY_SECONDS_KEY, new_tuple);
				break;

		  case HOURLY_VIBE_KEY:
				persist_write_int(HOURLY_VIBE_KEY, new_tuple->value->uint8); 
				refreshLayers(HOURLY_VIBE_KEY, new_tuple);
				break;

		  case HOURLY_VIBE_START_KEY:
				persist_write_int(HOURLY_VIBE_START_KEY, new_tuple->value->uint8);
				break;

		  case HOURLY_VIBE_END_KEY:
				persist_write_int(HOURLY_VIBE_END_KEY, new_tuple->value->uint8);
				break;

		  case HIDE_BAT_KEY:
				persist_write_int(HIDE_BAT_KEY, new_tuple->value->uint8 != 0);
				break;

		  case BACKLIGHT_KEY:
				persist_write_int(BACKLIGHT_KEY, new_tuple->value->uint8 != 0);
				refreshLayers(BACKLIGHT_KEY, new_tuple);
				break;

		  case POP_KEY:
				//check that sync is getting something different than default value before saving
				if (strcmp(new_tuple->value->cstring,"999") != 0){
					//Save the Rain Probability
					persist_write_string(POP_KEY, new_tuple->value->cstring);
					//refresh the local variable
					//refreshLayers(POP_KEY,new_tuple);
				}
				break;

		  case THEME_KEY:
				//Save the Theme (in case it changed)
				persist_write_int(THEME_KEY, new_tuple->value->uint8);
				break;
	}

	  
}


void SetupMessages(){
	
		//first, load the main screen persistent data
		//loadPersistentData(false, language_key);
		//loadPersistentData(false, WEATHER_TEMPERATURE_KEY);
		//loadPersistentData(false, WEATHER_ICON_KEY);
	
		//and then load the initial tuples
		loadInitialTuples();

		//second, open the app message session
        //app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
		//app_message_open(PBL_IF_BW_ELSE(256,512), PBL_IF_BW_ELSE(256,512));
		app_message_open(512, 512);
       
		//third, define the initial tuples array
		Tuplet initial_values[] = {
			TupletInteger(WEATHER_ICON_KEY,initial_ICON_CODE),
			MyTupletCString(WEATHER_TEMPERATURE_KEY, initial_temp),
			//TupletInteger(THEME_KEY, 0),
			MyTupletCString(WEATHER_CITY_KEY, "YWeather v3.6"), //display app version on load
			//TupletInteger(INVERT_COLOR_KEY, 0),
			TupletInteger(language_key, initial_Language), //INITIALIZE TO LAST SAVED	
			TupletInteger(VIBES_KEY, 0),
			MyTupletCString(WEATHER_HIGH_KEY,"999"),
			MyTupletCString(WEATHER_LOW_KEY,"999"),
			MyTupletCString(SUNRISE_KEY,"99:99"),
			MyTupletCString(SUNSET_KEY,"99:99"),
			MyTupletCString(WIND_KEY,"999"),
			MyTupletCString(WDIRECTION_KEY,"999"),
			MyTupletCString(POP_KEY,"999"),
		//3 days forecast
			TupletInteger(FORECAST_CODE1_KEY,18),
			MyTupletCString(FORECAST_HIGH1_KEY,"999"),
			MyTupletCString(FORECAST_LOW1_KEY,"999"),
			TupletInteger(FORECAST_CODE2_KEY,18),
			MyTupletCString(FORECAST_HIGH2_KEY,"999"),
			MyTupletCString(FORECAST_LOW2_KEY,"999"),
			TupletInteger(FORECAST_CODE3_KEY,18),
			MyTupletCString(FORECAST_HIGH3_KEY,"999"),
			MyTupletCString(FORECAST_LOW3_KEY,"999"),
		//Extra Features
			TupletInteger(EXTRA_ESDURATION_KEY,initial_ESDuration_ms),
			TupletInteger(EXTRA_TIMER_KEY,initial_timeout_ms),
			TupletInteger(EXTRA_FORECAST_KEY,initial_bln3daysForecast),
			TupletInteger(DISPLAY_SECONDS_KEY,initial_blnseconds),
			TupletInteger(HOURLY_VIBE_KEY,initial_HourlyVibe),
			TupletInteger(HOURLY_VIBE_START_KEY,0),
			TupletInteger(HOURLY_VIBE_END_KEY,0),
			//TupletInteger(HIDE_BAT_KEY,0),
			TupletInteger(BACKLIGHT_KEY, initial_blnBacklight),
       	}; //TUPLET INITIAL VALUES
        
	
		//finally init the app sync
		app_sync_init(&sync, sync_buffer, sizeof(sync_buffer), initial_values,
					  ARRAY_LENGTH(initial_values), sync_tuple_changed_callback,
					  NULL, NULL);
	
		//after initializing the sync, unload the initial tuples to free memory
		//unloadInitialTuples();
}

void loadInitialTuples(){
	//Weather
	if(persist_exists(WEATHER_TEMPERATURE_KEY)){persist_read_string(WEATHER_TEMPERATURE_KEY, initial_temp, sizeof(initial_temp));}
	if(persist_exists(WEATHER_ICON_KEY)){initial_ICON_CODE = persist_read_int(WEATHER_ICON_KEY);}
	if(persist_exists(WEATHER_CITY_KEY)){persist_read_string(WEATHER_CITY_KEY, initial_city, sizeof(initial_city));}
	if(persist_exists(EXTRA_TIMER_KEY)){initial_timeout_ms = persist_read_int(EXTRA_TIMER_KEY);}
	if(persist_exists(language_key)){initial_Language = persist_read_int(language_key);}
	//Miscellaneous
	if(persist_exists(HOURLY_VIBE_KEY)){initial_HourlyVibe = persist_read_int(HOURLY_VIBE_KEY);}
	if(persist_exists(EXTRA_ESDURATION_KEY)){
		initial_ESDuration_ms = persist_read_int(EXTRA_ESDURATION_KEY);
		//ensure the initial_ESDuration_ms is not over the limits (by mistake)
		if(initial_ESDuration_ms > 15000){initial_ESDuration_ms = 5000;}
	}
	if(persist_exists(BACKLIGHT_KEY)){
		initial_blnBacklight= persist_read_int(BACKLIGHT_KEY);
	}
	
	if(persist_exists(DISPLAY_SECONDS_KEY)){
		initial_blnseconds = persist_read_int(DISPLAY_SECONDS_KEY);
		
	}
	
	/*
	//Forecast
	if(persist_exists(WEATHER_HIGH_KEY)){persist_read_string(WEATHER_HIGH_KEY, initial_high, sizeof(initial_high));}
	if(persist_exists(WEATHER_LOW_KEY)){persist_read_string(WEATHER_LOW_KEY, initial_low, sizeof(initial_low));}
	if(persist_exists(SUNRISE_KEY)){persist_read_string(SUNRISE_KEY, initial_sunrise, sizeof(initial_sunrise));}
	if(persist_exists(SUNSET_KEY)){persist_read_string(SUNSET_KEY, initial_sunset, sizeof(initial_sunset));}
	if(persist_exists(WIND_KEY)){persist_read_string(WIND_KEY, initial_wind, sizeof(initial_wind));}
	if(persist_exists(POP_KEY)){persist_read_string(POP_KEY, initial_PoP, sizeof(initial_PoP));}
	if(persist_exists(WDIRECTION_KEY)){persist_read_string(WDIRECTION_KEY, initial_strwdirection, sizeof(initial_strwdirection));}
	*/
	//3-Day Forecast
	if(persist_exists(EXTRA_FORECAST_KEY)){initial_bln3daysForecast = persist_read_int(EXTRA_FORECAST_KEY);}
	/*
	if(persist_exists(FORECAST_HIGH1_KEY)){persist_read_string(FORECAST_HIGH1_KEY, initial_day1H, sizeof(initial_day1H));}
	if(persist_exists(FORECAST_LOW1_KEY)){persist_read_string(FORECAST_LOW1_KEY, initial_day1L, sizeof(initial_day1L));}
	if(persist_exists(FORECAST_HIGH2_KEY)){persist_read_string(FORECAST_HIGH2_KEY, initial_day2H, sizeof(initial_day2H));}
	if(persist_exists(FORECAST_LOW2_KEY)){persist_read_string(FORECAST_LOW2_KEY, initial_day2L, sizeof(initial_day2L));}
	if(persist_exists(FORECAST_HIGH3_KEY)){persist_read_string(FORECAST_HIGH3_KEY, initial_day3H, sizeof(initial_day3H));}
	if(persist_exists(FORECAST_LOW3_KEY)){persist_read_string(FORECAST_LOW3_KEY, initial_day3L, sizeof(initial_day3L));}
	if(persist_exists(FORECAST_CODE1_KEY)){initial_day1_code = persist_read_int(FORECAST_CODE1_KEY);}
	if(persist_exists(FORECAST_CODE2_KEY)){initial_day2_code = persist_read_int(FORECAST_CODE2_KEY);}
	if(persist_exists(FORECAST_CODE3_KEY)){initial_day3_code = persist_read_int(FORECAST_CODE3_KEY);}
	*/
	
}

void unloadInitialTuples(){
	memset(&initial_temp[0], 0, sizeof(initial_temp));
	memset(&initial_city[0], 0, sizeof(initial_city));
	memset(&initial_temp[0], 0, sizeof(initial_high));
	memset(&initial_temp[0], 0, sizeof(initial_low));
	memset(&initial_temp[0], 0, sizeof(initial_sunrise));
	memset(&initial_temp[0], 0, sizeof(initial_sunset));
	memset(&initial_temp[0], 0, sizeof(initial_wind));
	memset(&initial_temp[0], 0, sizeof(initial_PoP));
	memset(&initial_temp[0], 0, sizeof(initial_strwdirection));
	memset(&initial_temp[0], 0, sizeof(initial_day1H));
	memset(&initial_temp[0], 0, sizeof(initial_day1L));
	memset(&initial_temp[0], 0, sizeof(initial_day2H));
	memset(&initial_temp[0], 0, sizeof(initial_day2L));
	memset(&initial_temp[0], 0, sizeof(initial_day3H));
	memset(&initial_temp[0], 0, sizeof(initial_day3L));
}