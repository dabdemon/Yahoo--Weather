#include <pebble.h>
#include <main.h>
#include <appMessage.h>
#include <bitmaps.h>
#include <userInterface.h>
#include <variables.h>
#include <language.h>
#include <functions.h>
#include <bluetooth.h>
#include <battery.h>
#include <PDUtils.h>


//*************//
// ENTRY POINT //
//*************//
int main(void){        
        handle_init();
        app_event_loop();
        handle_deinit();
}


//**********************//
// Kill the application //
//**********************//
void handle_deinit(void){
  //text_layer_destroy(text_layer);

/*
        //Unsuscribe services
        tick_timer_service_unsubscribe();
	
        //Deallocate custom fonts
        void unloadFontResource();
        
        //Deallocate the main window
         window_destroy(mainWindow);
*/

} //HANDLE_DEINIT

//**********************//
// Init the application //
//**********************//
void handle_init(void){
		//Use the internationalization API to detect the user's language
		setlocale(LC_ALL, i18n_get_system_locale());

        //Create the main window
        mainWindow = window_create();
        window_stack_push(mainWindow, true /* Animated */);  
	
		window_set_background_color(mainWindow, GColorBlack);
	
		loadFontResources();
	
		//loadPersistentData(false);
  
		//Load the Main Window
		LoadDigital();
		//Get Current Date
		loadPersistentData(false, language_key);
		getDate();
		//getTime();
		
		// Set up the update layer callback
		SubscribeTickEvent();
	
		//Enable the Battery check event (for PTR or Digital theme)
		battery_state_service_subscribe(&handle_battery);
		//and get the current battery status to do not experience delays
  		handle_battery(battery_state_service_peek());
	
		//Check the Bluetooth status
		//#ifdef PBL_SDK_2
		  //bluetooth_connection_service_subscribe(handle_bluetooth);
		//#elif PBL_SDK_3
		  connection_service_subscribe((ConnectionHandlers) {
			.pebble_app_connection_handler = handle_bluetooth
		  });
		//#endif
		//and get the current BT status to do not experience delays
		//#ifdef PBL_SDK_2
		  //handle_bluetooth(bluetooth_connection_service_peek());
		//#elif PBL_SDK_3
		  handle_bluetooth(connection_service_peek_pebble_app_connection());
		//#endif
	
		//setup the timer to refresh the weather info every 30min
	/*
		static char strdebug[15];
		memset(&strdebug[0], 0, sizeof(strdebug));
	  	itoa(timeout_ms, strdebug);
		APP_LOG(APP_LOG_LEVEL_INFO, "weatherTimer timeout_ms: ");
		APP_LOG(APP_LOG_LEVEL_INFO, strdebug);
	*/
	
		weatherTimer = app_timer_register(timeout_ms, weatherTimer_callback, NULL);
	
		//Get weather
		SetupMessages();
	
		//load Temperature
		LoadTemperature();
	
		//Subscribe to the accelerometer event.
        accel_tap_service_subscribe(accel_tap_handler);
        
} 

void loadFontResources(){

		res_t = resource_get_handle(RESOURCE_ID_FUTURA_CONDENSED_53); // Time font
		res_d = resource_get_handle(RESOURCE_ID_FUTURA_17); // Date font for common ASCII languages
		res_temp = resource_get_handle(RESOURCE_ID_FUTURA_43); //Temperature  
		res_u = resource_get_handle(RESOURCE_ID_FUTURA_10); // Last Update font
		res_russian = resource_get_handle(RESOURCE_ID_RUSSIAN_17); // Date in russian
		res_d_rus_forecast = resource_get_handle(RESOURCE_ID_RUSSIAN_14); // Date font for Russian language
		res_asian = resource_get_handle(RESOURCE_ID_ASIAN_17);

		font_date = fonts_load_custom_font(res_d);
		font_time = fonts_load_custom_font(res_t);
		font_temperature = fonts_load_custom_font(res_temp);
		font_update = fonts_load_custom_font(res_u);
		font_russian = fonts_load_custom_font(res_russian);
		font_russian_date_forecast = fonts_load_custom_font(res_d_rus_forecast);
		font_asian = fonts_load_custom_font(res_asian);
	

	}

void unloadFontResource(){
	fonts_unload_custom_font(font_date);
	fonts_unload_custom_font(font_time);
	fonts_unload_custom_font(font_temperature);
	fonts_unload_custom_font(font_update);
	fonts_unload_custom_font(font_russian);
	fonts_unload_custom_font(font_russian_date_forecast);
	fonts_unload_custom_font(font_asian);
}

