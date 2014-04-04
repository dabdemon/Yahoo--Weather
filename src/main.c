//Declare and Import references
#include "pebble.h"
#include "pebble_fonts.h"

 
//UIDs:
	//English: 35a28a4d-0c9f-408f-9c6d-551e65f03186
	//Spanish: 3ab59c04-142f-4ff1-b90d-aab93ce54a32
	//Italian: 6279f406-1114-4b2f-852d-65b0e8ff2a73

#define WEEKDAY_FRAME    (GRect(5, 2, 102, 168-145)) //,,95,
#define BATT_FRAME       (GRect(103, 4, 40, 168-146)) //98,,
#define BT_FRAME         (GRect(127, 4, 23, 168-146))
#define TIME_FRAME       (GRect(0, 15, 144, 168-16))
#define DATE_FRAME       (GRect(1, 69, 139, 168-62))
	
#define CHIN_WEEKDAY_FRAME    (GRect(5, 2, 60, 168-145)) //,,95,
/*
#define MAX_FRAME (GRect(65, 90, 40, 168-145))
#define MIN_FRAME (GRect(105, 90, 40, 168-145))
*/
        
#define LAST_UPDATE_FRAME (GRect(110, 148, 34, 168-145))
#define LOCATION_FRAME    (GRect(1, 148, 110, 168-145))
#define WEATHER_FRAME     (GRect(5, 90, 65, 168-108))
#define TEMPERATURE_FRAME (GRect(65, 95, 82, 168-118))
        

        
//******************//
// DEFINE THE ICONS //
//******************//        

static const uint32_t WEATHER_ICONS[] = {
  RESOURCE_ID_ICON_CLEAR_DAY,
  RESOURCE_ID_ICON_CLEAR_NIGHT,
  RESOURCE_ID_ICON_WIND,
  RESOURCE_ID_ICON_COLD,
  RESOURCE_ID_ICON_HOT,
  RESOURCE_ID_ICON_PARTLY_CLOUDY_DAY,
  RESOURCE_ID_ICON_PARTLY_CLOUDY_NIGHT,
  RESOURCE_ID_ICON_FOG,
  RESOURCE_ID_ICON_RAIN,
  RESOURCE_ID_ICON_SNOW,
  RESOURCE_ID_ICON_SLEET,
  RESOURCE_ID_ICON_SNOW_SLEET,
  RESOURCE_ID_ICON_RAIN_SLEET,
  RESOURCE_ID_ICON_RAIN_SNOW,
  RESOURCE_ID_ICON_CLOUDY,
  RESOURCE_ID_ICON_THUNDER,
  RESOURCE_ID_ICON_NOT_AVAILABLE,
  RESOURCE_ID_ICON_DRIZZLE,
};

