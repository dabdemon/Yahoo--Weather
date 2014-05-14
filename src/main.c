//Declare and Import references
#include "pebble.h"
#include "pebble_fonts.h"
#include "language.h"
#include "variables.h"
#include "bitmaps.h"
#include "textlayers.h"
#include "frames.h"

 
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
	  		Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_CHAR);
            bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
  } else {
	  //snprintf(battery_text, sizeof(battery_text), "%d%%", charge_state.charge_percent);

	  
	  //WHILE RUNNING LOW, BATT STATUS WILL ALWAYS DISPLAY  
         //set the new batt_image
         //DO NOT display the batt_icon all the time. it is annoying.
         if (charge_state.charge_percent <=10) //If the charge is between 0% and 10%
         {
			 Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_EMPTY);
             bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
         }
	  //CHECK IF BATTERY STATUS SHOULD DISPLAY ALL THE TIME OR JUST WHILE RUNNING LOW
	  else if (batt_status){
		 if (charge_state.charge_percent <=20) //If the charge is between 10% and 20%
         {
			 Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_20);
             bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
         }
															
		 else if (charge_state.charge_percent <=40) //If the charge is between 20% and 40%
         {
			 Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_40);
             bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
         }

		 else if (charge_state.charge_percent <=60) //If the charge is between 40% and 60%
         {
			 Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_60);
             bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
         }
															
		 else if (charge_state.charge_percent <=80) //If the charge is between 60% and 80%
         {
			 Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_80);
             bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
         }
															
		 else if (charge_state.charge_percent >80) //If the charge is between 80% and 100%
         {
			 Batt_image = gbitmap_create_with_resource(RESOURCE_ID_BATT_FULL);
             bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
         }
		  
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
			if (blnvibes==true){vibes_double_pulse();}
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


	//Try new translation method

		//Get the number of the weekday
		strftime(weekday_text,sizeof(weekday_text),"%u",tz1Ptr);
		int ia = weekday_text[0] - '0'; 
		int ib = (language*7)+ia;

		//Get the number of the month	
		strftime(month_text,sizeof(month_text),"%m",tz1Ptr);
		int ic = month_text[1] - '0';
		if (month_text[0]=='1'){ic=ic+10;}			
		int id = (language*12)+ic;

	if(language==100){ //ENGLISH

		//remove the chinese week day
		if (chinese_day) {gbitmap_destroy(chinese_day);}
		bitmap_layer_set_bitmap(chinese_day_layer, NULL);

		//Get the English fortmat
		strftime(month_text,sizeof(month_text),"%B %e",tz1Ptr);
		strftime(weekday_text,sizeof(weekday_text),"%A",tz1Ptr);

		text_layer_set_text(Weekday_Layer,weekday_text); //Update the weekday layer  
		text_layer_set_text(date_layer,month_text); 

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

	}

}