void loadPersistentData(bool refresh, int intKEY){
	
		/*
		static char strKEY[15];
		memset(&strKEY[0], 0, sizeof(strKEY));
	  	itoa(intKEY, strKEY);
		APP_LOG(APP_LOG_LEVEL_INFO, "loadPersistentData intKEY: ");
		APP_LOG(APP_LOG_LEVEL_INFO, strKEY);
		*/ //DEBUG//
	
	//Weather
	if(persist_exists(WEATHER_TEMPERATURE_KEY) && intKEY == WEATHER_TEMPERATURE_KEY){
		persist_read_string(WEATHER_TEMPERATURE_KEY, temp, sizeof(temp));
			/*		
				APP_LOG(APP_LOG_LEVEL_INFO, "loadPersistentData temp: ");
				APP_LOG(APP_LOG_LEVEL_INFO, temp);
			*/// DEBUG //
	}
	if(persist_exists(WEATHER_ICON_KEY) && intKEY == WEATHER_ICON_KEY){
		ICON_CODE = persist_read_int(WEATHER_ICON_KEY);
	
		/*
		static char strICON[15];
		memset(&strICON[0], 0, sizeof(strICON));
	  	itoa(ICON_CODE, strICON);
		APP_LOG(APP_LOG_LEVEL_INFO, "loadPersistentData ICON_CODE: ");
		APP_LOG(APP_LOG_LEVEL_INFO, strICON);
		*/// DEBUG //
		
	if (weather_image != NULL){gbitmap_destroy(weather_image);}
		weather_image = gbitmap_create_with_resource(WEATHER_ICONS[ICON_CODE]);
		#ifdef PBL_SDK_3
			bitmap_layer_set_bitmap(weather_icon_layer, weather_image);
		#endif
	}
	if(persist_exists(WEATHER_CITY_KEY) && intKEY == WEATHER_CITY_KEY){
		persist_read_string(WEATHER_CITY_KEY, city, sizeof(city));
			/*
				APP_LOG(APP_LOG_LEVEL_INFO, "loadPersistentData city: ");
				APP_LOG(APP_LOG_LEVEL_INFO, city);
			*/// DEBUG //
	}
	if(persist_exists(WEATHER_LAST_UPDATE) && intKEY == WEATHER_LAST_UPDATE){
		persist_read_string(WEATHER_LAST_UPDATE, last_update, sizeof(last_update));
			/*
				APP_LOG(APP_LOG_LEVEL_INFO, "loadPersistentData last_update: ");
				APP_LOG(APP_LOG_LEVEL_INFO, last_update);
			*/// DEBUG //
	}
	
	//Miscellaneous
	if(persist_exists(EXTRA_TIMER_KEY) && intKEY == EXTRA_TIMER_KEY){
		timeout_ms = persist_read_int(EXTRA_TIMER_KEY);
		/*
			static char strTIMER[15];
			memset(&strTIMER[0], 0, sizeof(strTIMER));
			itoa(timeout_ms, strTIMER);
			APP_LOG(APP_LOG_LEVEL_INFO, "loadPersistentData timeout_ms: ");
			APP_LOG(APP_LOG_LEVEL_INFO, strTIMER);
		*/// DEBUG //
	}
	if(persist_exists(language_key) && intKEY == language_key){
		intLanguage = persist_read_int(language_key);
			/*
				static char strLanguage[15];
				memset(&strLanguage[0], 0, sizeof(strLanguage));
				itoa(intLanguage, strLanguage);
				APP_LOG(APP_LOG_LEVEL_INFO, "loadPersistentData intLanguage: ");
				APP_LOG(APP_LOG_LEVEL_INFO, strLanguage);
			*/// DEBUG //
	}
	if(persist_exists(HOURLY_VIBE_KEY) && intKEY == HOURLY_VIBE_KEY){
		blnHourlyVibe = persist_read_int(HOURLY_VIBE_KEY);
			/*
			static char strHourlyVibe[15];
			memset(&strHourlyVibe[0], 0, sizeof(strHourlyVibe));
			itoa(blnHourlyVibe, strHourlyVibe);
			APP_LOG(APP_LOG_LEVEL_INFO, "loadPersistentData blnHourlyVibe: ");
			APP_LOG(APP_LOG_LEVEL_INFO, strHourlyVibe);
		*/// DEBUG //
	}
	if(persist_exists(HOURLY_VIBE_KEY) && intKEY == HOURLY_VIBE_KEY){
		blnHourlyVibe = persist_read_int(HOURLY_VIBE_KEY);
	}	
	if(persist_exists(BACKLIGHT_KEY) && intKEY == BACKLIGHT_KEY){
		blnBacklight= persist_read_int(BACKLIGHT_KEY);
	}
	
	//Forecast
	if(persist_exists(WEATHER_HIGH_KEY) && intKEY == WEATHER_HIGH_KEY){persist_read_string(WEATHER_HIGH_KEY, high, sizeof(high));}
	if(persist_exists(WEATHER_LOW_KEY) && intKEY == WEATHER_LOW_KEY){persist_read_string(WEATHER_LOW_KEY, low, sizeof(low));}
	if(persist_exists(SUNRISE_KEY) && intKEY == SUNRISE_KEY){persist_read_string(SUNRISE_KEY, sunrise, sizeof(sunrise));}
	if(persist_exists(SUNSET_KEY) && intKEY == SUNSET_KEY){persist_read_string(SUNSET_KEY, sunset, sizeof(sunset));}
	if(persist_exists(WIND_KEY) && intKEY == WIND_KEY){persist_read_string(WIND_KEY, wind, sizeof(wind));}
	if(persist_exists(POP_KEY) && intKEY == POP_KEY){persist_read_string(POP_KEY, PoP, sizeof(PoP));}
	if(persist_exists(WDIRECTION_KEY) && intKEY == WDIRECTION_KEY){persist_read_string(WDIRECTION_KEY, strwdirection, sizeof(strwdirection));}
	
	//3-Day Forecast
	if(persist_exists(EXTRA_FORECAST_KEY) && intKEY == EXTRA_FORECAST_KEY){bln3daysForecast = persist_read_int(EXTRA_FORECAST_KEY);}
	if(persist_exists(FORECAST_HIGH1_KEY) && intKEY == FORECAST_HIGH1_KEY){persist_read_string(FORECAST_HIGH1_KEY, day1H, sizeof(day1H));}
	if(persist_exists(FORECAST_LOW1_KEY) && intKEY == FORECAST_LOW1_KEY){	persist_read_string(FORECAST_LOW1_KEY, day1L, sizeof(day1L));}
	if(persist_exists(FORECAST_HIGH2_KEY) && intKEY == FORECAST_HIGH2_KEY){	persist_read_string(FORECAST_HIGH2_KEY, day2H, sizeof(day2H));}
	if(persist_exists(FORECAST_LOW2_KEY) && intKEY == FORECAST_LOW2_KEY){	persist_read_string(FORECAST_LOW2_KEY, day2L, sizeof(day2L));}
	if(persist_exists(FORECAST_HIGH3_KEY) && intKEY == FORECAST_HIGH3_KEY){	persist_read_string(FORECAST_HIGH3_KEY, day3H, sizeof(day3H));}
	if(persist_exists(FORECAST_LOW3_KEY) && intKEY == FORECAST_LOW3_KEY){	persist_read_string(FORECAST_LOW3_KEY, day3L, sizeof(day3L));}
	
	//if we want to refresh the on screen info, refresh the layers.
	if(refresh){refreshLayers();}
}

void refreshLayers(){
	
	//Init the date
	getDate();
}