//*********************//
// DEFINE THE WEEKDAYS //
//*********************// 
static const char *WEEKDAYS[] = {
	NULL,
	//SPANISH - 0
	"Lunes",
	"Martes",
	"Miércoles",
	"Jueves",
	"Viernes",
	"Sábado", 
	"Domingo", 
	//ITALIAN - 1
	"Lunedi",
	"Martedi",
	"Mercoledi", 
	"Giovedi", 
	"Venerdi", 
	"Sabato", 
	"Domenica", 
	//GERMAN - 2
	"Montag", 
	"Dienstag", 
	"Mittwoch", 
	"Donnerstag", 
	"Freitag", 
	"Samstag", 
	"Neděle",
	//CZECH - 3
	"Pondělí",
	"Úterý", 
	"Streda", 
	"Čtvrtek", 
	"Pátek", 
	"Sobota", 
	"Neděle", 
	//FRENCH - 4
	"Lundi",
	"Mardi", 
	"Mercredi",
	"Jeudi", 
	"Vendredi", 
	"Samedi", 
	"Dimanche", 
	//PORTUGUESE - 5
	"Segunda", 
	"Terça", 
	"Quarta",
	"Quinta", 
	"Sexta", 
	"Sábado", 
	"Domingo", 
	//FINNISH - 6
	"Maanantai", 
	"Tiistai", 
	"Keskiviikko",
	"Torstai", 
	"Perjantai",
	"Lauantai",
	"Sunnuntai", 
	//DUTCH - 7
	"Maandag", 
	"Dinsdag", 
	"Woensdag", 
	"Donderdag",
	"Vrijdag", 
	"Zaterdag", 
	"Zondag", 
	//POLISH - 8
	"Poniedzialek",
	"Wtorek", 
	"Sroda", 
	"Czwartek",
	"Piątek", 
	"Sobota",
	"Niedziela",
	//SWEDISH - 9
	"Måndag",
	"Tisdag", 
	"Onsdag", 
	"Torsdag", 
	"Fredag", 
	"Lördag",
	"Söndag ",
	//DANISH - 10
	"Mandag",
	"Tirsdag",
	"Onsdag",
	"Torsdag",
	"Fredag", 
	"Lørdag",
	"Søndag ",
	//CATALAN - 11
	"Dilluns", 
	"Dimarts",
	"Dimecres", 
	"Dijous", 
	"Divendres",
	"Dissabte",
	"Diumenge ",
	//HUNGARIAN - 12
	"Hétfo",
	"Kedd", 
	"Szerda",
	"Csütörtök",
	"Péntek", 
	"Szombat",
	"Vasárnap", 
	//NORWEGIAN - 13
	"Mandag",
	"Tirsdag",
	"Onsdag",
	"Torsdag",
	"Fredag", 
	"Lørdag",
	"Søndag ",  
};

static const char *MONTHS[] = {
	NULL,
	 //SPANISH - 0
	" enero",
	" febrero",
	" marzo",
	" abril",
	" mayo",
	" junio",
	" julio",
	" agosto", 
	" septiembre",
	" octubre", 
	" noviembre", 
	" diciembre", 
	//ITALIAN - 1
	" gennaio", 
	" febbraio",
	" marzo",
	" aprile",
	" maggio",
	" giugno",
	" luglio",
	" agosto",
	" settembre",
	" ottobre",
	" novembre",
	" dicembre",
	//GERMAN - 2
	".Januar",
	".Februar",
	".März",
	".April",
	".Mai", 
	".Juni", 
	".Juli", 
	".August",
	".September",
	".Oktober",
	".November",
	".Dezember",
	//CZECH - 3
	"Leden ",
	"Únor ",
	"Brezen ",
	"Duben ", 
	"Květen ", 
	"Červen ",
	"Červenec ", 
	"Srpen ",
	"Zárí ",
	"Ríjen ",
	"Listopad ",
	"Prosinec ",
	//FRENCH - 4
	" janvier",
	" février", 
	" mars", 
	" avril", 
	" mai", 
	" juin", 
	" juillet", 
	" août", 
	" septembre", 
	" octobre",
	" novembre", 
	" décembre", 
	//PORTUGUESE - 5
	" Janeiro", 
	" Fevereiro", 
	" Março", 
	" Abril",
	" Maio",
	" Junho",
	" Julho",
	" Agosto",
	" Setembro",
	" Outubro",
	" Novembro",
	" Dezembro",
	//FINNISH - 6
	". Tammikuu",
	". Helmikuu", 
	". Maaliskuu"
	". Huhtikuu", 
	". Toukokuu", 
	". Kesäkuu", 
	". Heinäkuu", 
	". Elokuu", 
	". Syyskuu", 
	". Lokakuu", 
	". Marraskuu", 
	". Joulukuu", 
	//DUTCH - 7
	" Januari", 
	" Februari",
	" Maart",
	" April",
	" Mei", 
	" Juni", 
	" Juli", 
	" Augustus", 
	" September", 
	" Oktober", 
	" November",
	" December", 
	//POLISH - 8
	" stycznia",
	" lutego", 
	" marca", 
	" kwietnia", 
	" maja", 
	" czerwca",
	" lipca", 
	" sierpnia",
	" wrzesnia",
	" pazdziernika",
	" listopada", 
	" grudnia", 
	//SWEDISH - 9
	" Januari", 
	" Februari",
	" Mars", 
	" April", 
	" Maj", 
	" Juni",
	" Juli", 
	" Augusti",
	" September", 
	" Oktober",
	" November", 
	" December", 
	//DANISH - 10
	". Januar",
	". Februar", 
	". Marts", 
	". April", 
	". Maj", 
	". Juni", 
	". Juli",
	". August",
	". September", 
	". Oktober", 
	". November",
	". December",
	//CATALAN - 11
	" Gener", 
	" Febrer", 
	" Març", 
	" Abril", 
	" Maig", 
	" Juny",
	" Juliol", 
	" Agost", 
	" Setembre", 
	" Octubre", 
	" Novembre", 
	" Desembre", 
	//HUNGARIAN - 12
	"január ", 
	"február ", 
	"március ",
	"április ", 
	"május ", 
	"június ", 
	"július ", 
	"augusztus ", 
	"szeptember ", 
	"október ",
	"november ", 
	"december ", 
	//NORWEGIAN - 13
	". januar", 
	". februar", 
	". mars", 
	". april", 
	". mai", 
	". juni", 
	". juli", 
	". august", 
	". september", 
	". oktober", 
	". november", 
	". desember", 
};
	

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
};