//*****************//
// AppSync options //
//*****************//

        static AppSync sync;
        static uint8_t sync_buffer[256];



        static void sync_tuple_changed_callback(const uint32_t key,
                                        const Tuple* new_tuple,
                                        const Tuple* old_tuple,
                                        void* context) {

        
  // App Sync keeps new_tuple in sync_buffer, so we may use it directly
  switch (key) {
    case WEATHER_ICON_KEY:
	    if (weather_image != NULL){gbitmap_destroy(weather_image);}

	  		weather_image = gbitmap_create_with_resource(WEATHER_ICONS[new_tuple->value->uint8]);
      		bitmap_layer_set_bitmap(weather_icon_layer, weather_image);
	  		ICON_CODE = new_tuple->value->uint8;
	  	  	persist_write_int(WEATHER_ICON_KEY, new_tuple->value->uint8);
      		break;

    case WEATHER_TEMPERATURE_KEY:
         //Update the temperature
      		text_layer_set_text(Temperature_Layer, new_tuple->value->cstring);
	    	persist_write_string(WEATHER_TEMPERATURE_KEY, new_tuple->value->cstring);
         //Set the time on which weather was retrived
         	memcpy(&last_update, time_text, strlen(time_text));
         	text_layer_set_text(Last_Update, last_update);
      		break;

     case WEATHER_CITY_KEY:
	  		persist_write_string(WEATHER_CITY_KEY, new_tuple->value->cstring);
         	text_layer_set_text(Location_Layer, new_tuple->value->cstring);
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
	        memcpy(&high,  new_tuple->value->cstring, strlen( new_tuple->value->cstring));
	    	persist_write_string(WEATHER_HIGH_KEY, new_tuple->value->cstring);
      		break;
		case WEATHER_LOW_KEY:
	  	  	//Save the Low temperature
	  		memcpy(&low,  new_tuple->value->cstring, strlen( new_tuple->value->cstring));
	    	persist_write_string(WEATHER_LOW_KEY, new_tuple->value->cstring);
      		break;
		case SUNRISE_KEY:
	  	  	//Save the Sunrise Time
	  	  	memcpy(&sunrise,  new_tuple->value->cstring, strlen(sunrise));
	    	persist_write_string(SUNRISE_KEY, new_tuple->value->cstring);
      		break;
		case SUNSET_KEY:
	  	  	//Save the Sunset Time
	  	  	memcpy(&sunset,  new_tuple->value->cstring, strlen(sunset));
	    	persist_write_string(SUNSET_KEY, new_tuple->value->cstring);
      		break;
		case WIND_KEY:
	  	  	 //Save the Wind Speed
	  	  	memcpy(&wind,  new_tuple->value->cstring, strlen(wind));
	    	persist_write_string(WIND_KEY, new_tuple->value->cstring);
      		break;
	  
	  	case WDIRECTION_KEY:
	  	  	//Save the Wind Direction
	  	  	wdirection = new_tuple->value->uint32;
	  	  	persist_write_int(WDIRECTION_KEY, wdirection);
      		break;
	  
  }
}

//************************//
// Capture the Tick event //
//************************//
void handle_tick(struct tm *tick_time, TimeUnits units_changed)
{
                     
        if (units_changed & MINUTE_UNIT)
        {

                        /*
                        if (units_changed & DAY_UNIT)
                        {        
                        } // DAY CHANGES
                        */

                        //Format the time        
                        if (clock_is_24h_style())
                        {
                                strftime(time_text, sizeof(time_text), "%H:%M", tick_time);
                        }
                        else
                        {
                                strftime(time_text, sizeof(time_text), "%I:%M", tick_time);
                        }
                
                        //Remove the leading 0s
						if (time_text[0]=='0') {memcpy(&time_text," ",1);}
			
						//Set the time to the Time Layer
                        text_layer_set_text(Time_Layer, time_text);
                
                        //Check Battery Status
                        handle_battery(battery_state_service_peek());
                
                        //Check BT Status
                        handle_bluetooth(bluetooth_connection_service_peek());

        } //MINUTE CHANGES
	     if (units_changed & DAY_UNIT){
			 	//Update the date
			 	getDate();}

	
} //HANDLE_TICK


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
	if(moon_icon_layer){bitmap_layer_destroy(moon_icon_layer);}
	
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
	memset(&city[0], 0, sizeof(city));
	persist_read_string(WEATHER_CITY_KEY, city, sizeof(city));
	text_layer_set_text(Location_Layer, city);
	
	//set back the temperature
	persist_read_string(WEATHER_TEMPERATURE_KEY, temperature, sizeof(temperature));
	text_layer_set_text(Temperature_Layer, temperature);
	
	//set back the last update
	text_layer_set_text(Last_Update, last_update);
	
	//if color inverted, then create the inverted layer
	InvertColors(color_inverted);
	
}


static void forecast_callback(void *context) {
       
        //Refresh the weather
        LoadTemperature();
    

}

/*****************************/
/* Decode the Wind Direction */
/*****************************/

