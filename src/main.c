//Declare and Import references
#include "pebble.h"
#include "pebble_fonts.h"
#include "language.h"
#include "variables.h"
#include "bitmaps.h"
#include "textlayers.h"
#include "frames.h"

#include "functions.h"


 
//UIDs:
	//English: 35a28a4d-0c9f-408f-9c6d-551e65f03186
	//Spanish: 3ab59c04-142f-4ff1-b90d-aab93ce54a32
	//Italian: 6279f406-1114-4b2f-852d-65b0e8ff2a73


//Declare initial window        
        Window *my_window;


//**************************//
// Check the Battery Status //
//**************************//

static void handle_battery(BatteryChargeState charge_state) {
     //static char battery_text[] = "100%";
	
	//kill previous batt_image to avoid invalid ones.
	if (Batt_image !=NULL) {gbitmap_destroy(Batt_image);}
    bitmap_layer_set_bitmap(Batt_icon_layer, NULL);

  if (charge_state.is_charging) {
    //snprintf(battery_text, sizeof(battery_text), "charging");
	  		//Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_CHAR);
	  		Batt_image = gbitmap_create_with_resource(BATTERY_ICON[0]);
            bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
  } else {
	  //snprintf(battery_text, sizeof(battery_text), "%d%%", charge_state.charge_percent);

	  
	  //WHILE RUNNING LOW, BATT STATUS WILL ALWAYS DISPLAY  
         //set the new batt_image
         //DO NOT display the batt_icon all the time. it is annoying.
         if (charge_state.charge_percent <=10) //If the charge is between 0% and 10%
         {
			 //Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_EMPTY);
			 Batt_image = gbitmap_create_with_resource(BATTERY_ICON[1]);
             bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
         }
	  //CHECK IF BATTERY STATUS SHOULD DISPLAY ALL THE TIME OR JUST WHILE RUNNING LOW
	  else if (batt_status){
		  
		  Batt_image = gbitmap_create_with_resource(BATTERY_ICON[charge_state.charge_percent/10]);
          bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
		  
	  }

  }
  //text_layer_set_text(Batt_Layer, battery_text);
}


	
/**************************/
// Vibes on disconnection //
/**************************/
static void vibes()
{


	//Vibes on connection
    if (BTConnected == false){
		if (bluetooth_connection_service_peek() == true){
			//Vibes to alert connection
			if (blnvibes==true){vibes_short_pulse();}
			BTConnected = true;
		}
	}
                
	//Vibes on disconnect
    if (BTConnected == true){
    	//Vibes to alert disconnection
		if (bluetooth_connection_service_peek()== false){
			if(blnvibes==true){vibes_long_pulse();}
       		BTConnected = false;
	    }
    }

}	


//******************************//
// Handle Bluetooth Connection //
//*****************************//
static void handle_bluetooth(bool connected)
{
          //text_layer_set_text(BT_Layer, connected ? "C" : "D");
        
        //draw the BT icon if connected        
        if(connected ==true)
        {
			if (BT_image !=NULL) {gbitmap_destroy(BT_image);}
			BT_image = gbitmap_create_with_resource(RESOURCE_ID_BT_CONNECTED);
            bitmap_layer_set_bitmap(BT_icon_layer, BT_image);
			if (BTConnected == false){
			//setup the timer to catch false disconnections (5 secs)
         	timer = app_timer_register(5000, vibes, NULL);
			}

        }
        else
        {
            //Kill the previous image
		    //if (BT_image!=NULL) {gbitmap_destroy(BT_image);}
            bitmap_layer_set_bitmap(BT_icon_layer, NULL);
			if (BTConnected == true){
			//setup the timer to catch false disconnections (5 secs)
         	timer = app_timer_register(5000, vibes, NULL);
		}
			
      
        }
	

        
} //handle_bluetooth

/////////////////	
//Invert colors//
/////////////////
void InvertColors(bool inverted)
{
	
	if (inverted){
		//Inverter layer
		if (blninverted == false){		
			inv_layer = inverter_layer_create(GRect(0, 0, 144, 168));
			layer_add_child(window_get_root_layer(my_window), (Layer*) inv_layer);
			blninverted =  true;
	    }
	}
	
	else{
		if(blninverted){
			inverter_layer_destroy(inv_layer);
			blninverted = false;}
	}
	
}// END - Invert colors