//Declare initial window        
        Window *my_window;

//Define the layers
        TextLayer *date_layer;                 // Layer for the date
        TextLayer *Time_Layer;                         // Layer for the time
        TextLayer *Weekday_Layer;                 //Layer for the weekday
        TextLayer *Last_Update;                 // Layer for the last update
        TextLayer *Location_Layer;                 // Layer for the last update
        TextLayer *Batt_Layer;                        //Layer for the BT connection
        TextLayer *BT_Layer;                        //Layer for the BT connection
        TextLayer *Temperature_Layer;        //Layer for the Temperature

        static GBitmap *BT_image;
        static BitmapLayer *BT_icon_layer; //Layer for the BT connection
        
        static GBitmap *Batt_image;
        static BitmapLayer *Batt_icon_layer; //Layer for the Battery status
        
        static GBitmap *weather_image;
        static BitmapLayer *weather_icon_layer; //Layer for the weather info

        static GBitmap *chinese_day;
        static BitmapLayer *chinese_day_layer; //Layer for the weather info

//Define and initialize variables
        //FONTS
        GFont font_date; // Font for date
        GFont font_time; // Font for time
        GFont font_update; // Font for last update
        GFont font_temperature;        // Font for the temperature

        //Vibe Control
        bool BTConnected = true;

        //Time control for weather refresh
        static AppTimer *timer;
        const uint32_t timeout_ms = 1800000; //30min (1min = 60000)

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
        
        bool translate_sp = true;
        int language = 0; 	
		bool color_inverted;
		int ICON_CODE;
		bool batt_status = true; //If true, display the battery status all the time; if false, just when running low (<10%)

		bool blnvibes;

		InverterLayer *inv_layer;

//**************************//
// Check the Battery Status //
//**************************//

static void handle_battery(BatteryChargeState charge_state) {
          static char battery_text[] = "100%";
	
	//kill previous batt_image to avoid invalid ones.
	if (Batt_image) {gbitmap_destroy(Batt_image);}
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

static void vibes()
{
//************************//
// Vibes on disconnection //
//************************//

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
			if (BT_image) {gbitmap_destroy(BT_image);}
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
		    if (BT_image) {gbitmap_destroy(BT_image);}
            bitmap_layer_set_bitmap(BT_icon_layer, NULL);
			if (BTConnected == true){
			//setup the timer to catch false disconnections (5 secs)
         	timer = app_timer_register(5000, vibes, NULL);
			}
       
        }
	

        
} //handle_bluetooth