void windDirection()
{
/*
Wind directions
	
N 348.75 - 11.25
NNE 11.25 - 33.75
NE 33.75 - 56.25
ENE 56.25 - 78.75
E 78.75 - 101.25
ESE 101.25 - 123.75
SE 123.75 - 146.25
SSE 146.25 - 168.75
S 168.75 - 191.25
SSW 191.25 - 213.75
SW 213.75 - 236.25
WSW 236.25 - 258.75
W 258.75 - 281.25
WNW 281.25 - 303.75
NW 303.75 - 326.25
NNW 326.25 - 348.75

*/
	
	memset(&strwdirection[0],0,strlen(strwdirection));
	
	if((wdirection>348)||(wdirection<12)){memcpy(&strwdirection, "N", 1);}
	else if((wdirection>11)&&(wdirection<34)){memcpy(&strwdirection, "NNE", 3);}
	else if((wdirection>33)&&(wdirection<57)){memcpy(&strwdirection, "NE", 2);}
	else if((wdirection>56)&&(wdirection<79)){memcpy(&strwdirection, "ENE", 3);}
	else if((wdirection>78)&&(wdirection<102)){memcpy(&strwdirection, "E", 1);}
	else if((wdirection>101)&&(wdirection<124)){memcpy(&strwdirection, "ESE", 3);}
	else if((wdirection>123)&&(wdirection<147)){memcpy(&strwdirection, "SE", 2);}
	else if((wdirection>146)&&(wdirection<169)){memcpy(&strwdirection, "SSE", 3);}
	else if((wdirection>168)&&(wdirection<191)){memcpy(&strwdirection, "S", 1);}
	else if((wdirection>191)&&(wdirection<214)){memcpy(&strwdirection, "SSW", 3);}
	else if((wdirection>214)&&(wdirection<237)){memcpy(&strwdirection, "SW", 2);}
	else if((wdirection>237)&&(wdirection<259)){memcpy(&strwdirection, "WSW", 3);}
	else if((wdirection>259)&&(wdirection<282)){memcpy(&strwdirection, "W", 1);}
	else if((wdirection>282)&&(wdirection<304)){memcpy(&strwdirection, "WNW", 3);}
	else if((wdirection>304)&&(wdirection<327)){memcpy(&strwdirection, "NW", 2);}
	else if((wdirection>326)&&(wdirection<349)){memcpy(&strwdirection, "NNW", 3);}

}

/*********************************************************/
/* Format Sunrise/Sunset time based on Pebble's settings */
/*********************************************************/
void formatSunset(){
	
	time_t actualPtr = time(NULL);
	
	//Split the sunset hour and minutes (assume sunset is always after noon)
	
	if (sunset[1]==':'){
		
	
		//hours
		iHours = sunset[0] - '0';
		//minutes
		iMinutes = sunset[2] - '0';
		iMinutes2 = sunset[3] - '0';
		
		iMinutes = ((iMinutes*10)+iMinutes2);
	}
	else{
		//hours
		iHours = sunset[0] - '0';
		iHours2 = sunset[1] - '0';
		
		iHours = ((iHours*10)+iHours2);
		
		//minutes
		iMinutes = sunset[3] - '0';
		iMinutes2 = sunset[4] - '0';
		
		iMinutes = ((iMinutes*10)+iMinutes2);
		
	}

	//SUNSET
	struct tm *tz1Ptr = gmtime(&actualPtr);
	tz1Ptr->tm_hour = iHours+12; //assume sunset is always after noon
	tz1Ptr->tm_min = iMinutes;
	
	
	if (clock_is_24h_style()){strftime(sunset, sizeof(sunset), "%H:%M", tz1Ptr);}
	else {strftime(sunset, sizeof(sunset), "%I:%M", tz1Ptr);}	
	
	//Remove the leading 0s
	if (sunset[0]=='0') {memcpy(&sunset," ",1);}
}

void formatSunrise(){
	
	time_t actualPtr2 = time(NULL);
	
	//Split the sunset hour and minutes (assume sunrise is always before noon)
	
	if (sunrise[1]==':'){
		
	
		//hours
		iHours = sunrise[0] - '0';
		//minutes
		iMinutes = sunrise[2] - '0';
		iMinutes2 = sunrise[3] - '0';
		
		iMinutes = ((iMinutes*10)+iMinutes2);
	}
	else{
		//hours
		iHours = sunrise[0] - '0';
		iHours2 = sunrise[1] - '0';
		
		iHours = ((iHours*10)+iHours2);
		
		//minutes
		iMinutes = sunrise[3] - '0';
		iMinutes2 = sunrise[4] - '0';
		
		iMinutes = ((iMinutes*10)+iMinutes2);
		
	}


	//SUNSET
	struct tm *tz2Ptr = gmtime(&actualPtr2);
	tz2Ptr->tm_hour = iHours; //assume sunrise is always before noon
	tz2Ptr->tm_min = iMinutes;
	
	
	if (clock_is_24h_style()){strftime(sunrise, sizeof(sunrise), "%H:%M", tz2Ptr);}
	else {strftime(sunrise, sizeof(sunrise), "%I:%M", tz2Ptr);}	
	
	//Remove the leading 0s
	if (sunrise[0]=='0') {memcpy(&sunrise," ",1);}
}