//**************************//
//** Get the current date **//
//**************************//
void getDate()
{

	//Get the date
	time_t actualPtr = time(NULL);
	struct tm *tz1Ptr = gmtime(&actualPtr);

	//get day, month and year for moon phase
	intday = tz1Ptr->tm_mday;
	intmonth = tz1Ptr->tm_mon;
	intyear = tz1Ptr->tm_year;
	

	//fix the development issue (set to english non-us)
	if (language>100){language = 97;}
	//Check that the selected language exists in the installed watchface version
	//(EXCLIDING CHINESE, JAPANESE AND ENGLISH!!) -- SET TO ENGLISH U.S.
	if((language>intLangCounter)&&(language<97)){language=100;}
	



	//Try new translation method

		//Get the number of the weekday
		strftime(weekday_text,sizeof(weekday_text),"%u",tz1Ptr);
		int ia = weekday_text[0] - '0'; 
		int ib = (language*7)+ia;
	
		//Get the 3 days forecast days
		int fcA = ia+1;
		if (fcA>7){fcA=fcA-7;}
		//if english, chinese or japanese, don't check the language key (they use their own array)
		if (language<97){fcA = (language*7)+fcA;}		
	
		int fcB = ia+2;
		if (fcB>7){fcB=fcB-7;}
		//if english, chinese or japanese, don't check the language key (they use their own array)
		if (language<97){fcB = (language*7)+fcB;}		
			
		int fcC = ia+3;
		if (fcC>7){fcC=fcC-7;}
		//if english, chinese or japanese, don't check the language key (they use their own array)
		if (language<97){fcC = (language*7)+fcC;}	
	
		//Get the number of the month	
		strftime(month_text,sizeof(month_text),"%m",tz1Ptr);
		int ic = month_text[1] - '0';
		if (month_text[0]=='1'){ic=ic+10;}			
		int id = (language*12)+ic;

	if((language==100)||(language==97)){ //ENGLISH

		//remove the chinese week day
		if (chinese_day) {gbitmap_destroy(chinese_day);}
		bitmap_layer_set_bitmap(chinese_day_layer, NULL);

		//Get the English fortmat
		if (language==100){strftime(month_text,sizeof(month_text),"%B %e",tz1Ptr);} //English US
		else {strftime(month_text,sizeof(month_text),"%e %B",tz1Ptr);} // English Non-US
		
		strftime(weekday_text,sizeof(weekday_text),"%A",tz1Ptr);

		text_layer_set_text(Weekday_Layer,weekday_text); //Update the weekday layer  
		text_layer_set_text(date_layer,month_text); 
		
		//Get the 3 days forecast
		memcpy(&weekday1_text, ENGLISH_DAYS[fcA], strlen(ENGLISH_DAYS[fcA])+1);
		memcpy(&weekday2_text, ENGLISH_DAYS[fcB], strlen(ENGLISH_DAYS[fcB])+1);
		memcpy(&weekday3_text, ENGLISH_DAYS[fcC], strlen(ENGLISH_DAYS[fcC])+1);

	}

	else if (language==99){//CHINESE

		//Work on retrieving the correct weekday
		//Get the Month
		strftime(month_text,sizeof(month_text),"%m/%d",tz1Ptr);

		//Clean un the text layer
		text_layer_set_text(Weekday_Layer,"");

		if (chinese_day!= NULL) {gbitmap_destroy(chinese_day);}
		chinese_day = gbitmap_create_with_resource(CHINESE_DAYS[ia-1]);
		//Display the weekday in chinese
		bitmap_layer_set_bitmap(chinese_day_layer, chinese_day);
		text_layer_set_text(date_layer, month_text);
		
		//Get the 3 days forecast (in english for now)
		memcpy(&weekday1_text, ENGLISH_DAYS[fcA], strlen(ENGLISH_DAYS[fcA])+1);
		memcpy(&weekday2_text, ENGLISH_DAYS[fcB], strlen(ENGLISH_DAYS[fcB])+1);
		memcpy(&weekday3_text, ENGLISH_DAYS[fcC], strlen(ENGLISH_DAYS[fcC])+1);
		

	}
	else if (language==98){//JAPANESE (use the same layer and bitmap than japanese)

		//Work on retrieving the correct weekday
		//Get the Month
		strftime(month_text,sizeof(month_text),"%m/%d",tz1Ptr);

		//Clean un the text layer
		text_layer_set_text(Weekday_Layer,"");

		if (chinese_day!= NULL) {gbitmap_destroy(chinese_day);}
		chinese_day = gbitmap_create_with_resource(JAPANESE_DAYS[ia-1]);
		//Display the weekday in chinese
		bitmap_layer_set_bitmap(chinese_day_layer, chinese_day);
		text_layer_set_text(date_layer, month_text);
		
		//Get the 3 days forecast (in english for now)
		memcpy(&weekday1_text, ENGLISH_DAYS[fcA], strlen(ENGLISH_DAYS[fcA])+1);
		memcpy(&weekday2_text, ENGLISH_DAYS[fcB], strlen(ENGLISH_DAYS[fcB])+1);
		memcpy(&weekday3_text, ENGLISH_DAYS[fcC], strlen(ENGLISH_DAYS[fcC])+1);
//		if (chinese_day1!= NULL) {gbitmap_destroy(chinese_day1);}
//		if (chinese_day2!= NULL) {gbitmap_destroy(chinese_day2);}
//		if (chinese_day3!= NULL) {gbitmap_destroy(chinese_day3);}
		
//		chinese_day1 = gbitmap_create_with_resource(JAPANESE_DAYS[fcA-1]);
//		chinese_day2 = gbitmap_create_with_resource(JAPANESE_DAYS[fcB-1]);
//		chinese_day3 = gbitmap_create_with_resource(JAPANESE_DAYS[fcC-1]);

	}

	else{
		//remove the chinese week day
		if (chinese_day !=NULL) {gbitmap_destroy(chinese_day);}
		bitmap_layer_set_bitmap(chinese_day_layer, NULL);

		//Set the weekeday
		text_layer_set_text(Weekday_Layer, WEEKDAYS[ib]); //Update the weekday layer  


		//Get the day
		strftime(day_month,sizeof(day_month),"%e",tz1Ptr);

		//Set the month
		//text_layer_set_text(date_layer, MONTHS[id]);
				 if ((language == 12)||(language == 3)){
					memcpy(&month_text, MONTHS[id], strlen(MONTHS[id])+1);
					text_layer_set_text(date_layer,strncat(month_text,day_month,strlen(month_text)));} //Czech or Hungarian
				else{text_layer_set_text(date_layer,strncat(day_month,MONTHS[id],strlen(MONTHS[id]))); }
		
		//Get the 3 days forecast
		memcpy(&weekday1_text, WEEKDAYS[fcA], strlen(WEEKDAYS[fcA])+1);
		memcpy(&weekday2_text, WEEKDAYS[fcB], strlen(WEEKDAYS[fcB])+1);
		memcpy(&weekday3_text, WEEKDAYS[fcC], strlen(WEEKDAYS[fcC])+1);

	}

}

//YWeather 2.3 - REQ01. Display Seconds - START
void getTime()
	{
	
	time_t actualPtr = time(NULL);
	struct tm *tz1Ptr = gmtime(&actualPtr);
	
	if (clock_is_24h_style()){strftime(time_text, sizeof(time_text), "%H:%M", tz1Ptr);}
	else {strftime(time_text, sizeof(time_text), "%I:%M", tz1Ptr);}	
	
	//Remove the leading 0s
	if (time_text[0]=='0') {memcpy(&time_text," ",1);}
	
	//clock_copy_time_string(time_text, sizeof(time_text));
	
		
		//Set the time to the Time Layer
        text_layer_set_text(Time_Layer, time_text);
                
        //Check Battery Status
        handle_battery(battery_state_service_peek());
                
        //Check BT Status
        handle_bluetooth(bluetooth_connection_service_peek());
	
}
//YWeather 2.3 - REQ01. Display Seconds - END


//************************//
// Capture the Tick event //
//************************//
void handle_tick(struct tm *tick_time, TimeUnits units_changed)
{
	//YWeather 2.3 - REQ01. Display Seconds - START
			//Set the AM/PM indicator
			//if(clock_is_24h_style()){memcpy(&ampm_text,  "24H", strlen("24H"));}
			//else {strftime(ampm_text, sizeof(ampm_text), "%p", tick_time);}
			if(!clock_is_24h_style()){strftime(ampm_text, sizeof(ampm_text), "%p", tick_time);}
			text_layer_set_text(ampm_layer, ampm_text); //Update the weekday layer  
	//YWeather 2.3 - REQ01. Display Seconds - END
     
	    if (units_changed & SECOND_UNIT)
		{
			//YWeather 2.3 - REQ01. Display Seconds - START
			//refresh the tap counter every second
			//TapCount = 0;
			//Set the seconds
			strftime(seconds_text, sizeof(seconds_text), "%S", tick_time);
			if (blnseconds){text_layer_set_text(seconds_layer, seconds_text);}
			else {text_layer_set_text(seconds_layer, "");}
			//YWeather 2.3 - REQ01. Display Seconds - END
			
		}
       if (units_changed & MINUTE_UNIT)
       {
//YWeather 2.3 - REQ01. Display Seconds - START
			getTime();
		   
		   //clean up the seconds if disables
		   if (! blnseconds){text_layer_set_text(seconds_layer, "");}
//YWeather 2.3 - REQ01. Display Seconds - END
	//YWeather 2.3 - REQ02. Hourly Vibe - START
		   //Vibes on O'Clock
		  // if (blnhourly_vibe){
		   		//if ((tick_time->tm_min == 0)&&(tick_time->tm_sec == 0)) {vibes_double_pulse();}
		   //}
	} //MINUTE CHANGES
		if (units_changed & HOUR_UNIT){
			//Vibes on O'Clock
			if (blnhourly_vibe){
				if(!DoNotDisturb(tick_time->tm_hour, tick_time->tm_min,HOURLY_VIBE_START_KEY,HOURLY_VIBE_END_KEY)){vibes_double_pulse();}
				//vibes_double_pulse();
				}
		} //HOUR CHANGES
		   

	//YWeather 2.3 - REQ02. Hourly Vibe - END
	     if (units_changed & DAY_UNIT){
			 	//Update the date
			 	getDate();}

	
} //HANDLE_TICK