//Invert colors
void InvertColors(bool inverted)
{
	
	if (inverted){
		//Inverter layer
		inv_layer = inverter_layer_create(GRect(0, 0, 144, 168));
		layer_add_child(window_get_root_layer(my_window), (Layer*) inv_layer);
	}
	else{
		inverter_layer_destroy(inv_layer);
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
	
	//Get the Month + Day (English format)
	strftime(month_text,sizeof(month_text),"%B %e",tz1Ptr);
	strftime(weekday_text,sizeof(weekday_text),"%A",tz1Ptr);

	
	//Try new translation method
	if(language==100){ //ENGLISH
		
		//remove the chinese week day
		if (chinese_day) {gbitmap_destroy(chinese_day);}
		bitmap_layer_set_bitmap(chinese_day_layer, NULL);
		
		text_layer_set_text(Weekday_Layer,weekday_text); //Update the weekday layer  
		text_layer_set_text(date_layer,month_text); 
		
	}
	else if (language==99){//CHINESE
		
		//Work on retrieving the correct weekday
		//Get the Month
		strftime(month_text,sizeof(month_text),"%m/%d",tz1Ptr);
		
		if (chinese_day) {gbitmap_destroy(chinese_day);}
		chinese_day = gbitmap_create_with_resource(RESOURCE_ID_CHIN_SATURDAY);
		//Display the weekday in chinese
		bitmap_layer_set_bitmap(chinese_day_layer, chinese_day);
		text_layer_set_text(date_layer, month_text);
		
	}

	else{
		//remove the chinese week day
		if (chinese_day) {gbitmap_destroy(chinese_day);}
		bitmap_layer_set_bitmap(chinese_day_layer, NULL);
		//Get the number of the weekday
		strftime(weekday_text,sizeof(weekday_text),"%u",tz1Ptr);
		int ia = weekday_text[0] - '0'; 
		int ib = (language*7)+ia;
		//Set the weekeday
		text_layer_set_text(Weekday_Layer, WEEKDAYS[ib]); //Update the weekday layer  
		
		//Get the number of the month	
		strftime(month_text,sizeof(month_text),"%m",tz1Ptr);
		int ic = month_text[1] - '0';
		if (month_text[0]=='1'){ic=ic+10;}			
		int id = (language*12)+ic;
		
		//Get the day
		strftime(day_month,sizeof(day_month),"%e",tz1Ptr);
		
		//Set the month
		//text_layer_set_text(date_layer, MONTHS[id]);
				if (language == 3){text_layer_set_text(date_layer,strncat(day_month,MONTHS[id],strlen(MONTHS[id])));} //Czech
				else if (language == 12){text_layer_set_text(date_layer,strncat(day_month,MONTHS[id],strlen(MONTHS[id])));} //Hungarian
				else{text_layer_set_text(date_layer,strncat(day_month,MONTHS[id],strlen(MONTHS[id]))); }
		
	}


	
	/*
	if(language[0] == '4'){ //Chinese
		
			//Get the Month
			strftime(month_text,sizeof(month_text),"%m/%d",tz1Ptr);
			//Get the day
			strftime(day_text,sizeof(day_text),"%d",tz1Ptr);
			//Translate 
			TranslateDate();
		
		//Display the weekday in chinese
		bitmap_layer_set_bitmap(chinese_day_layer, chinese_day);
		text_layer_set_text(date_layer, month_text);
	}

	
	else if(language[0] != '0'){
		
			//remove the chinese week day
			if (chinese_day) {gbitmap_destroy(chinese_day);}
			bitmap_layer_set_bitmap(chinese_day_layer, NULL);
		
			//Get the Month
			strftime(month_text,sizeof(month_text),"%B",tz1Ptr);
			//Get the day
			strftime(day_text,sizeof(day_text),"%e",tz1Ptr);
			//Translate 
			TranslateDate();
			
			if(translate_sp){ 
				//Concatenate the day to the month
				//If Czech the month is before day
				if (language[0] == 'C'){strncat(month_text,day_text,strlen(day_text));}
				else if (language[0] == 'H'){strncat(month_text,day_text,strlen(day_text));} //Hungarian
				else {memcpy(&month_text, day_text, strlen(day_text));}    
			}
			else{
				//Keep the Month + Day (English format)
				strftime(month_text,sizeof(month_text),"%B %e",tz1Ptr);
			}
		
	}	
*/
		//text_layer_set_text(date_layer, day_text);
		//text_layer_set_text(Weekday_Layer, weekday_text); //Update the weekday layer    
		
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
	    if (weather_image) {gbitmap_destroy(weather_image);}

	  		weather_image = gbitmap_create_with_resource(WEATHER_ICONS[new_tuple->value->uint8]);
      		bitmap_layer_set_bitmap(weather_icon_layer, weather_image);
	  		//persist_write_int(WEATHER_ICON_KEY, new_tuple->value->uint8);
	  		ICON_CODE = new_tuple->value->uint8;
      		break;

    case WEATHER_TEMPERATURE_KEY:
         //Update the temperature
      		text_layer_set_text(Temperature_Layer, new_tuple->value->cstring);
         //Set the time on which weather was retrived
         	memcpy(&last_update, time_text, strlen(time_text));
         	text_layer_set_text(Last_Update, last_update);
      		break;

     case WEATHER_CITY_KEY:
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
         //Tuplet value = TupletInteger(1, 1);
	  	//Tuplet value = TupletCString(2, "loading...");
         Tuplet value = TupletInteger(5, 0);
        
         DictionaryIterator *iter;
         app_message_outbox_begin(&iter);
        
         if (iter == NULL) {
                return;
         }
        
         dict_write_tuplet(iter, &value);
         dict_write_end(iter);
        
         app_message_outbox_send();
	
		//JavaScript call is broken after 2h. Not sure if that is because lack of memory or Pebble App is breaking this.
		//Check that weather info is updated, and close the AppMessage and create a new session if not.
}

static void timer_callback(void *context) {

		//Developer vibe: confirm that timer is not killed
		//vibes_double_pulse();
	
        timer = app_timer_register(timeout_ms, timer_callback, NULL);
        
        //Refresh the weather
        send_cmd();
	       

}


//****************************//
// Initialize the application //
//****************************//

void handle_init(void)
{
        //Define Resources
    	ResHandle res_d;
        ResHandle res_u;
        ResHandle res_t;
        ResHandle res_temp;
	
	
	         // Setup messaging
                const int inbound_size = 256;
                const int outbound_size = 256;
	
                app_message_open(inbound_size, outbound_size);
        
                Tuplet initial_values[] = {
                TupletInteger(WEATHER_ICON_KEY, (uint8_t) 16), //INITIALIZE TO "N/A"
                TupletCString(WEATHER_TEMPERATURE_KEY, ""),
                TupletCString(WEATHER_CITY_KEY, ""),
				TupletInteger(INVERT_COLOR_KEY, persist_read_bool(INVERT_COLOR_KEY)),
				TupletInteger(language_key, (uint8_t) 0), //INITIALIZE TO SPANISH
				TupletInteger(VIBES_KEY, persist_read_bool(VIBES_KEY)),
                }; //TUPLET INITIAL VALUES
        
                 app_sync_init(&sync, sync_buffer, sizeof(sync_buffer), initial_values,
                ARRAY_LENGTH(initial_values), sync_tuple_changed_callback,
                NULL, NULL);
  
		//load persistent storage options
		color_inverted = persist_read_bool(INVERT_COLOR_KEY);
		blnvibes = persist_read_bool(VIBES_KEY);
		language = persist_read_int(language_key);
	
		//Init the date
		//getDate();

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
        
                //Display the Weather layer
                weather_icon_layer = bitmap_layer_create(WEATHER_FRAME);
                bitmap_layer_set_bitmap(weather_icon_layer, weather_image);
                layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(weather_icon_layer));
        
                //Display the Temperature layer
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
        
 
	            //Drawn the normal/inverted based on saved settings
	            InvertColors(color_inverted);
	
        // Ensures time is displayed immediately (will break if NULL tick event accessed).
         // (This is why it's a good idea to have a separate routine to do the update itself.)
                 
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
        
        if (BT_image){gbitmap_destroy(BT_image);}
        if (Batt_image){gbitmap_destroy(Batt_image);}
        if (weather_image){gbitmap_destroy(weather_image);}
		if (chinese_day) {gbitmap_destroy(chinese_day);}
	
        
        //Deallocate layers
        text_layer_destroy(Time_Layer);
        text_layer_destroy(date_layer);
        text_layer_destroy(Weekday_Layer);
        text_layer_destroy(Temperature_Layer);        
        text_layer_destroy(Location_Layer);        
        text_layer_destroy(Last_Update);        
	    inverter_layer_destroy(inv_layer);
        
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