/*****************/
/* DATE AND TIME */
/*****************/

	void LoadDigital(){
		

		//Weekday
			Weekday_Layer = text_layer_create(WEEKDAY_FRAME);
			text_layer_set_text_alignment(Weekday_Layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter,GTextAlignmentLeft));
			text_layer_set_text_color(Weekday_Layer, GColorWhite);
			text_layer_set_background_color(Weekday_Layer, GColorClear);
			text_layer_set_font(Weekday_Layer, font_date);
			layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Weekday_Layer));
		 	 
		//Date
			date_layer = text_layer_create(DATE_FRAME);
			text_layer_set_text_alignment(date_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter,GTextAlignmentRight));
			text_layer_set_text_color(date_layer, GColorWhite);
			text_layer_set_background_color(date_layer, GColorClear);
			text_layer_set_font(date_layer, font_date);
			layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(date_layer));

		//Time
			Time_Layer = text_layer_create(TIME_FRAME);
			text_layer_set_text_alignment(Time_Layer, GTextAlignmentCenter);

			//Define the text color based on the Pebble model
			#ifdef PBL_COLOR
				text_layer_set_text_color(Time_Layer, GColorChromeYellow);
			#else
				text_layer_set_text_color(Time_Layer, GColorWhite);
			#endif

			text_layer_set_background_color(Time_Layer, GColorClear);
			text_layer_set_font(Time_Layer, font_time);
			layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Time_Layer));
		
		//Add the Battery Layer
		//#ifdef PBL_SDK_3
			  Layer *window_layer = window_get_root_layer(mainWindow);
			  GRect bounds = layer_get_bounds(window_layer);
			  battery_layer = layer_create(bounds);
			  layer_set_update_proc(battery_layer, battery_update_proc);
			  layer_add_child(window_layer, battery_layer);
		//#endif 
		
		#ifdef PBL_RECT
			Batt_Layer = text_layer_create(BATT_FRAME);
			text_layer_set_text_alignment(Batt_Layer, GTextAlignmentCenter);
			text_layer_set_text_color(Batt_Layer, GColorWhite);
			text_layer_set_background_color(Batt_Layer, GColorClear);
			text_layer_set_font(Batt_Layer, font_update);
			layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Batt_Layer));
		#endif
		
		//Bluetooth connection
		
		#ifdef PBL_ROUND
			//After the date & time, draw a line to separate from weather
			line = text_layer_create(BT_FRAME);
			text_layer_set_background_color(line, GColorWhite);
			layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(line));
		#else
			BT_icon_layer = bitmap_layer_create(BT_FRAME);
			bitmap_layer_set_bitmap(BT_icon_layer, NULL);
			layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(BT_icon_layer));
      	#endif

		
//APP_LOG(APP_LOG_LEVEL_DEBUG, "LoadDigital: Heap free is %u bytes", heap_bytes_free());
		
	}//LoadMainWindow END
	void unloadDigital(){
		text_layer_destroy(Weekday_Layer);
		text_layer_destroy(date_layer);
		text_layer_destroy(Time_Layer);
		
APP_LOG(APP_LOG_LEVEL_DEBUG, "unloadDigital: Heap free is %u bytes", heap_bytes_free());
	}

	//**************************//
	//** Get the current date **//
	//**************************//
	void getDate(){

		//Get the date
		time_t actualPtr = time(NULL);
		struct tm *tz1Ptr = localtime(&actualPtr);
		//get the local date
		char *sys_locale = setlocale(LC_ALL, "");
		//get the date and month numbers
		intDay = tz1Ptr->tm_mday;
		intMonth = tz1Ptr->tm_mon + 1; //tm_mon sets january to month 0.
		intWDay = tz1Ptr->tm_wday; 
		
		//clean up the day, date and weekday char arrays
		memset(&weekday_text[0], 0, sizeof(weekday_text));
		memset(&month_text[0], 0, sizeof(month_text));
		memset(&day_month[0], 0, sizeof(day_month));
		memset(&weekday1_text[0], 0, sizeof(weekday1_text));
		memset(&weekday2_text[0], 0, sizeof(weekday2_text));
		memset(&weekday3_text[0], 0, sizeof(weekday3_text));
				
		
		//control that people using old settings page are now referencing to the new asian translation method
		//if (intLanguage == 98){intLanguage=20;}
		//if (intLanguage == 99){intLanguage=19;}
		
		//control that app doesn't crash if selected language doesn't exist (version control)
		if (intLanguage > intLangCounter){intLanguage = 100;} //set to watch language 

		
		//if russian, change the font type
		if (intLanguage == 18){
			text_layer_set_font(date_layer, font_russian);
			text_layer_set_font(Weekday_Layer, font_russian);
		}
		else if (intLanguage == 19 || intLanguage == 20){
			text_layer_set_font(date_layer, font_asian);
			text_layer_set_font(Weekday_Layer, font_asian);
		}
		else{
			text_layer_set_font(date_layer, font_date);
			text_layer_set_font(Weekday_Layer, font_date);
		}
		
		
		if (intLanguage==100){
			if (strcmp("en_US", sys_locale) == 0) {
				//Get the USA format
				strftime(month_text,sizeof(month_text),"%B %e",tz1Ptr);
			}
			else{
				//Get the Europe's format
				strftime(month_text,sizeof(month_text),"%e %B",tz1Ptr);
			}
			strftime(weekday_text,sizeof(weekday_text),"%A",tz1Ptr);
			text_layer_set_text(date_layer,month_text); 
			//Get the 3-day forecast
			struct tm *auxPtr = localtime(&actualPtr);
			//Since mktime() is not realible in Pebble's firmware, use PUtils to built the dual time.
			auxPtr->tm_mday +=1;
			time_t dayPlusOne = p_mktime(auxPtr);
			struct tm *wd1Ptr = gmtime(&dayPlusOne);
			strftime(weekday1_text,sizeof(weekday1_text),PBL_IF_ROUND_ELSE("%a","%A"),wd1Ptr);
			
			auxPtr->tm_mday +=1;
			time_t dayPlusTwo = p_mktime(auxPtr);
			struct tm *wd2Ptr = gmtime(&dayPlusTwo);
			strftime(weekday2_text,sizeof(weekday2_text),PBL_IF_ROUND_ELSE("%a","%A"),wd2Ptr);
			
			auxPtr->tm_mday +=1;
			time_t dayPlusThree = p_mktime(auxPtr);
			struct tm *wd3Ptr = gmtime(&dayPlusThree);
			strftime(weekday3_text,sizeof(weekday3_text),PBL_IF_ROUND_ELSE("%a","%A"),wd3Ptr);
		}//WATCH LANGUAGE
		else{
			//translate the day of the week
			char *translatedDay = translateDay(intWDay, intLanguage, false);
			memcpy(&weekday_text, translatedDay, strlen(translatedDay)+1);
			//translate the 3-day forecast
			//week day + 1
				int intDayPlusOne = intWDay+1;
				if (intDayPlusOne > 6){intDayPlusOne = intDayPlusOne-7;}
				char *translatedDay1 = translateDay(intDayPlusOne, intLanguage, PBL_IF_ROUND_ELSE(true,false));
				//snprintf(weekday1_text, strlen(translatedDay1)+1,translatedDay1);
				memcpy(&weekday1_text, translatedDay1, strlen(translatedDay1)+1);
			//week day + 2
				int intDayPlusTwo = intWDay+2;
				if (intDayPlusTwo > 6){intDayPlusTwo = intDayPlusTwo-7;}
				char *translatedDay2 = translateDay(intDayPlusTwo, intLanguage, PBL_IF_ROUND_ELSE(true,false));
				//snprintf(weekday2_text, strlen(translatedDay2)+1,translatedDay2);
				memcpy(&weekday2_text, translatedDay2, strlen(translatedDay2)+1);
			//week day + 3
				int intDayPlusThree = intWDay+3;
				if (intDayPlusThree > 6){intDayPlusThree = intDayPlusThree-7;}
				char *translatedDay3 = translateDay(intDayPlusThree, intLanguage, PBL_IF_ROUND_ELSE(true,false));
				//snprintf(weekday3_text, strlen(translatedDay3)+1,translatedDay3);
				memcpy(&weekday3_text, translatedDay3, strlen(translatedDay3)+1);
								
			//translate the month
			char *translatedMonth = translateMonth(intMonth, intLanguage);
			memcpy(&month_text, translatedMonth, strlen(translatedMonth)+1);
			
			//concatenate the day of the month
			strftime(day_month,sizeof(day_month),"%e",tz1Ptr);
				
			if ((intLanguage == 13)||(intLanguage == 4)){
				text_layer_set_text(date_layer,strncat(month_text,day_month,strlen(month_text)));
				//text_layer_set_text(date_layer,strcat(translateMonth(intMonth, intLanguage),day_month));
			} //Czech or Hungarian 
			//else if (intLanguage == 19){text_layer_set_text(date_layer,strcat(translateMonth(intMonth, intLanguage),chinese_numbers[intDay]));} //Chinese
			else if (intLanguage == 19){text_layer_set_text(date_layer,strcat(translateMonth(intMonth, intLanguage),japanese_numbers[intDay]));} //Chinese
			else if (intLanguage == 20){text_layer_set_text(date_layer,strcat(translateMonth(intMonth, intLanguage),japanese_numbers[intDay]));} //Japanese
			else{
				text_layer_set_text(date_layer,strncat(day_month,month_text,strlen(month_text)));
				//text_layer_set_text(date_layer,strcat(day_month,translateMonth(intMonth, intLanguage)));
			}
		/*		
			APP_LOG(APP_LOG_LEVEL_INFO, "getDate date_layer: ");
			APP_LOG(APP_LOG_LEVEL_INFO, text_layer_get_text(date_layer));
			//DEBUG//
		*/
		}


		text_layer_set_text(Weekday_Layer,weekday_text); //Update the weekday layer 
		//text_layer_set_text(Weekday_Layer,translateDay(intWDay, intLanguage)); //Update the weekday layer 

	}

	/********************/
	/* Get Current time */
	/********************/
	void getTime(){

		time_t actualPtr = time(NULL);
		struct tm *tz1Ptr = localtime(&actualPtr);

		if (clock_is_24h_style()){strftime(time_text, sizeof(time_text), "%H:%M", tz1Ptr);}
		else {strftime(time_text, sizeof(time_text), "%I:%M", tz1Ptr);}	

		//Remove the leading 0s
		if (time_text[0]=='0') {memcpy(&time_text," ",1);}

		//Set the time to the Time Layer
		text_layer_set_text(Time_Layer, time_text);

	}

	/***************/
	/* Tick Events */
	/***************/
	void handle_tick(struct tm *tick_time, TimeUnits units_changed){

		if (units_changed & MINUTE_UNIT){
			getTime();
			/*
			if (intLanguage == 19){
				getDate();
			} //if chinese refresh the date every minute
			*/
		}
		if (units_changed & HOUR_UNIT){
			if (blnHourlyVibe){
				hourlyVibe(DoNotDisturb(tick_time->tm_hour, tick_time->tm_min,HOURLY_VIBE_START_KEY,HOURLY_VIBE_END_KEY));
			}
		}

		if (units_changed & DAY_UNIT){
			getDate();
		}

	} //HANDLE_TICK

	void SubscribeTickEvent(){

		time_t now = time(NULL);
		struct tm *current_time = localtime(&now);

		handle_tick(current_time, MINUTE_UNIT);
		tick_timer_service_subscribe(MINUTE_UNIT, &handle_tick);

	}