void SubscribeTickEvent(){
		time_t now = time(NULL);
		struct tm *current_time = localtime(&now);
	
		if (blnseconds) {
			handle_tick(current_time, SECOND_UNIT);
			tick_timer_service_subscribe(SECOND_UNIT, &handle_tick);
		}
		else {
			handle_tick(current_time, MINUTE_UNIT);
			tick_timer_service_subscribe(MINUTE_UNIT, &handle_tick);
			
		}
}

//*****************//
// AppSync options //
//*****************//

        static AppSync sync;
        static uint8_t sync_buffer[512];

  static void sync_tuple_changed_callback(const uint32_t key,
                                        const Tuple* new_tuple,
                                        const Tuple* old_tuple,
                                        void* context) {

        
  // App Sync keeps new_tuple in sync_buffer, so we may use it directly
  switch (key) {
    case WEATHER_ICON_KEY:
	    if (weather_image != NULL){gbitmap_destroy(weather_image);}

	  		weather_image = gbitmap_create_with_resource(WEATHER_ICONS[new_tuple->value->uint8]);
			//If the app is in the Main Screen, refresh the weather icon
			if (blnForecast == false) {bitmap_layer_set_bitmap(weather_icon_layer, weather_image);}
	  		//ICON_CODE = new_tuple->value->uint8;
	  	  	persist_write_int(WEATHER_ICON_KEY, new_tuple->value->uint8);
      		break;

    case WEATHER_TEMPERATURE_KEY:
         //Update the temperature
	        //Set the time on which weather was retrived
			//clock_copy_time_string(last_update, sizeof(last_update));
	  		memcpy(&last_update,  time_text, strlen(time_text));
	  		//If the app is in the Main Screen, refresh Last Update
			if (blnForecast == false) {text_layer_set_text(Last_Update, last_update);}
	  		
	  		//Save the temperature
	    	persist_write_string(WEATHER_TEMPERATURE_KEY, new_tuple->value->cstring);
	  	  	//If the app is in the Main Screen, refresh Temperature
			if (blnForecast == false) {text_layer_set_text(Temperature_Layer, new_tuple->value->cstring);}	        
      		break;

     case WEATHER_CITY_KEY:
	  		persist_write_string(WEATHER_CITY_KEY, new_tuple->value->cstring);
	  	  	//If the app is in the Main Screen, refresh City
			if (blnForecast == false) {text_layer_set_text(Location_Layer, new_tuple->value->cstring);}        	
         	break;

	 case INVERT_COLOR_KEY:
		  color_inverted = new_tuple->value->uint8 != 0;
		  persist_write_bool(INVERT_COLOR_KEY, color_inverted);

	  	  //refresh the layout
	  	  InvertColors(color_inverted);
		  break;
	  
	  case language_key:
	  	  language = new_tuple->value->uint8;
	  	  persist_write_int(language_key, language);
	  		//Init the date
			getDate();
		  break;
	  
	  case VIBES_KEY:
		  blnvibes = new_tuple->value->uint8 != 0;
		  persist_write_bool(VIBES_KEY, blnvibes);
		  break;
  
	  //Forecast for the day
		case WEATHER_HIGH_KEY: 
	  		//Save the High temperature
	        //memcpy(&high,  new_tuple->value->cstring, strlen( new_tuple->value->cstring));
	    	persist_write_string(WEATHER_HIGH_KEY, new_tuple->value->cstring);
      		break;
		case WEATHER_LOW_KEY:
	  	  	//Save the Low temperature
	  		//memcpy(&low,  new_tuple->value->cstring, strlen( new_tuple->value->cstring));
	    	persist_write_string(WEATHER_LOW_KEY, new_tuple->value->cstring);
      		break;
		case SUNRISE_KEY:
	  	  	//Save the Sunrise Time
	  	  	//memcpy(&sunrise,  new_tuple->value->cstring, strlen(sunrise));
	    	persist_write_string(SUNRISE_KEY, new_tuple->value->cstring);
      		break;
		case SUNSET_KEY:
	  	  	//Save the Sunset Time
	  	  	//memcpy(&sunset,  new_tuple->value->cstring, strlen(sunset));
	    	persist_write_string(SUNSET_KEY, new_tuple->value->cstring);
      		break;
		case WIND_KEY:
	  	  	 //Save the Wind Speed
	  	  	//memcpy(&wind,  new_tuple->value->cstring, strlen(wind));
	    	persist_write_string(WIND_KEY, new_tuple->value->cstring);
      		break;
	  
	  	case WDIRECTION_KEY:
	  	  	//Save the Wind Direction
	  	  	//wdirection = new_tuple->value->uint32;
	  	  	//persist_write_int(WDIRECTION_KEY, wdirection);
	  		persist_write_string(WDIRECTION_KEY, new_tuple->value->cstring);
      		break;
	  
	  	case FORECAST_CODE1_KEY:
	  		//Saves de weather condition
	  	    //if (forecast1 != NULL){gbitmap_destroy(forecast1);}
	  		//if (image != NULL){gbitmap_destroy(image);}

	  		//image = gbitmap_create_with_resource(WEATHER_ICONS[new_tuple->value->uint8]);
	  		//resized_data = malloc((image->bounds.size.h * image->row_size_bytes) * sizeof(uint8_t));
	  		//forecast1 = scaleBitmap(image, 37, 37, resized_data);
	  		persist_write_int(FORECAST_CODE1_KEY, new_tuple->value->uint8);
      		break;
	  
	  	case FORECAST_HIGH1_KEY:
	  		//Saves the high for the day
	  		//memcpy(&day1H,  new_tuple->value->cstring, strlen( new_tuple->value->cstring));
	  	 	persist_write_string(FORECAST_HIGH1_KEY, new_tuple->value->cstring);
      		break;
	  
	  	case FORECAST_LOW1_KEY:
	  		//Saves the low for the day
	  		//memcpy(&day1L,  new_tuple->value->cstring, strlen( new_tuple->value->cstring));
	  	    persist_write_string(FORECAST_LOW1_KEY, new_tuple->value->cstring);
      		break;	 
	  
	  	case FORECAST_CODE2_KEY:
	  		//Saves de weather condition
	  		persist_write_int(FORECAST_CODE2_KEY, new_tuple->value->uint8);
      		break;
	  
	  	case FORECAST_HIGH2_KEY:
	  		//Saves the high for the day
	  	  	//memcpy(&day2H,  new_tuple->value->cstring, strlen( new_tuple->value->cstring));
	  	    persist_write_string(FORECAST_HIGH2_KEY, new_tuple->value->cstring);
      		break;
	  
	  	case FORECAST_LOW2_KEY:
	  		//Saves the low for the day
	  	  	//memcpy(&day2L,  new_tuple->value->cstring, strlen( new_tuple->value->cstring));
	  	    persist_write_string(FORECAST_LOW2_KEY, new_tuple->value->cstring);
      		break;
	  
	  	case FORECAST_CODE3_KEY:
	  		//Saves the weather condition
	  		persist_write_int(FORECAST_CODE3_KEY, new_tuple->value->uint8);
      		break;
	  
	  	case FORECAST_HIGH3_KEY:
	  		//Saves the high for the day
	  	  	//memcpy(&day3H,  new_tuple->value->cstring, strlen( new_tuple->value->cstring));
	  	    persist_write_string(FORECAST_HIGH3_KEY, new_tuple->value->cstring);
      		break;
	  
	  	case FORECAST_LOW3_KEY:
	  		//Saves the low for the day
	  		//memcpy(&day3L,  new_tuple->value->cstring, strlen( new_tuple->value->cstring));
	  	    persist_write_string(FORECAST_LOW3_KEY, new_tuple->value->cstring);
      		break;
	  
	  	case EXTRA_ESDURATION_KEY:
	  		//Saves the Extended Screen duration
	 		ESDuration_ms = new_tuple->value->uint8*1000;
	  		persist_write_int(EXTRA_ESDURATION_KEY, ESDuration_ms);
      		break;
	  
	  	case EXTRA_TIMER_KEY:
	  		//Saves the weather update frequency
	  		timeout_ms = new_tuple->value->uint8 * 60000;
	  		persist_write_int(EXTRA_TIMER_KEY,timeout_ms);
      		break;
	  
	  	case EXTRA_FORECAST_KEY:
	  		//Saves the 3 days forecast toggle
	  		bln3daysForecast =  new_tuple->value->uint8 != 0;
	  		persist_write_int(EXTRA_FORECAST_KEY, new_tuple->value->uint8);
      		break;
	  	//YWeather 2.3 - REQ01. Display Seconds - START
	  	  	case DISPLAY_SECONDS_KEY:
	  		//Saves the display seconds toggle (only when the new value differs from the saved one)
	  		if (blnseconds !=  new_tuple->value->uint8){
				//APP_LOG(APP_LOG_LEVEL_INFO, "blnsecond cambia");
				blnseconds =  new_tuple->value->uint8 != 0;
				persist_write_int(DISPLAY_SECONDS_KEY, new_tuple->value->uint8);

			//YWeather 2.4 - Enhance Display Seconds - START
				//subscribes to the new tick even
				tick_timer_service_unsubscribe();
				SubscribeTickEvent();
			}
		//YWeather 2.4 - Enhance Display Seconds - END

      		break;
	  	//YWeather 2.3 - REQ01. Display Seconds - END
	  	//YWeather 2.3 - REQ02. Hourly Vibe - START
	  	  	case HOURLY_VIBE_KEY:
	  		//Saves the hourly vibe toggle
	  		blnhourly_vibe =  new_tuple->value->uint8 != 0;
	  		persist_write_int(HOURLY_VIBE_KEY, new_tuple->value->uint8); 
      		break;
	  	//YWeather 2.3 - REQ02. Hourly Vibe - END
	  	  	
	  		case HOURLY_VIBE_START_KEY:
	  		persist_write_int(HOURLY_VIBE_START_KEY, new_tuple->value->uint8);
	  		break;
	  
	  	  	case HOURLY_VIBE_END_KEY:
	  		persist_write_int(HOURLY_VIBE_END_KEY, new_tuple->value->uint8);
	  		break;
	  
	  	 	case HIDE_BAT_KEY:
		  	batt_status = new_tuple->value->uint8 != 0;
		  	persist_write_int(HIDE_BAT_KEY, batt_status);

		  	break;
	  
	  	  case FONT_KEY:
	  	  intUI = new_tuple->value->uint8;
	  	  persist_write_int(FONT_KEY, intUI);
		  break;

  }
	  
}