/****************************/
/* Calculate the Moon Phase */
/****************************/

//Extracted from "Ninety Weather Moon" by Novo//
int moon_phase(int y, int m, int d) {
    /*
      calculates the moon phase (0-7), accurate to 1 segment.
      0 = > new moon.
      4 => full moon.
    */
    int c,e;
    double jd;
    int b;

    if (m < 3) {
        y--;
        m += 12;
    }
    ++m;
    c = 365.25*y;
    e = 30.6*m;
    jd = c+e+d-694039.09;  	/* jd is total days elapsed */
    jd /= 29.53;        	/* divide by the moon cycle (29.53 days) */
    b = jd;		   			/* int(jd) -> b, take integer part of jd */
    jd -= b;		   		/* subtract integer part to leave fractional part of original jd */
    b = jd*8 + 0.5;	   		/* scale fraction from 0-8 and round by adding 0.5 */
    b = b & 7;		   		/* 0 and 8 are the same so turn 8 into 0 */
    return b;
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
	//Destroy the temperature Layer
	if(Temperature_Layer){text_layer_destroy(Temperature_Layer);}
	if(weather_icon_layer){bitmap_layer_destroy(weather_icon_layer);}
	if(Location_Layer){text_layer_destroy(Location_Layer);}
	if(Last_Update){text_layer_destroy(Last_Update);}
	
	

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
	formatSunrise();
	text_layer_set_text(Sunrise_Layer,sunrise);
	
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
	formatSunset();
	text_layer_set_text(Sunset_Layer,sunset);
	
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
	
	wdirection =  persist_read_int(WDIRECTION_KEY); 
	//decode the wind direction code to text
	windDirection();
	text_layer_set_text(WDirection_Layer,strwdirection);
	
	//Display the wind icon
	if (wind_image){gbitmap_destroy(wind_image);}
	wind_image = gbitmap_create_with_resource(RESOURCE_ID_WIND_SMALL);
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
	
	//setup the timer to set back the temperature after 5sec
	weather = app_timer_register(5000, forecast_callback, NULL);

	
}


//************************************//
//** Capture the accelerometer Taps **//
//************************************//