/***********/
/* WEATHER */
/***********/

void LoadTemperature(){	
	
	  //Track that we are displaying the primary screen
		blnForecast = false;
	
      //Weather Icon
      	weather_icon_layer = bitmap_layer_create(WEATHER_FRAME);
		//if there weather_image contains data, do not load again (avoid memory issues)
		weather_image = gbitmap_create_with_resource(WEATHER_ICONS[ICON_CODE]);
      	bitmap_layer_set_bitmap(weather_icon_layer, weather_image);
      	layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(weather_icon_layer));
      //Temperature
      	Temperature_Layer = text_layer_create(TEMPERATURE_FRAME);
      	text_layer_set_text_alignment(Temperature_Layer, PBL_IF_ROUND_ELSE(GTextAlignmentRight, GTextAlignmentCenter));
    	text_layer_set_text_color(Temperature_Layer, GColorWhite);  
		text_layer_set_background_color(Temperature_Layer, GColorClear);	
		text_layer_set_font(Temperature_Layer, font_temperature);
		layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Temperature_Layer));
		text_layer_set_text(Temperature_Layer, temp);
	//Location
      	Location_Layer = text_layer_create(LOCATION_FRAME);
    	text_layer_set_text_color(Location_Layer, GColorWhite);
  	  	text_layer_set_text_alignment(Location_Layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentRight));
		text_layer_set_background_color(Location_Layer, GColorClear);
		text_layer_set_font(Location_Layer, font_update);
		layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Location_Layer));
		text_layer_set_text(Location_Layer, city);
	//Last Update
      	Last_Update = text_layer_create(LAST_UPDATE_FRAME);
    	text_layer_set_text_color(Last_Update, GColorWhite);
		text_layer_set_background_color(Last_Update, GColorClear);	
		text_layer_set_font(Last_Update, font_update);
		text_layer_set_text_alignment(Last_Update, GTextAlignmentRight);
		layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Last_Update));
		text_layer_set_text(Last_Update, last_update);
	
	//check the Pebble model to determine if the image is colored or not
	#ifdef PBL_BW
		bitmap_layer_set_compositing_mode(weather_icon_layer, GCompOpAssign);
	#elif PBL_COLOR
		bitmap_layer_set_compositing_mode(weather_icon_layer, GCompOpSet);
	#endif

	
//APP_LOG(APP_LOG_LEVEL_DEBUG, "LoadTemperature: Heap free is %u bytes", heap_bytes_free());
	
} //LoadTemperature - END
void UnloadTemperature(){
	//Destroy the temperature Layer
	if(Temperature_Layer){text_layer_destroy(Temperature_Layer);}
	if(weather_icon_layer){bitmap_layer_destroy(weather_icon_layer);}
	if(Location_Layer){text_layer_destroy(Location_Layer);}
	if(Last_Update){text_layer_destroy(Last_Update);}
	//kill the weather icon
	gbitmap_destroy(weather_image);
	
//APP_LOG(APP_LOG_LEVEL_DEBUG, "unloadTemperature: Heap free is %u bytes", heap_bytes_free());
}