//************************************************//
// TIMER to refresh the weather data every 30 min //
//************************************************//
static void send_cmd(void) {

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

static void timer_callback(void *context) {

		//Developer vibe: confirm that timer is not killed
		//vibes_double_pulse();
	
        timer = app_timer_register(timeout_ms, timer_callback, NULL);

        //Refresh the weather
        send_cmd();
	       

}

/*********************************/
/* Load  the main weather screen */
/*********************************/
void LoadTemperature()
{	
	//remove the inverted layer (if any) before creating the new text layers
	if(blninverted){inverter_layer_destroy(inv_layer);	blninverted = false;}
	//Track that we are displaying the primary screen
	blnForecast = false;
	
	//Display the Weather layer
	weather_icon_layer = bitmap_layer_create(WEATHER_FRAME);
	bitmap_layer_set_bitmap(weather_icon_layer, weather_image);
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(weather_icon_layer));
	
	//Create the Temperature Layer
	Temperature_Layer = text_layer_create(TEMPERATURE_FRAME);
	text_layer_set_text_color(Temperature_Layer, GColorWhite);
	text_layer_set_background_color(Temperature_Layer, GColorClear);	
	text_layer_set_font(Temperature_Layer, font_temperature);
	text_layer_set_text_alignment(Temperature_Layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Temperature_Layer));
	
	//Display the Location layer
	Location_Layer = text_layer_create(LOCATION_FRAME);
	text_layer_set_text_color(Location_Layer, GColorWhite);	
	text_layer_set_background_color(Location_Layer, GColorClear);
	text_layer_set_font(Location_Layer, font_update);
	text_layer_set_text_alignment(Location_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Location_Layer));
	
	//Display the Last Update layer
	Last_Update = text_layer_create(LAST_UPDATE_FRAME);
	text_layer_set_text_color(Last_Update, GColorWhite);
	text_layer_set_background_color(Last_Update, GColorClear);	
	text_layer_set_font(Last_Update, font_update);
	text_layer_set_text_alignment(Last_Update, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Last_Update));
	
	//set back the location
	//memset(&city[0], 0, sizeof(city));
	persist_read_string(WEATHER_CITY_KEY, city, sizeof(city));
	text_layer_set_text(Location_Layer, city);
	
	//set back the temperature
	persist_read_string(WEATHER_TEMPERATURE_KEY, temp, sizeof(temp));
	text_layer_set_text(Temperature_Layer, temp);
	
	//set back the last update
	text_layer_set_text(Last_Update, last_update);
	
	//if color inverted, then create the inverted layer
	InvertColors(color_inverted);
	
} //LoadTemperature - END