void accel_tap_handler(AccelAxisType axis, int32_t direction){

    //send_cmd();
	//Just fire the event while displaying the primary screen
		if (blnForecast==false){LoadForecast();}

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
        
                //Display the Batt layer
                Batt_icon_layer = bitmap_layer_create(BATT_FRAME);
                bitmap_layer_set_bitmap(Batt_icon_layer, Batt_image);
                layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(Batt_icon_layer));
        
                //Display the BT layer
                BT_icon_layer = bitmap_layer_create(BT_FRAME);
                bitmap_layer_set_bitmap(BT_icon_layer, BT_image);
                layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(BT_icon_layer));
        
                //Display the Time layer
                Time_Layer = text_layer_create(TIME_FRAME);
				text_layer_set_text_color(Time_Layer, GColorWhite);
	            text_layer_set_background_color(Time_Layer, GColorClear);
                text_layer_set_font(Time_Layer, font_time);
                text_layer_set_text_alignment(Time_Layer, GTextAlignmentCenter);
                layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(Time_Layer));
        
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
				MyTupletCString(WEATHER_TEMPERATURE_KEY,temperature),
                MyTupletCString(WEATHER_CITY_KEY, ""),
				TupletInteger(INVERT_COLOR_KEY, color_inverted),
				TupletInteger(language_key, language), //INITIALIZE TO LAST SAVED
				TupletInteger(VIBES_KEY, blnvibes),
				MyTupletCString(WEATHER_HIGH_KEY,high),
				MyTupletCString(WEATHER_LOW_KEY,low),
				MyTupletCString(SUNRISE_KEY,sunrise),
				MyTupletCString(SUNSET_KEY,sunset),
				MyTupletCString(WIND_KEY,wind),
				TupletInteger(WDIRECTION_KEY,wdirection),
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
		persist_read_string(WEATHER_TEMPERATURE_KEY, temperature, sizeof(temperature));
		persist_read_string(WEATHER_HIGH_KEY, high, sizeof(high));
		persist_read_string(WEATHER_LOW_KEY, low, sizeof(low));
		persist_read_string(SUNRISE_KEY, sunrise, sizeof(sunrise));
		persist_read_string(SUNSET_KEY, sunset, sizeof(sunset));
		persist_read_string(WIND_KEY, wind, sizeof(wind));
		wdirection =  persist_read_int(WDIRECTION_KEY); 
	
        //Create the main window
        my_window = window_create();
        window_stack_push(my_window, true /* Animated */);
		window_set_background_color(my_window, GColorBlack);          
        
        //Load the custom fonts
        res_t = resource_get_handle(RESOURCE_ID_FUTURA_CONDENSED_53); // Time font
        res_d = resource_get_handle(RESOURCE_ID_FUTURA_17); // Date font
        res_u = resource_get_handle(RESOURCE_ID_FUTURA_10); // Last Update font
        res_temp = resource_get_handle(RESOURCE_ID_FUTURA_43); //Temperature     
                
    	font_date = fonts_load_custom_font(res_d);
        font_update = fonts_load_custom_font(res_u);
        font_time = fonts_load_custom_font(res_t);
        font_temperature = fonts_load_custom_font(res_temp);
       
        
		//Load the Main Window
		LoadMainWindow();
		//Get Current Date
		getDate();
	
        // Ensures time is displayed immediately (will break if NULL tick event accessed).
         // (This is why it's a good idea to have a separate routine to do the update itself.)
	
		//Initialize the Message Service
		SetupMessages();
	               
	  // Set up the update layer callback
	
		time_t now = time(NULL);
		struct tm *current_time = localtime(&now);
		handle_tick(current_time, MINUTE_UNIT);
		tick_timer_service_subscribe(MINUTE_UNIT, &handle_tick);
		
		//Enable the Battery check event
		battery_state_service_subscribe(&handle_battery);
		//Enable the Bluetooth check event
		bluetooth_connection_service_subscribe(&handle_bluetooth);
		
		//setup the timer to refresh the weather info every 30min
		//const uint32_t timeout_ms = 1800000;
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
  /*      
        if (BT_image){gbitmap_destroy(BT_image);}
        if (Batt_image){gbitmap_destroy(Batt_image);}
        if (weather_image){gbitmap_destroy(weather_image);}
		if (chinese_day) {gbitmap_destroy(chinese_day);}
	
		if (high_image){gbitmap_destroy(high_image);}
		if (low_image){gbitmap_destroy(low_image);}
		if (sunrise_image){gbitmap_destroy(sunrise_image);}
		if (sunset_image){gbitmap_destroy(sunset_image);}
		if (wind_image){gbitmap_destroy(wind_image);}

        
        //Deallocate layers
        text_layer_destroy(Time_Layer);
        text_layer_destroy(date_layer);
        text_layer_destroy(Weekday_Layer);
        text_layer_destroy(Temperature_Layer);        
        text_layer_destroy(Location_Layer);        
        text_layer_destroy(Last_Update);        
	    inverter_layer_destroy(inv_layer);
	
		text_layer_destroy(High_Layer);
		text_layer_destroy(Low_Layer);
		text_layer_destroy(Sunrise_Layer);
		text_layer_destroy(Sunset_Layer);
		text_layer_destroy(Wind_Layer);
		text_layer_destroy(WDirection_Layer);
		bitmap_layer_destroy(sunrise_icon_layer);
		bitmap_layer_destroy(sunset_icon_layer);
		bitmap_layer_destroy(high_icon_layer);
		bitmap_layer_destroy(low_icon_layer);
		bitmap_layer_destroy(wind_icon_layer);
 */
	
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