void loadForecastIcons(){

	high_image = gbitmap_create_with_resource(RESOURCE_ID_HIGH);
	low_image = gbitmap_create_with_resource(RESOURCE_ID_LOW);
	sunrise_image = gbitmap_create_with_resource(RESOURCE_ID_SUNRISE);
	sunset_image = gbitmap_create_with_resource(RESOURCE_ID_SUNSET);
	wind_image = gbitmap_create_with_resource(RESOURCE_ID_WIND_ICON);
	rain_image = gbitmap_create_with_resource(RESOURCE_ID_ICON_RAIN_SMALL);
}
void unloadForecastIcons(){

	gbitmap_destroy(high_image);
	gbitmap_destroy(low_image);
	gbitmap_destroy(sunrise_image);
	gbitmap_destroy(sunset_image);
	gbitmap_destroy(wind_image);
	gbitmap_destroy(rain_image);
}

void LoadForecast(){
	
	//Track that we are displaying the secondary screen
	blnForecast = true;
	
	//Unload the temperature layers
	UnloadTemperature();
	
	//Load the forecast images
	loadForecastIcons();
  //animate the time (easing out)
      #ifdef PBL_ROUND
        //take the day out
        static PropertyAnimation* weekday_animation;
        weekday_animation = property_animation_create_layer_frame((Layer*)Weekday_Layer, &WEEKDAY_FRAME, &GRect(-1000,-1000,1,1));
        animation_schedule((Animation*) weekday_animation);
      
        //take the date out
        static PropertyAnimation* date_animation;
        date_animation = property_animation_create_layer_frame((Layer*)date_layer, &DATE_FRAME, &GRect(-1000,-1000,1,1));
        animation_schedule((Animation*) date_animation);
        
        //scroll up the time
        static PropertyAnimation* time_animation;
        time_animation = property_animation_create_layer_frame((Layer*)Time_Layer, &TIME_FRAME, &TIME_FRAME_ANIMATED);
        animation_schedule((Animation*) time_animation);
        text_layer_set_text_alignment(Time_Layer, GTextAlignmentCenter);
      
	  /*
        //Remove the seconds and AM/PM indicator
        if (blnseconds){
            //seconds
            static PropertyAnimation* seconds_animation;
            seconds_animation = property_animation_create_layer_frame((Layer*)seconds_layer, &SECONDS_FRAME_CHALK, &GRect(-1000,-1000,1,1));
            animation_schedule((Animation*) seconds_animation);
        }
        if(!clock_is_24h_style()){
            //AM/PM indicator
            static PropertyAnimation* ampm_animation;
            ampm_animation = property_animation_create_layer_frame((Layer*)ampm_layer, &AMPM_FRAME_CHALK, &GRect(-1000,-1000,1,1));
            animation_schedule((Animation*) ampm_animation);
          
        }
      */
	  
        //scroll up the bluetooth indicator
        static PropertyAnimation* bt_animation;
        bt_animation = property_animation_create_layer_frame((Layer*)line, &GRect(20, 109, 140, 2), &GRect(20, 81, 140, 2));
        animation_schedule((Animation*) bt_animation);
      #endif

	//Create the Forecast Layers

	//HIGH
	High_Layer = text_layer_create(HIGH_FRAME);
    text_layer_set_font(High_Layer, font_date);
	text_layer_set_text_color(High_Layer, GColorWhite);
	text_layer_set_background_color(High_Layer, GColorClear);
	text_layer_set_text_alignment(High_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(High_Layer));
	
	persist_read_string(WEATHER_HIGH_KEY, high, sizeof(high));
	text_layer_set_text(High_Layer,high);
	

	//Display the High icon
	high_icon_layer = bitmap_layer_create(HIGH_ICON_FRAME);
	bitmap_layer_set_bitmap(high_icon_layer, high_image);
  	layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(high_icon_layer));
	
	
	//LOW
	Low_Layer = text_layer_create(LOW_FRAME);
  	text_layer_set_font(Low_Layer, font_date);
	text_layer_set_text_color(Low_Layer, GColorWhite);
	text_layer_set_background_color(Low_Layer, GColorClear);
	text_layer_set_text_alignment(Low_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Low_Layer));
	
	persist_read_string(WEATHER_LOW_KEY, low, sizeof(low));
	text_layer_set_text(Low_Layer,low);

	
	//Display the Low icon
	low_icon_layer = bitmap_layer_create(LOW_ICON_FRAME);
	bitmap_layer_set_bitmap(low_icon_layer, low_image);
    layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(low_icon_layer));
	
	//SUNRISE
	Sunrise_Layer = text_layer_create(SUNRISE_FRAME);
  	text_layer_set_font(Sunrise_Layer, font_date);
	text_layer_set_text_color(Sunrise_Layer, GColorWhite);
	text_layer_set_background_color(Sunrise_Layer, GColorClear);
	text_layer_set_text_alignment(Sunrise_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Sunrise_Layer));
	
	persist_read_string(SUNRISE_KEY, sunrise, sizeof(sunrise));
	text_layer_set_text(Sunrise_Layer,formatSunrise(sunrise));
	
	//APP_LOG(APP_LOG_LEVEL_INFO, "loadPersistentData llego hasta el SUNRISE");
	//Display the sunset icon
	sunrise_icon_layer = bitmap_layer_create(SUNRISE_ICON_FRAME);
	bitmap_layer_set_bitmap(sunrise_icon_layer, sunrise_image);
  	layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(sunrise_icon_layer));
	
	//SUNSET
	Sunset_Layer = text_layer_create(SUNSET_FRAME);	
  	text_layer_set_font(Sunset_Layer, font_date);
	text_layer_set_text_color(Sunset_Layer, GColorWhite);
	text_layer_set_background_color(Sunset_Layer, GColorClear);
	text_layer_set_text_alignment(Sunset_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Sunset_Layer));
	
	persist_read_string(SUNSET_KEY, sunset, sizeof(sunset));
	text_layer_set_text(Sunset_Layer,formatSunset(sunset));
	
	//APP_LOG(APP_LOG_LEVEL_INFO, "loadPersistentData llego hasta el SUNSET");
	//Display the sunset icon
	sunset_icon_layer = bitmap_layer_create(SUNSET_ICON_FRAME);
	bitmap_layer_set_bitmap(sunset_icon_layer, sunset_image);
  	layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(sunset_icon_layer));
  
	//WIND SPEED
	Wind_Layer = text_layer_create(WIND_FRAME);
  	text_layer_set_text_alignment(Wind_Layer, PBL_IF_ROUND_ELSE(GTextAlignmentLeft, GTextAlignmentRight));
	text_layer_set_font(Wind_Layer, font_date);
	text_layer_set_text_color(Wind_Layer, GColorWhite);
	text_layer_set_background_color(Wind_Layer, GColorClear);
	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Wind_Layer));
	
	persist_read_string(WIND_KEY, wind, sizeof(wind));
	text_layer_set_text(Wind_Layer,wind);
	
	//WIND DIRECTION
	WDirection_Layer = text_layer_create(WDIRECTION_FRAME);	
  	text_layer_set_text_alignment(WDirection_Layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentRight)); 
	text_layer_set_text_color(WDirection_Layer, GColorWhite);
	text_layer_set_background_color(WDirection_Layer, GColorClear);
	text_layer_set_font(WDirection_Layer, font_update);
	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(WDirection_Layer));
	
	persist_read_string(WDIRECTION_KEY, strwdirection, sizeof(strwdirection));
	text_layer_set_text(WDirection_Layer,strwdirection);

	//APP_LOG(APP_LOG_LEVEL_INFO, "loadPersistentData llego hasta el WIND");
    //Display the wind icon
	wind_icon_layer = bitmap_layer_create(WIND_ICON_FRAME);
	bitmap_layer_set_bitmap(wind_icon_layer, wind_image);
  	layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(wind_icon_layer));
	
  
	
	//RAIN PROBABILITY	
	PoP_Layer = text_layer_create(POP_FRAME);
  	text_layer_set_font(PoP_Layer, PBL_IF_ROUND_ELSE(font_update,font_date));
	text_layer_set_text_color(PoP_Layer, GColorWhite);
	text_layer_set_background_color(PoP_Layer, GColorClear);
	text_layer_set_text_alignment(PoP_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(PoP_Layer));
	
	persist_read_string(POP_KEY, PoP, sizeof(PoP));
	text_layer_set_text(PoP_Layer,PoP);
	
	//APP_LOG(APP_LOG_LEVEL_INFO, "loadPersistentData llego hasta el RAIN");
	//Rain ICON
	rain_icon_layer = bitmap_layer_create(RAIN_ICON_FRAME);
	bitmap_layer_set_bitmap(rain_icon_layer, rain_image);
  	layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(rain_icon_layer));
	
	
	//refresh the tap counter 
	TapCount = 0;

	
	//APP_LOG(APP_LOG_LEVEL_INFO, "loadPersistentData llego hasta el forecastTIMER");
	//setup the timer to set back the temperature after 5sec
	forecastTimer = app_timer_register(ESDuration_ms, forecast_callback, NULL);
	
	