//UNLOAD LAYERS //

void UnloadForecast()
{
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
	if(moon_icon_layer){bitmap_layer_destroy(moon_icon_layer);}
	
}

void UnloadTemperature(){
	//Destroy the temperature Layer
	if(Temperature_Layer){text_layer_destroy(Temperature_Layer);}
	if(weather_icon_layer){bitmap_layer_destroy(weather_icon_layer);}
	if(Location_Layer){text_layer_destroy(Location_Layer);}
	if(Last_Update){text_layer_destroy(Last_Update);}

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
}

//TIMER CALLBACK

static void forecast3Days_callback(void *context) {
       
        //Refresh the weather
		Unload3Days();
        LoadTemperature();
    

}

void Load3Days()
{

	//remove the inverted layer (if any) before creating the new text layers
	if(blninverted){inverter_layer_destroy(inv_layer);	blninverted = false;}
//DAY 1
	//Weekday
		Day1_Layer = text_layer_create(FORECAST_DAY1_FRAME);	
		text_layer_set_text_color(Day1_Layer, GColorWhite);
		text_layer_set_background_color(Day1_Layer, GColorClear);
		text_layer_set_font(Day1_Layer, font_date);
		text_layer_set_text_alignment(Day1_Layer, GTextAlignmentLeft);
		layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Day1_Layer));
	
		text_layer_set_text(Day1_Layer,weekday1_text);
	
	//Display the weather icon
	if (forecast1 != NULL){gbitmap_destroy(forecast1);}

	code1 = persist_read_int(FORECAST_CODE1_KEY);
	forecast1 = gbitmap_create_with_resource(WEATHER_ICONS_SMALL[code1]);
	

	forecast1_layer = bitmap_layer_create(FORECAST_CODE1_FRAME);
	bitmap_layer_set_bitmap(forecast1_layer, forecast1);
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(forecast1_layer));

	//High for the day
	High1_Layer = text_layer_create(FORECAST_HIGH1_FRAME);	
	text_layer_set_text_color(High1_Layer, GColorWhite);
	text_layer_set_background_color(High1_Layer, GColorClear);
	text_layer_set_font(High1_Layer, font_update);
	text_layer_set_text_alignment(High1_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(High1_Layer));
	
	persist_read_string(FORECAST_HIGH1_KEY, day1H, sizeof(day1H));
	text_layer_set_text(High1_Layer,day1H);
	
	
	//Low for the day
	Low1_Layer = text_layer_create(FORECAST_LOW1_FRAME);	
	text_layer_set_text_color(Low1_Layer, GColorWhite);
	text_layer_set_background_color(Low1_Layer, GColorClear);
	text_layer_set_font(Low1_Layer, font_update);
	text_layer_set_text_alignment(Low1_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Low1_Layer));
	
	persist_read_string(FORECAST_LOW1_KEY, day1L, sizeof(day1L));
	text_layer_set_text(Low1_Layer,day1L);
	
//DAY 2
	//Weekday
		Day2_Layer = text_layer_create(FORECAST_DAY2_FRAME);	
		text_layer_set_text_color(Day2_Layer, GColorWhite);
		text_layer_set_background_color(Day2_Layer, GColorClear);
		text_layer_set_font(Day2_Layer, font_date);
		text_layer_set_text_alignment(Day2_Layer, GTextAlignmentLeft);
		layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Day2_Layer));

		text_layer_set_text(Day2_Layer,weekday2_text);
	//Display the weather icon
	if (forecast2 != NULL){gbitmap_destroy(forecast2);}
	code2 = persist_read_int(FORECAST_CODE2_KEY);
	forecast2 = gbitmap_create_with_resource(WEATHER_ICONS_SMALL[code2]);
	forecast2_layer = bitmap_layer_create(FORECAST_CODE2_FRAME);
	bitmap_layer_set_bitmap(forecast2_layer, forecast2);
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(forecast2_layer));
	
	//High for the day
	High2_Layer = text_layer_create(FORECAST_HIGH2_FRAME);	
	text_layer_set_text_color(High2_Layer, GColorWhite);
	text_layer_set_background_color(High2_Layer, GColorClear);
	text_layer_set_font(High2_Layer, font_update);
	text_layer_set_text_alignment(High2_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(High2_Layer));
	persist_read_string(FORECAST_HIGH2_KEY, day2H, sizeof(day2H));
	text_layer_set_text(High2_Layer,day2H);
	//Low for the day
	Low2_Layer = text_layer_create(FORECAST_LOW2_FRAME);	
	text_layer_set_text_color(Low2_Layer, GColorWhite);
	text_layer_set_background_color(Low2_Layer, GColorClear);
	text_layer_set_font(Low2_Layer, font_update);
	text_layer_set_text_alignment(Low2_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Low2_Layer));
	persist_read_string(FORECAST_LOW2_KEY, day2L, sizeof(day2L));
	text_layer_set_text(Low2_Layer,day2L);
	
//DAY 3
	//Weekday
		Day3_Layer = text_layer_create(FORECAST_DAY3_FRAME);	
		text_layer_set_text_color(Day3_Layer, GColorWhite);
		text_layer_set_background_color(Day3_Layer, GColorClear);
		text_layer_set_font(Day3_Layer, font_date);
		text_layer_set_text_alignment(Day3_Layer, GTextAlignmentLeft);
		layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Day3_Layer));

		text_layer_set_text(Day3_Layer,weekday3_text);
	
	//Display the weather icon
	if (forecast3 != NULL){gbitmap_destroy(forecast3);}

	code3 = persist_read_int(FORECAST_CODE3_KEY);
	forecast3 = gbitmap_create_with_resource(WEATHER_ICONS_SMALL[code3]);
	
	
	forecast3_layer = bitmap_layer_create(FORECAST_CODE3_FRAME);
	bitmap_layer_set_bitmap(forecast3_layer, forecast3);
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(forecast3_layer));
	
	//High for the day
	High3_Layer = text_layer_create(FORECAST_HIGH3_FRAME);	
	text_layer_set_text_color(High3_Layer, GColorWhite);
	text_layer_set_background_color(High3_Layer, GColorClear);
	text_layer_set_font(High3_Layer, font_update);
	text_layer_set_text_alignment(High3_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(High3_Layer));
	
	persist_read_string(FORECAST_HIGH3_KEY, day3H, sizeof(day3H));
	text_layer_set_text(High3_Layer,day3H);
	
	//Low for the day
	Low3_Layer = text_layer_create(FORECAST_LOW3_FRAME);	
	text_layer_set_text_color(Low3_Layer, GColorWhite);
	text_layer_set_background_color(Low3_Layer, GColorClear);
	text_layer_set_font(Low3_Layer, font_update);
	text_layer_set_text_alignment(Low3_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Low3_Layer));
	
	persist_read_string(FORECAST_LOW3_KEY, day3L, sizeof(day3L));
	text_layer_set_text(Low3_Layer,day3L);
	
	//if color inverted, then create the inverted layer
	InvertColors(color_inverted);
	//setup the timer to set back the temperature after 5sec
	weather = app_timer_register(ESDuration_ms, forecast3Days_callback, NULL);
	
} //Load3Days - END

