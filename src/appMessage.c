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
static char initial_city[100];;
uint32_t initial_timeout_ms = 180000; 
bool initial_HourlyVibe = false;
uint32_t initial_ESDuration_ms = 5000; //5sec (1min = 60000)
int initial_Language = 100;
static char initial_high[]="     ";
static char initial_low[]="    ";
static char initial_sunrise[]="     ";
static char initial_sunset[]="     ";
static char initial_wind[]="     ";
static int initial_wdirection;
static char initial_strwdirection[100];
static char initial_city[100];
static char initial_PoP[] = "    ";
bool initial_bln3daysForecast = false;
bool initial_blnBacklight = false;
static char initial_day1H[] = "      ";
static char initial_day1L[] = "      ";
static char initial_day2H[] = "      ";
static char initial_day2L[] = "      ";
static char initial_day3H[] = "      ";
static char initial_day3L[] = "      ";
int oldLanguage;
int initial_day1_code = 18;
int initial_day2_code = 18;
int initial_day3_code = 18;


static void sync_tuple_changed_callback(const uint32_t key,
                                        const Tuple* new_tuple,
                                        const Tuple* old_tuple,
                                        void* context) {

  // App Sync keeps new_tuple in sync_buffer, so we may use it directly
  switch (key) {
	  
	  case WEATHER_ICON_KEY:
	  	  	persist_write_int(WEATHER_ICON_KEY, new_tuple->value->uint8);
	  		loadPersistentData(true, WEATHER_ICON_KEY);
      		break;
	  
	  case WEATHER_TEMPERATURE_KEY:
	  		//Save the temperature
	    	persist_write_string(WEATHER_TEMPERATURE_KEY, new_tuple->value->cstring);
	  		//Save the last update
	  		clock_copy_time_string(update_text, sizeof(update_text));
	  		persist_write_string(WEATHER_LAST_UPDATE, update_text);
	  		//Reload data
	  		loadPersistentData(true, WEATHER_TEMPERATURE_KEY);
	  		loadPersistentData(false, WEATHER_LAST_UPDATE);
      		break;
	  
	  case WEATHER_CITY_KEY:
	  		persist_write_string(WEATHER_CITY_KEY, new_tuple->value->cstring);
	  		loadPersistentData(true, WEATHER_CITY_KEY);
         	break;
	  
	  case INVERT_COLOR_KEY:
		  persist_write_bool(INVERT_COLOR_KEY, new_tuple->value->uint8 != 0);
		  break;
	  
	  case language_key:
	  	  oldLanguage = persist_read_int(language_key);
	  	  persist_write_int(language_key, new_tuple->value->uint8);
	  	  if (oldLanguage != new_tuple->value->uint8){
			 loadPersistentData(true, language_key);  
		  }
		  
		  break;
	  
	  case VIBES_KEY:
		  persist_write_int(VIBES_KEY, new_tuple->value->uint8);
		  break;
  
	  //Forecast for the day
	  
	  case WEATHER_HIGH_KEY: 
	  		//Save the High temperature
	    	persist_write_string(WEATHER_HIGH_KEY, new_tuple->value->cstring);
	  		loadPersistentData(false, WEATHER_HIGH_KEY);
      		break;
	  
	  case WEATHER_LOW_KEY:
	  	  	//Save the Low temperature
	    	persist_write_string(WEATHER_LOW_KEY, new_tuple->value->cstring);
	  		loadPersistentData(false, WEATHER_LOW_KEY);
      		break;
	  
	  case SUNRISE_KEY:
	  	  	//Save the Sunrise Time
	    	persist_write_string(SUNRISE_KEY, new_tuple->value->cstring);
	  		loadPersistentData(false, SUNRISE_KEY);
      		break;
	  
	  case SUNSET_KEY:
	  	  	//Save the Sunset Time
	    	persist_write_string(SUNSET_KEY, new_tuple->value->cstring);
	  		loadPersistentData(false, SUNSET_KEY);
      		break;
	  
	  case WIND_KEY:
	  	  	 //Save the Wind Speed
	    	persist_write_string(WIND_KEY, new_tuple->value->cstring);
	  		loadPersistentData(false, WIND_KEY);
      		break;
	  
	  case WDIRECTION_KEY:
	  	  	//Save the Wind Direction
	  		persist_write_string(WDIRECTION_KEY, new_tuple->value->cstring);
	 		loadPersistentData(false, WDIRECTION_KEY);
      		break;
	  
	  case FORECAST_CODE1_KEY:
	  		//Saves de weather condition
	  		persist_write_int(FORECAST_CODE1_KEY, new_tuple->value->uint8);
	 		loadPersistentData(false, FORECAST_CODE1_KEY);
      		break;
	  
	  case FORECAST_HIGH1_KEY:
	  		//Saves the high for the day
	  	 	persist_write_string(FORECAST_HIGH1_KEY, new_tuple->value->cstring);
	  		loadPersistentData(false, FORECAST_HIGH1_KEY);
      		break;
	  
	  case FORECAST_LOW1_KEY:
	  		//Saves the low for the day
	  	    persist_write_string(FORECAST_LOW1_KEY, new_tuple->value->cstring);
	  		loadPersistentData(false, FORECAST_LOW1_KEY);
      		break;	 
	  
	  case FORECAST_CODE2_KEY:
	  		//Saves de weather condition
	  		persist_write_int(FORECAST_CODE2_KEY, new_tuple->value->uint8);
	  		loadPersistentData(false, FORECAST_CODE2_KEY);
      		break;
	  
	  case FORECAST_HIGH2_KEY:
	  		//Saves the high for the day
	  	    persist_write_string(FORECAST_HIGH2_KEY, new_tuple->value->cstring);
	  		loadPersistentData(false, FORECAST_HIGH2_KEY);
      		break;
	  
	  case FORECAST_LOW2_KEY:
	  		//Saves the low for the day
	  	    persist_write_string(FORECAST_LOW2_KEY, new_tuple->value->cstring);
	  		loadPersistentData(false, FORECAST_LOW2_KEY);
      		break;
	  
	  case FORECAST_CODE3_KEY:
	  		//Saves the weather condition
	  		persist_write_int(FORECAST_CODE3_KEY, new_tuple->value->uint8);
	  		loadPersistentData(false, FORECAST_CODE3_KEY);
      		break;
	  
	  case FORECAST_HIGH3_KEY:
	  		//Saves the high for the day
	  	    persist_write_string(FORECAST_HIGH3_KEY, new_tuple->value->cstring);
	  		loadPersistentData(false, FORECAST_HIGH3_KEY);
      		break;
	  
	  case FORECAST_LOW3_KEY:
	  	    persist_write_string(FORECAST_LOW3_KEY, new_tuple->value->cstring);
	  		loadPersistentData(false, FORECAST_LOW3_KEY);
      		break;
	  
	  case EXTRA_ESDURATION_KEY:
	  		persist_write_int(EXTRA_ESDURATION_KEY, new_tuple->value->uint8*1000);
	  		loadPersistentData(false, EXTRA_ESDURATION_KEY);
      		break;
	  
	  case EXTRA_TIMER_KEY:
	  		persist_write_int(EXTRA_TIMER_KEY,new_tuple->value->uint8 * 60000);
	  		loadPersistentData(false, EXTRA_TIMER_KEY);
      		break;
	  
	  case EXTRA_FORECAST_KEY:
	  		persist_write_int(EXTRA_FORECAST_KEY, new_tuple->value->uint8);
	  		loadPersistentData(false, EXTRA_FORECAST_KEY);
      		break;
	  
	  case DISPLAY_SECONDS_KEY:
	  		//Saves the display seconds toggle
			persist_write_int(DISPLAY_SECONDS_KEY, new_tuple->value->uint8);
      		break;

	  case HOURLY_VIBE_KEY:
	  		persist_write_int(HOURLY_VIBE_KEY, new_tuple->value->uint8); 
	  		loadPersistentData(false, HOURLY_VIBE_KEY);
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
	  		loadPersistentData(false, BACKLIGHT_KEY);
		  	break;
	  
	  case POP_KEY:
	  	  	//Save the Rain Probability
	    	persist_write_string(POP_KEY, new_tuple->value->cstring);
		  	loadPersistentData(false, POP_KEY);
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
			MyTupletCString(WEATHER_CITY_KEY, "YWeather v3.3"), //display app version on load
			//TupletInteger(INVERT_COLOR_KEY, 0),
			TupletInteger(language_key, initial_Language), //INITIALIZE TO LAST SAVED	
			TupletInteger(VIBES_KEY, 0),
			MyTupletCString(WEATHER_HIGH_KEY,initial_high),
			MyTupletCString(WEATHER_LOW_KEY,initial_low),
			MyTupletCString(SUNRISE_KEY,initial_sunrise),
			MyTupletCString(SUNSET_KEY,initial_sunset),
			MyTupletCString(WIND_KEY,initial_wind),
			MyTupletCString(WDIRECTION_KEY,initial_strwdirection),
			MyTupletCString(POP_KEY,initial_PoP),
		//3 days forecast
			TupletInteger(FORECAST_CODE1_KEY,initial_day1_code),
			MyTupletCString(FORECAST_HIGH1_KEY,initial_day1H),
			MyTupletCString(FORECAST_LOW1_KEY,initial_day1L),
			TupletInteger(FORECAST_CODE2_KEY,initial_day2_code),
			MyTupletCString(FORECAST_HIGH2_KEY,initial_day2H),
			MyTupletCString(FORECAST_LOW2_KEY,initial_day2L),
			TupletInteger(FORECAST_CODE3_KEY,initial_day3_code),
			MyTupletCString(FORECAST_HIGH3_KEY,initial_day3H),
			MyTupletCString(FORECAST_LOW3_KEY,initial_day3L),
		//Extra Features
			TupletInteger(EXTRA_ESDURATION_KEY,initial_ESDuration_ms),
			TupletInteger(EXTRA_TIMER_KEY,initial_timeout_ms),
			TupletInteger(EXTRA_FORECAST_KEY,initial_bln3daysForecast),
			//TupletInteger(DISPLAY_SECONDS_KEY,0),
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
		unloadInitialTuples();
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
	//Forecast
	if(persist_exists(WEATHER_HIGH_KEY)){persist_read_string(WEATHER_HIGH_KEY, initial_high, sizeof(initial_high));}
	if(persist_exists(WEATHER_LOW_KEY)){persist_read_string(WEATHER_LOW_KEY, initial_low, sizeof(initial_low));}
	if(persist_exists(SUNRISE_KEY)){persist_read_string(SUNRISE_KEY, initial_sunrise, sizeof(initial_sunrise));}
	if(persist_exists(SUNSET_KEY)){persist_read_string(SUNSET_KEY, initial_sunset, sizeof(initial_sunset));}
	if(persist_exists(WIND_KEY)){persist_read_string(WIND_KEY, initial_wind, sizeof(initial_wind));}
	if(persist_exists(POP_KEY)){persist_read_string(POP_KEY, initial_PoP, sizeof(initial_PoP));}
	if(persist_exists(WDIRECTION_KEY)){persist_read_string(WDIRECTION_KEY, initial_strwdirection, sizeof(initial_strwdirection));}
	//3-Day Forecast
	if(persist_exists(EXTRA_FORECAST_KEY)){initial_bln3daysForecast = persist_read_int(EXTRA_FORECAST_KEY);}
	if(persist_exists(FORECAST_HIGH1_KEY)){persist_read_string(FORECAST_HIGH1_KEY, initial_day1H, sizeof(initial_day1H));}
	if(persist_exists(FORECAST_LOW1_KEY)){persist_read_string(FORECAST_LOW1_KEY, initial_day1L, sizeof(initial_day1L));}
	if(persist_exists(FORECAST_HIGH2_KEY)){persist_read_string(FORECAST_HIGH2_KEY, initial_day2H, sizeof(initial_day2H));}
	if(persist_exists(FORECAST_LOW2_KEY)){persist_read_string(FORECAST_LOW2_KEY, initial_day2L, sizeof(initial_day2L));}
	if(persist_exists(FORECAST_HIGH3_KEY)){persist_read_string(FORECAST_HIGH3_KEY, initial_day3H, sizeof(initial_day3H));}
	if(persist_exists(FORECAST_LOW3_KEY)){persist_read_string(FORECAST_LOW3_KEY, initial_day3L, sizeof(initial_day3L));}
	if(persist_exists(FORECAST_CODE1_KEY)){initial_day1_code = persist_read_int(FORECAST_CODE1_KEY);}
	if(persist_exists(FORECAST_CODE2_KEY)){initial_day2_code = persist_read_int(FORECAST_CODE2_KEY);}
	if(persist_exists(FORECAST_CODE3_KEY)){initial_day3_code = persist_read_int(FORECAST_CODE3_KEY);}
	
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