//APP_LOG(APP_LOG_LEVEL_DEBUG, "LoadForecast: Heap free is %u bytes", heap_bytes_free());

} //LoadForecast - END
void UnloadForecast(){
	//Destroy the forecast Layers
	if(High_Layer){text_layer_destroy(High_Layer);}
	if(Low_Layer){text_layer_destroy(Low_Layer);}
	if(Sunrise_Layer){text_layer_destroy(Sunrise_Layer);}
	if(Sunset_Layer){text_layer_destroy(Sunset_Layer);}
	if(Wind_Layer){text_layer_destroy(Wind_Layer);}
	if(WDirection_Layer){text_layer_destroy(WDirection_Layer);}
	if(sunrise_icon_layer){bitmap_layer_destroy(sunrise_icon_layer);}
	if(sunset_icon_layer){bitmap_layer_destroy(sunset_icon_layer);}
	if(high_icon_layer){bitmap_layer_destroy(high_icon_layer);}
	if(low_icon_layer){bitmap_layer_destroy(low_icon_layer);}
	if(wind_icon_layer){bitmap_layer_destroy(wind_icon_layer);}
	//printf ("%s \n", "Unload moon icon");
	//if(moon_icon_layer){bitmap_layer_destroy(moon_icon_layer);}
	if(PoP_Layer){text_layer_destroy(PoP_Layer);}
	if(rain_icon_layer){bitmap_layer_destroy(rain_icon_layer);}
	//unload the forecast icons
	unloadForecastIcons();
	
//APP_LOG(APP_LOG_LEVEL_DEBUG, "unloadForecast: Heap free is %u bytes", heap_bytes_free());
}

void load3DaysIcons(){

	code1 = persist_read_int(FORECAST_CODE1_KEY);
	forecast1 = gbitmap_create_with_resource(WEATHER_ICONS_SMALL[code1]);
	
	code2 = persist_read_int(FORECAST_CODE2_KEY);
	forecast2 = gbitmap_create_with_resource(WEATHER_ICONS_SMALL[code2]);
	
	code3 = persist_read_int(FORECAST_CODE3_KEY);
	forecast3 = gbitmap_create_with_resource(WEATHER_ICONS_SMALL[code3]);
	
}
void unload3DaysIcons(){
	gbitmap_destroy(forecast1);
	gbitmap_destroy(forecast2);
	gbitmap_destroy(forecast3);
}

void Load3Days(){
	
	//load the weather images
	load3DaysIcons();
	
//DAY 1
	//Weekday	
	 	Day1_Layer = text_layer_create(FORECAST_DAY1_FRAME);
		text_layer_set_text_color(Day1_Layer, GColorWhite);
		text_layer_set_background_color(Day1_Layer, GColorClear);
		if (intLanguage == 18){
        	text_layer_set_font(Day1_Layer, font_russian_date_forecast);
			}
		else if (intLanguage == 19 || intLanguage == 20){
			text_layer_set_font(Day1_Layer, PBL_IF_ROUND_ELSE(font_date,font_asian));
			}
		else{
			text_layer_set_font(Day1_Layer, font_date);
			}
		text_layer_set_text_alignment(Day1_Layer, GTextAlignmentLeft);
		layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Day1_Layer));
	
		text_layer_set_text(Day1_Layer,weekday1_text);


	//Display the weather icon
	forecast1_layer = bitmap_layer_create(FORECAST_CODE1_FRAME);
	bitmap_layer_set_bitmap(forecast1_layer, forecast1);
    layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(forecast1_layer));


	//High for the day	
	High1_Layer = text_layer_create(FORECAST_HIGH1_FRAME);
	text_layer_set_text_color(High1_Layer, GColorWhite);
	text_layer_set_background_color(High1_Layer, GColorClear);
	text_layer_set_font(High1_Layer, font_update);
  	PBL_IF_RECT_ELSE(text_layer_set_text_alignment(High1_Layer, GTextAlignmentRight),text_layer_set_text_alignment(High1_Layer, GTextAlignmentLeft)); 
	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(High1_Layer));
	
	persist_read_string(FORECAST_HIGH1_KEY, day1H, sizeof(day1H));
	text_layer_set_text(High1_Layer,day1H);
	
	
	//Low for the day
	Low1_Layer = text_layer_create(FORECAST_LOW1_FRAME);
	text_layer_set_text_color(Low1_Layer, GColorWhite);
	text_layer_set_background_color(Low1_Layer, GColorClear);
	text_layer_set_font(Low1_Layer, font_update);
  	PBL_IF_RECT_ELSE(text_layer_set_text_alignment(Low1_Layer, GTextAlignmentRight),text_layer_set_text_alignment(Low1_Layer, GTextAlignmentLeft)); 
	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Low1_Layer));
	
	persist_read_string(FORECAST_LOW1_KEY, day1L, sizeof(day1L));
	text_layer_set_text(Low1_Layer,day1L);
	
	