static void forecast_callback(void *context) {
       
        //Refresh the weather
		UnloadForecast();
		if (bln3daysForecast){
			//LoadTemperature();
			Load3Days();
		}
		else{
			LoadTemperature();
		}
    

}




/****************************************/
/* Display the secondary weather screen */
/****************************************/

void LoadForecast()
{
	//remove the inverted layer (if any) before creating the new text layers
	if(blninverted){inverter_layer_destroy(inv_layer);	blninverted = false;}
	//Track that we are displaying the secondary screen
	blnForecast = true;

	//Unload the temperature layers
	UnloadTemperature();
	
	//Create the Forecast Layers

	//HIGH
	High_Layer = text_layer_create(HIGH_FRAME);	
	text_layer_set_text_color(High_Layer, GColorWhite);
	text_layer_set_background_color(High_Layer, GColorClear);
	text_layer_set_font(High_Layer, font_date);
	text_layer_set_text_alignment(High_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(High_Layer));
	
	persist_read_string(WEATHER_HIGH_KEY, high, sizeof(high));
	text_layer_set_text(High_Layer,high);
	
	//Display the High icon
	if (high_image){gbitmap_destroy(high_image);}
	high_image = gbitmap_create_with_resource(RESOURCE_ID_HIGH);
	high_icon_layer = bitmap_layer_create(HIGH_ICON_FRAME);
	bitmap_layer_set_bitmap(high_icon_layer, high_image);
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(high_icon_layer));
	
	//LOW
	Low_Layer = text_layer_create(LOW_FRAME);	
	text_layer_set_text_color(Low_Layer, GColorWhite);
	text_layer_set_background_color(Low_Layer, GColorClear);
	text_layer_set_font(Low_Layer, font_date);
	text_layer_set_text_alignment(Low_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Low_Layer));
	
	persist_read_string(WEATHER_LOW_KEY, low, sizeof(low));
	text_layer_set_text(Low_Layer,low);
	
	//Display the Low icon
	if (low_image){gbitmap_destroy(low_image);}
	low_image = gbitmap_create_with_resource(RESOURCE_ID_LOW);
	low_icon_layer = bitmap_layer_create(LOW_ICON_FRAME);
	bitmap_layer_set_bitmap(low_icon_layer, low_image);
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(low_icon_layer));
	
	//SUNRISE
	Sunrise_Layer = text_layer_create(SUNRISE_FRAME);	
	text_layer_set_text_color(Sunrise_Layer, GColorWhite);
	text_layer_set_background_color(Sunrise_Layer, GColorClear);
	text_layer_set_font(Sunrise_Layer, font_date);
	text_layer_set_text_alignment(Sunrise_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Sunrise_Layer));
	
	persist_read_string(SUNRISE_KEY, sunrise, sizeof(sunrise));
	text_layer_set_text(Sunrise_Layer,formatSunrise(sunrise));
	
	//Display the sunset icon
	if (sunrise_image){gbitmap_destroy(sunrise_image);}
	sunrise_image = gbitmap_create_with_resource(RESOURCE_ID_SUNRISE);
	sunrise_icon_layer = bitmap_layer_create(SUNRISE_ICON_FRAME);
	bitmap_layer_set_bitmap(sunrise_icon_layer, sunrise_image);
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(sunrise_icon_layer));
	
	//SUNSET
	Sunset_Layer = text_layer_create(SUNSET_FRAME);	
	text_layer_set_text_color(Sunset_Layer, GColorWhite);
	text_layer_set_background_color(Sunset_Layer, GColorClear);
	text_layer_set_font(Sunset_Layer, font_date);
	text_layer_set_text_alignment(Sunset_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Sunset_Layer));
	
	persist_read_string(SUNSET_KEY, sunset, sizeof(sunset));
	text_layer_set_text(Sunset_Layer,formatSunset(sunset));
	
	//Display the sunset icon
	if (sunset_image){gbitmap_destroy(sunset_image);}
	sunset_image = gbitmap_create_with_resource(RESOURCE_ID_SUNSET);
	sunset_icon_layer = bitmap_layer_create(SUNSET_ICON_FRAME);
	bitmap_layer_set_bitmap(sunset_icon_layer, sunset_image);
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(sunset_icon_layer));
	
	//WIND SPEED
	Wind_Layer = text_layer_create(WIND_FRAME);	
	text_layer_set_text_color(Wind_Layer, GColorWhite);
	text_layer_set_background_color(Wind_Layer, GColorClear);
	text_layer_set_font(Wind_Layer, font_date);
	text_layer_set_text_alignment(Wind_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Wind_Layer));
	
	persist_read_string(WIND_KEY, wind, sizeof(wind));
	text_layer_set_text(Wind_Layer,wind);
	
	//WIND DIRECTION
	WDirection_Layer = text_layer_create(WDIRECTION_FRAME);	
	text_layer_set_text_color(WDirection_Layer, GColorWhite);
	text_layer_set_background_color(WDirection_Layer, GColorClear);
	text_layer_set_font(WDirection_Layer, font_update);
	text_layer_set_text_alignment(WDirection_Layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(WDirection_Layer));
	
	//wdirection =  persist_read_int(WDIRECTION_KEY); 
	//decode the wind direction code to text
	//windDirection();
	persist_read_string(WDIRECTION_KEY, strwdirection, sizeof(strwdirection));
	text_layer_set_text(WDirection_Layer,strwdirection);
	
	//Display the wind icon
	if (wind_image){gbitmap_destroy(wind_image);}
	wind_image = gbitmap_create_with_resource(RESOURCE_ID_WIND_ICON);
	wind_icon_layer = bitmap_layer_create(WIND_ICON_FRAME);
	bitmap_layer_set_bitmap(wind_icon_layer, wind_image);
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(wind_icon_layer));
	
	//moonphase
	moonphase_number = moon_phase(intyear+1900,intmonth,intday);
	if (moon_image) {gbitmap_destroy(moon_image);}
	moon_image = gbitmap_create_with_resource(MOON_IMAGE_RESOURCE_IDS[moonphase_number]);
	moon_icon_layer = bitmap_layer_create(MOON_ICON_FRAME);
	bitmap_layer_set_bitmap(moon_icon_layer, moon_image);
    layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(moon_icon_layer));
	
	//if color inverted, then create the inverted layer
	InvertColors(color_inverted);
	
	//refresh the tap counter 
	TapCount = 0;
	
	//setup the timer to set back the temperature after 5sec
	weather = app_timer_register(ESDuration_ms, forecast_callback, NULL);

	
} //LoadForecast - END


//************************************//
//** Capture the accelerometer Taps **//
//************************************//


void accel_tap_handler(AccelAxisType axis, int32_t direction){

    //send_cmd();
	//Check if the Forecast is enabled 
	if (ESDuration_ms>0){
	//Just fire the event while displaying the primary screen
		if (blnForecast==false){
			TapCount = TapCount + 1;
			if (TapCount > 1){
				LoadForecast();
			}
		}
	}
}


//****************************//
// Initialize the application //
//****************************//

void LoadMainWindow(){
	        //LOAD THE LAYERS
                //Display the Weekday layer
                Weekday_Layer = text_layer_create(WEEKDAY_FRAME);
				text_layer_set_text_color(Weekday_Layer, GColorWhite);
	            text_layer_set_background_color(Weekday_Layer, GColorClear);
                text_layer_set_font(Weekday_Layer, font_date);
                text_layer_set_text_alignment(Weekday_Layer, GTextAlignmentLeft);
                layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Weekday_Layer));
	
				//Display the weekday in chinese
				chinese_day_layer = bitmap_layer_create(CHIN_WEEKDAY_FRAME);
				layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(chinese_day_layer));
				bitmap_layer_set_alignment(chinese_day_layer, GAlignLeft);	
       
                //Display the Batt layer
                Batt_icon_layer = bitmap_layer_create(BATT_FRAME);
                bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
                layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(Batt_icon_layer));
        
                //Display the BT layer
                BT_icon_layer = bitmap_layer_create(BT_FRAME);
                bitmap_layer_set_bitmap(BT_icon_layer, BT_image);
                layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(BT_icon_layer));
        
                //Display the Time layer
			//YWeather 2.3 - REQ01. Display Seconds - START
                //Time_Layer = text_layer_create(TIME_FRAME);
				Time_Layer = text_layer_create(TIME_FRAME2);	
			//YWeather 2.3 - REQ01. Display Seconds - END
				text_layer_set_text_color(Time_Layer, GColorWhite);
	            text_layer_set_background_color(Time_Layer, GColorClear);
                text_layer_set_font(Time_Layer, font_time);
		//YWeather 2.3 - REQ01. Display Seconds - START
                //text_layer_set_text_alignment(Time_Layer, GTextAlignmentCenter);
				text_layer_set_text_alignment(Time_Layer, GTextAlignmentRight);
		//YWeather 2.3 - REQ01. Display Seconds - END
                layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Time_Layer));
	
	
	//YWeather 2.3 - REQ01. Display Seconds - START
	            //Display the Second layer
                seconds_layer = text_layer_create(SECONDS_FRAME);
				text_layer_set_text_color(seconds_layer, GColorWhite);
	            text_layer_set_background_color(seconds_layer, GColorClear);
                text_layer_set_font(seconds_layer, font_date);
                text_layer_set_text_alignment(seconds_layer, GTextAlignmentLeft);
                layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(seconds_layer));
	
	            ampm_layer = text_layer_create(AMPM_FRAME);
				text_layer_set_text_color(ampm_layer, GColorWhite);
	            text_layer_set_background_color(ampm_layer, GColorClear);
                text_layer_set_font(ampm_layer, font_update);
                text_layer_set_text_alignment(ampm_layer, GTextAlignmentLeft);
                layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(ampm_layer));
	//YWeather 2.3 - REQ01. Display Seconds - END
        
                //Display the Date layer
                date_layer = text_layer_create(DATE_FRAME);	
				text_layer_set_text_color(date_layer, GColorWhite);
	            text_layer_set_background_color(date_layer, GColorClear);
                text_layer_set_font(date_layer, font_date);
                text_layer_set_text_alignment(date_layer, GTextAlignmentRight);
                layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(date_layer));
        
        
                //Display the Temperature layer
				LoadTemperature();     

        
 
	            //Drawn the normal/inverted based on saved settings
	            //InvertColors(color_inverted);
}//LoadMainWindow END

void SetupMessages(){


                app_message_open(inbound_size, outbound_size);
        
                Tuplet initial_values[] = {
                TupletInteger(WEATHER_ICON_KEY, ICON_CODE), //INITIALIZE TO "N/A"
				MyTupletCString(WEATHER_TEMPERATURE_KEY, temp),
				//MyTupletCString(WEATHER_TEMPERATURE_KEY,low), //Init to something
                MyTupletCString(WEATHER_CITY_KEY, "YWeather v2.5"), //display app version on load
				TupletInteger(INVERT_COLOR_KEY, color_inverted),
				TupletInteger(language_key, language), //INITIALIZE TO LAST SAVED
				TupletInteger(VIBES_KEY, blnvibes),
				MyTupletCString(WEATHER_HIGH_KEY,high),
				MyTupletCString(WEATHER_LOW_KEY,low),
				MyTupletCString(SUNRISE_KEY,sunrise),
				MyTupletCString(SUNSET_KEY,sunset),
				MyTupletCString(WIND_KEY,wind),
				//MyTupletCString(WIND_KEY,"0"), //Init to something
				//TupletInteger(WDIRECTION_KEY,wdirection),
				MyTupletCString(WDIRECTION_KEY,strwdirection),
				//3 days forecast
				TupletInteger(FORECAST_CODE1_KEY,0),
				MyTupletCString(FORECAST_HIGH1_KEY,day1H),
				MyTupletCString(FORECAST_LOW1_KEY,day1L),
				TupletInteger(FORECAST_CODE2_KEY,0),
				MyTupletCString(FORECAST_HIGH2_KEY,day2H),
				MyTupletCString(FORECAST_LOW2_KEY,day2L),
				TupletInteger(FORECAST_CODE3_KEY,0),
				MyTupletCString(FORECAST_HIGH3_KEY,day3H),
				MyTupletCString(FORECAST_LOW3_KEY,day3L),
				//Extra Features
				TupletInteger(EXTRA_ESDURATION_KEY,init_ESDuration_ms),
				TupletInteger(EXTRA_TIMER_KEY,init_timeout_ms),
				TupletInteger(EXTRA_FORECAST_KEY,bln3daysForecast),
			//YWeather 2.3 - REQ01. Display Seconds - START
				TupletInteger(DISPLAY_SECONDS_KEY,blnseconds),
			//YWeather 2.3 - REQ01. Display Seconds - END
			//YWeather 2.3 - REQ02. Hourly Vibe - START
				TupletInteger(HOURLY_VIBE_KEY,blnhourly_vibe),
			//YWeather 2.3 - REQ02. Hourly Vibe - END
				TupletInteger(HOURLY_VIBE_START_KEY,0),
				TupletInteger(HOURLY_VIBE_END_KEY,9),
				TupletInteger(HIDE_BAT_KEY,batt_status),
				TupletInteger(FONT_KEY, intUI), //INITIALIZE TO LAST SAVED
                }; //TUPLET INITIAL VALUES
        
                app_sync_init(&sync, sync_buffer, sizeof(sync_buffer), initial_values,
                ARRAY_LENGTH(initial_values), sync_tuple_changed_callback,
                NULL, NULL);
	
}