//DAY 2
	//Weekday	
		Day2_Layer = text_layer_create(FORECAST_DAY2_FRAME);
		text_layer_set_text_color(Day2_Layer, GColorWhite);
		text_layer_set_background_color(Day2_Layer, GColorClear);
		if (intLanguage == 18){
        	text_layer_set_font(Day2_Layer, font_russian_date_forecast);
			}
		else if (intLanguage == 19 || intLanguage == 20){
			text_layer_set_font(Day2_Layer, PBL_IF_ROUND_ELSE(font_date,font_asian));
			}
		else{
			text_layer_set_font(Day2_Layer, font_date);
			}
		text_layer_set_text_alignment(Day2_Layer, GTextAlignmentLeft);
		layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Day2_Layer));

		text_layer_set_text(Day2_Layer,weekday2_text);
		
	
	//Display the weather icon
	forecast2_layer = bitmap_layer_create(FORECAST_CODE2_FRAME);
	bitmap_layer_set_bitmap(forecast2_layer, forecast2);
    layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(forecast2_layer));
	
	//High for the day
	High2_Layer = text_layer_create(FORECAST_HIGH2_FRAME);
	text_layer_set_text_color(High2_Layer, GColorWhite);
	text_layer_set_background_color(High2_Layer, GColorClear);
	text_layer_set_font(High2_Layer, font_update);
  	PBL_IF_RECT_ELSE(text_layer_set_text_alignment(High2_Layer, GTextAlignmentRight),text_layer_set_text_alignment(High2_Layer, GTextAlignmentLeft)); 
	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(High2_Layer));
	
	persist_read_string(FORECAST_HIGH2_KEY, day2H, sizeof(day2H));
	text_layer_set_text(High2_Layer,day2H);
	
	//Low for the day
	Low2_Layer = text_layer_create(FORECAST_LOW2_FRAME);
	text_layer_set_text_color(Low2_Layer, GColorWhite);
	text_layer_set_background_color(Low2_Layer, GColorClear);
	text_layer_set_font(Low2_Layer, font_update);
  	PBL_IF_RECT_ELSE(text_layer_set_text_alignment(Low2_Layer, GTextAlignmentRight),text_layer_set_text_alignment(Low2_Layer, GTextAlignmentLeft));
	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Low2_Layer));
	
	persist_read_string(FORECAST_LOW2_KEY, day2L, sizeof(day2L));
	text_layer_set_text(Low2_Layer,day2L);
	
	
//DAY 3
	//Weekday
		Day3_Layer = text_layer_create(FORECAST_DAY3_FRAME);
		text_layer_set_text_color(Day3_Layer, GColorWhite);
		text_layer_set_background_color(Day3_Layer, GColorClear);
		if (intLanguage == 18){
        	text_layer_set_font(Day3_Layer, font_russian_date_forecast);
			}
		else if (intLanguage == 19 || intLanguage == 20){
			text_layer_set_font(Day3_Layer, PBL_IF_ROUND_ELSE(font_date,font_asian));
			}
		else{
			text_layer_set_font(Day3_Layer, font_date);
			}
		text_layer_set_text_alignment(Day3_Layer, GTextAlignmentLeft);
		layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Day3_Layer));

		text_layer_set_text(Day3_Layer,weekday3_text);
	
	//Display the weather icon
	forecast3_layer = bitmap_layer_create(FORECAST_CODE3_FRAME);
	bitmap_layer_set_bitmap(forecast3_layer, forecast3);
    layer_add_child(window_get_root_layer(mainWindow), bitmap_layer_get_layer(forecast3_layer));
	
	
	//High for the day	
	High3_Layer = text_layer_create(FORECAST_HIGH3_FRAME);
	text_layer_set_text_color(High3_Layer, GColorWhite);
	text_layer_set_background_color(High3_Layer, GColorClear);
	text_layer_set_font(High3_Layer, font_update);
  	PBL_IF_RECT_ELSE(text_layer_set_text_alignment(High3_Layer, GTextAlignmentRight),text_layer_set_text_alignment(High3_Layer, GTextAlignmentLeft));
	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(High3_Layer));
	
	persist_read_string(FORECAST_HIGH3_KEY, day3H, sizeof(day3H));
	text_layer_set_text(High3_Layer,day3H);
	
	//Low for the day	
	Low3_Layer = text_layer_create(FORECAST_LOW3_FRAME);
	text_layer_set_text_color(Low3_Layer, GColorWhite);
	text_layer_set_background_color(Low3_Layer, GColorClear);
	text_layer_set_font(Low3_Layer, font_update);
  	PBL_IF_RECT_ELSE(text_layer_set_text_alignment(Low3_Layer, GTextAlignmentRight),text_layer_set_text_alignment(Low3_Layer, GTextAlignmentLeft));
	layer_add_child(window_get_root_layer(mainWindow), text_layer_get_layer(Low3_Layer));
	
	persist_read_string(FORECAST_LOW3_KEY, day3L, sizeof(day3L));
	text_layer_set_text(Low3_Layer,day3L);
	
	//setup the timer to set back the temperature after 5sec
	forecastTimer = app_timer_register(ESDuration_ms, forecast3Days_callback, NULL);
	
	
//APP_LOG(APP_LOG_LEVEL_DEBUG, "Load3Days: Heap free is %u bytes", heap_bytes_free());
	
} 
void Unload3Days(){
	
	//Destroy the  Layers
	if(Day1_Layer){text_layer_destroy(Day1_Layer);}
	if(High1_Layer){text_layer_destroy(High1_Layer);}
	if(Low1_Layer){text_layer_destroy(Low1_Layer);}
	if(forecast1_layer){bitmap_layer_destroy(forecast1_layer);}
		
	if(Day2_Layer){text_layer_destroy(Day2_Layer);}
	if(High2_Layer){text_layer_destroy(High2_Layer);}
	if(Low2_Layer){text_layer_destroy(Low2_Layer);}
	if(forecast2_layer){bitmap_layer_destroy(forecast2_layer);}
	
	if(Day3_Layer){text_layer_destroy(Day3_Layer);}
	if(High3_Layer){text_layer_destroy(High3_Layer);}
	if(Low3_Layer){text_layer_destroy(Low3_Layer);}
	if(forecast3_layer){bitmap_layer_destroy(forecast3_layer);}
	
	
//APP_LOG(APP_LOG_LEVEL_DEBUG, "Unload3Days: Heap free is %u bytes", heap_bytes_free());
}

//*****************//
// TIMER callbacks //
//*****************//
static void fetchWeather(void) {

         Tuplet value = TupletInteger(5, 0);
        
         DictionaryIterator *iter;
         app_message_outbox_begin(&iter);
        
         if (iter == NULL) {
                return;
         }
        
         dict_write_tuplet(iter, &value);
         dict_write_end(iter);
        
         app_message_outbox_send();
	
}

static void weatherTimer_callback(void *context) {

		//Developer vibe: confirm that timer is not killed
		//vibes_double_pulse();
	
		if(persist_exists(EXTRA_TIMER_KEY)){timeout_ms = persist_read_int(EXTRA_TIMER_KEY);}
	
		/*
		static char strdebug[15];
		memset(&strdebug[0], 0, sizeof(strdebug));
	  	itoa(timeout_ms, strdebug);
		APP_LOG(APP_LOG_LEVEL_INFO, "weatherTimer timeout_ms: ");
		APP_LOG(APP_LOG_LEVEL_INFO, strdebug);
		*/ // DEBUG //
	
        weatherTimer = app_timer_register(timeout_ms, weatherTimer_callback, NULL);

        //Refresh the weather
        fetchWeather();
	       

}

static void forecast_callback(void *context) {
        //Unload the forecast screen
		UnloadForecast();
		if (bln3daysForecast){
			//LoadTemperature();
			Load3Days();
		}
		else{
	
			#ifdef PBL_ROUND
				//take the day in
				static PropertyAnimation* weekday_animation;
				weekday_animation = property_animation_create_layer_frame((Layer*)Weekday_Layer, &GRect(-1000,-1000,1,1),&WEEKDAY_FRAME);
				animation_schedule((Animation*) weekday_animation);

				//take the date in
				static PropertyAnimation* date_animation;
				date_animation = property_animation_create_layer_frame((Layer*)date_layer, &GRect(-1000,-1000,1,1),&DATE_FRAME);
				animation_schedule((Animation*) date_animation);

				//scroll down the time
				static PropertyAnimation* time_animation;

				time_animation = property_animation_create_layer_frame((Layer*)Time_Layer, &TIME_FRAME_ANIMATED, &TIME_FRAME);

				animation_schedule((Animation*) time_animation);

				//scroll down the bluetooth indicator
				static PropertyAnimation* bt_animation;
				bt_animation = property_animation_create_layer_frame((Layer*)line, &GRect(20, 81, 140, 2),&GRect(20, 109, 140, 2));
				animation_schedule((Animation*) bt_animation);
			#endif

			//If the backlight is on, turn it off and cancel the timer
			if(blnBacklight){app_timer_cancel(BackLightTimer);}
			//Set the temperature back
			LoadTemperature();
			
		}

}

static void forecast3Days_callback(void *context) {
       
		
		//Refresh the weather
		Unload3Days();
		//unload the weather images
		unload3DaysIcons();

       //animate the time (easing in)
            #ifdef PBL_ROUND
              //take the day out
              static PropertyAnimation* weekday_animation;
              weekday_animation = property_animation_create_layer_frame((Layer*)Weekday_Layer, &GRect(-1000,-1000,1,1),&WEEKDAY_FRAME);
              animation_schedule((Animation*) weekday_animation);
            
              //take the date out
              static PropertyAnimation* date_animation;
              date_animation = property_animation_create_layer_frame((Layer*)date_layer, &GRect(-1000,-1000,1,1),&DATE_FRAME);
              animation_schedule((Animation*) date_animation);
              
              //scroll up the time
              static PropertyAnimation* time_animation;
	/*
              if ((blnseconds) || (!clock_is_24h_style())){
                  time_animation = property_animation_create_layer_frame((Layer*)Time_Layer, &TIME_FRAME_ANIMATED, &TIME_FRAME2);
                  text_layer_set_text_alignment(Time_Layer, GTextAlignmentRight);
              }
              else{
			  */
                  time_animation = property_animation_create_layer_frame((Layer*)Time_Layer, &TIME_FRAME_ANIMATED, &TIME_FRAME);
            //  }
            animation_schedule((Animation*) time_animation);
          
              //scroll up the bluetooth indicator
              static PropertyAnimation* bt_animation;
              bt_animation = property_animation_create_layer_frame((Layer*)line, &GRect(20, 81, 140, 2),&GRect(20, 109, 140, 2));
              animation_schedule((Animation*) bt_animation);
          /*
              //Remove the seconds and AM/PM indicator
              if (blnseconds){
                  //seconds
                  static PropertyAnimation* seconds_animation;
                  seconds_animation = property_animation_create_layer_frame((Layer*)seconds_layer, &GRect(-1000,-1000,1,1), &SECONDS_FRAME_CHALK);
                  animation_schedule((Animation*) seconds_animation);
              }
              if(!clock_is_24h_style()){
                  //AM/PM indicator
                  static PropertyAnimation* ampm_animation;
                  ampm_animation = property_animation_create_layer_frame((Layer*)ampm_layer, &GRect(-1000,-1000,1,1), &AMPM_FRAME_CHALK);
                  animation_schedule((Animation*) ampm_animation);
                
              }
		*/
			#endif
			//If the backlight is on, turn it off and cancel the timer
			if(blnBacklight){app_timer_cancel(BackLightTimer);}
			//Load the temperature layer
			LoadTemperature();


}

void accel_tap_handler(AccelAxisType axis, int32_t direction){

	//Check if the Forecast is enabled 
	if (ESDuration_ms>0){
	//Just fire the event while displaying the primary screen
		if (blnForecast==false){
			TapCount = TapCount + 1;
			if (TapCount > 1){
				//turn the backlight on (every second until forecast screen closes)
				if(blnBacklight){BackLightTimer = app_timer_register(1000, ExtendBackLight, NULL);}
				//load extended screen
				LoadForecast();
			}
		}
	}
}