static void init_callback(void *context) {
       
        //Subscribe to the accelerometer event.
        accel_tap_service_subscribe(accel_tap_handler);
    
}

void handle_init(void)
{
	

        //Define Resources
    	ResHandle res_d;
        ResHandle res_u;
        ResHandle res_t;
        ResHandle res_temp;
  
		//load persistent storage options
		color_inverted = persist_read_bool(INVERT_COLOR_KEY);
		blnvibes = persist_read_bool(VIBES_KEY);
		language = persist_read_int(language_key);
		ICON_CODE = persist_read_int(WEATHER_ICON_KEY);
		persist_read_string(WEATHER_TEMPERATURE_KEY, temp, sizeof(temp));
		persist_read_string(WEATHER_HIGH_KEY, high, sizeof(high));
		persist_read_string(WEATHER_LOW_KEY, low, sizeof(low));
		persist_read_string(SUNRISE_KEY, sunrise, sizeof(sunrise));
		persist_read_string(SUNSET_KEY, sunset, sizeof(sunset));
		persist_read_string(WIND_KEY, wind, sizeof(wind));
		//wdirection =  persist_read_int(WDIRECTION_KEY); 
		persist_read_string(WDIRECTION_KEY, strwdirection, sizeof(strwdirection));
		persist_read_string(FORECAST_HIGH1_KEY, day1H, sizeof(day1H));
		persist_read_string(FORECAST_LOW1_KEY, day1L, sizeof(day1L));
		persist_read_string(FORECAST_HIGH2_KEY, day2H, sizeof(day2H));
		persist_read_string(FORECAST_LOW2_KEY, day2L, sizeof(day2L));
		persist_read_string(FORECAST_HIGH3_KEY, day3H, sizeof(day3H));
		persist_read_string(FORECAST_LOW3_KEY, day3L, sizeof(day3L));
		ESDuration_ms = persist_read_int(EXTRA_ESDURATION_KEY);
		timeout_ms = persist_read_int(EXTRA_TIMER_KEY);
		//ensures timeout_ms is never less than 5mins (if so, set to 30mins)
		if (timeout_ms<35000) {timeout_ms=180000;}
		//ensures Extended Screen duration is never less than 5secs (if so, set to 5secs)
		//if (ESDuration_ms < 5000){ESDuration_ms = 5000;} 
		bln3daysForecast = persist_read_int(EXTRA_FORECAST_KEY);
	//YWeather 2.3 - REQ01. Display Seconds - START
		blnseconds = persist_read_int(DISPLAY_SECONDS_KEY);
	//YWeather 2.3 - REQ01. Display Seconds - END
	//YWeather 2.3 - REQ02. Hourly Vibe - START
		blnhourly_vibe = persist_read_int(HOURLY_VIBE_KEY);
	//YWeather 2.3 - REQ02. Hourly Vibe - END
		batt_status = persist_read_int(HIDE_BAT_KEY);
		intUI = persist_read_int(FONT_KEY);
	
		init_ESDuration_ms = ESDuration_ms/1000;
		init_timeout_ms = timeout_ms/60000;
	

        //Create the main window
        my_window = window_create();
        window_stack_push(my_window, true /* Animated */);
		window_set_background_color(my_window, GColorBlack);          
        

		if (intUI == 1){
			res_t = resource_get_handle(RESOURCE_ID_Modern_53); // Time font
			res_d = resource_get_handle(RESOURCE_ID_Modern_17); // Date font
			res_u = resource_get_handle(RESOURCE_ID_Modern_10); // Last Update font
			res_temp = resource_get_handle(RESOURCE_ID_Modern_47); //Temperature  
			
		}
		else if (intUI == 2){
			res_t = resource_get_handle(RESOURCE_ID_Aunchanted_bold_51); // Time font
			res_d = resource_get_handle(RESOURCE_ID_Aunchanted_bold_20); // Date font
			res_u = resource_get_handle(RESOURCE_ID_Aunchanted_bold_14); // Last Update font
			res_temp = resource_get_handle(RESOURCE_ID_Aunchanted_bold_51); //Temperature  
			
		}
		else{ //default to Futura
			res_t = resource_get_handle(RESOURCE_ID_FUTURA_CONDENSED_53); // Time font
			res_d = resource_get_handle(RESOURCE_ID_FUTURA_17); // Date font
			res_u = resource_get_handle(RESOURCE_ID_FUTURA_10); // Last Update font
			res_temp = resource_get_handle(RESOURCE_ID_FUTURA_43); //Temperature  
			
		}

     

		font_date = fonts_load_custom_font(res_d);
        font_update = fonts_load_custom_font(res_u);
        font_time = fonts_load_custom_font(res_t);
        font_temperature = fonts_load_custom_font(res_temp);	


       
      
		//Load the Main Window
		LoadMainWindow();
		//Get Current Date
		getDate();
	//YWeather 2.3 - REQ01. Display Seconds - START
		getTime();
	//YWeather 2.3 - REQ01. Display Seconds - END
	
        // Ensures time is displayed immediately (will break if NULL tick event accessed).
         // (This is why it's a good idea to have a separate routine to do the update itself.)
	
		//Initialize the Message Service
		SetupMessages();
	               
	  // Set up the update layer callback
	
		SubscribeTickEvent();
		
		//Enable the Battery check event
		battery_state_service_subscribe(&handle_battery);
		//Enable the Bluetooth check event
		bluetooth_connection_service_subscribe(&handle_bluetooth);
		
		//setup the timer to refresh the weather info every 30min
		timer = app_timer_register(timeout_ms, timer_callback, NULL);
		
		//setup a timer to wait 5 seconds before subscribe to tap events.
		//that will avoid a crash when loading extended screen before all the
		//componenets are properly loaded.
		initialize = app_timer_register(5000, init_callback, NULL);
		
        
} //HANDLE_INIT



//**********************//
// Kill the application //
//**********************//
void handle_deinit(void)
{
  //text_layer_destroy(text_layer);


        //Unsuscribe services
        tick_timer_service_unsubscribe();
        battery_state_service_unsubscribe();
        bluetooth_connection_service_unsubscribe();
		accel_tap_service_unsubscribe();

	
        //Deallocate custom fonts
        fonts_unload_custom_font(font_date);
        fonts_unload_custom_font(font_update);
        fonts_unload_custom_font(font_time);
        fonts_unload_custom_font(font_temperature);
        
        //Deallocate the main window
         window_destroy(my_window);

} //HANDLE_DEINIT


//*************//
// ENTRY POINT //
//*************//
int main(void)
{        
        handle_init();
        app_event_loop();
        handle_deinit();
}



