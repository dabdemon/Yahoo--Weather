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

//*************//
// Define KEYS //
//*************//


enum WeatherKey {
  WEATHER_ICON_KEY = 0x0,        // TUPLE_INT
  WEATHER_TEMPERATURE_KEY = 0x1, // TUPLE_CSTRING
  WEATHER_CITY_KEY = 0x2,        //	TUPLE_CSTRING
  INVERT_COLOR_KEY = 0x3,  		 // TUPLE_INT
  language_key = 0x4, 			// TUPLE_CSTRING
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
        static char day_text[] = "31";
        static char day_month[]= "31 SEPTEMBER";
        static char time_text[] = "00:00";
	  	static char inverted[]="B";
        
        bool translate_sp = true;
        static char language[] = "R"; 	//"0" = English //"E" = Spanish // "I" = Italian // "G" = German 
										// "C" = Czech // "F" = French // "P" = Portuguese // "X" = Finnish // "D" = Dutch
										//"1" = Polish // "S" = Swedish // "2" = Danish //"3" = Catalan // "H" = Hungarian
										// "N"= Norwegian
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

void TranslateDate(){
        
        if (language[0] == 'E'){ //SPANISH
			translate_sp= true;
                        
                        if (month_text[0] == 'J' && month_text[1] == 'a')
                        {
                                memcpy(&month_text, "   enero", strlen("   enero")+1); // January
                        }
                        
                        if (month_text[0] == 'F' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   febrero", strlen("   febrero")+1); // Febrary
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'r')
                        {
                                memcpy(&month_text, "   marzo", strlen("   marzo")+1); // March
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'p')
                        {
                                memcpy(&month_text, "   abril", strlen("   abril")+1); // April
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'y')
                        {
                                memcpy(&month_text, "   mayo", strlen("   mayo")+1); // May
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'n')
                        {
                                memcpy(&month_text, "   junio", strlen("   junio")+1); // June
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'l')
                        {
                                memcpy(&month_text, "   julio", strlen("   julio")+1); // July
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'u')
                        {
                                memcpy(&month_text, "   agosto", strlen("   agosto")+1); // August
                        }
                        
                        if (month_text[0] == 'S' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   septiembre", strlen("   septiembre")+1); // September
                        }
                        
                        if (month_text[0] == 'O' && month_text[1] == 'c')
                        {
                                memcpy(&month_text, "   octubre", strlen("   octubre")+1); // October
                        }
                        
                        if (month_text[0] == 'N' && month_text[1] == 'o')
                        {
                                memcpy(&month_text, "   noviembre", strlen("   noviembre")+1); // November
                        }
                        
                        if (month_text[0] == 'D' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   diciembre", strlen("   diciembre")+1); // December
                        }
                        
                        // Primitive hack to translate the day of week to another language
                        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
                        // Supported characters: A-Z, a-z, 0-9
                        
                        if (weekday_text[0] == 'M')
                        {
                                memcpy(&weekday_text, "Lunes", strlen("Lunes")+1); // Monday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Martes", strlen("Martes")+1); // Tuesday
                        }
                        
                        if (weekday_text[0] == 'W')
                        {
                                memcpy(&weekday_text, "Miércoles", strlen("Miércoles")+1); // Wednesday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
                        {
                                memcpy(&weekday_text, "Jueves", strlen("Jueves")+1); // Thursday
                        }
                        
                        if (weekday_text[0] == 'F')
                        {
                                memcpy(&weekday_text, "Viernes", strlen("Viernes")+1); // Friday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
                        {
                                memcpy(&weekday_text, "Sábado", strlen("Sábado")+1); // Saturday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Domingo", strlen("Domingo")+1); // Sunday
                        }

        }//END OF SPANISH
        else if (language[0] == 'I'){ //ITALIAN
			translate_sp= true;
			
                        if (month_text[0] == 'J' && month_text[1] == 'a')
                        {
                                memcpy(&month_text, "   gennaio", strlen("   gennaio")+1); // January
                        }
                        
                        if (month_text[0] == 'F' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   febbraio", strlen("   febbraio")+1); // Febrary
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'r')
                        {
                                memcpy(&month_text, "   marzo", strlen("   marzo")+1); // March
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'p')
                        {
                                memcpy(&month_text, "   aprile", strlen("   aprile")+1); // April
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'y')
                        {
                                memcpy(&month_text, "   maggio", strlen("   maggio")+1); // May
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'n')
                        {
                                memcpy(&month_text, "   giugno", strlen("   giugno")+1); // June
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'l')
                        {
                                memcpy(&month_text, "   luglio", strlen("   luglio")+1); // July
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'u')
                        {
                                memcpy(&month_text, "   agosto", strlen("   agosto")+1); // August
                        }
                        
                        if (month_text[0] == 'S' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   settembre", strlen("   settembre")+1); // September
                        }
                        
                        if (month_text[0] == 'O' && month_text[1] == 'c')
                        {
                                memcpy(&month_text, "   ottobre", strlen("   ottobre")+1); // October
                        }
                        
                        if (month_text[0] == 'N' && month_text[1] == 'o')
                        {
                                memcpy(&month_text, "   novembre", strlen("   novembre")+1); // November
                        }
                        
                        if (month_text[0] == 'D' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   dicembre", strlen("   dicembre")+1); // December
                        }
                        
                        // Primitive hack to translate the day of week to another language
                        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
                        // Supported characters: A-Z, a-z, 0-9
                        if (weekday_text[0] == 'M')
                        {
                                memcpy(&weekday_text, "Lunedi", strlen("Lunedi")+1); // Monday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Martedi", strlen("Martedi")+1); // Tuesday
                        }
                        
                        if (weekday_text[0] == 'W')
                        {
                                memcpy(&weekday_text, "Mercoledi", strlen("Mercoledi")+1); // Wednesday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
                        {
                                memcpy(&weekday_text, "Giovedi", strlen("Giovedi")+1); // Thursday
                        }
                        
                        if (weekday_text[0] == 'F')
                        {
                                memcpy(&weekday_text, "Venerdi", strlen("Venerdi")+1); // Friday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
                        {
                                memcpy(&weekday_text, "Sabato", strlen("Sabato")+1); // Saturday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Domenica", strlen("Domenica")+1); // Sunday
                        }
                        
        } //END OF ITALIAN                        
        else if (language[0] == 'G'){ //GERMAN
			translate_sp= true;
                        if (month_text[0] == 'J' && month_text[1] == 'a')
                        {
                                memcpy(&month_text, "  .Januar", strlen("  .Januar")+1); // January
                        }
                        
                        if (month_text[0] == 'F' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "  .Februar", strlen("  .Februar")+1); // Febrary
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'r')
                        {
                                memcpy(&month_text, "  .März", strlen("  .März")+1); // March
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'p')
                        {
                                memcpy(&month_text, "  .April", strlen("  .April")+1); // April
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'y')
                        {
                                memcpy(&month_text, "  .Mai", strlen("  .Mai")+1); // May
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'n')
                        {
                                memcpy(&month_text, "  .Juni", strlen("  .Juni")+1); // June
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'l')
                        {
                                memcpy(&month_text, "  .Juli", strlen("  .Juli")+1); // July
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'u')
                        {
                                memcpy(&month_text, "  .August", strlen("  .August")+1); // August
                        }
                        
                        if (month_text[0] == 'S' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "  .September", strlen("  .September")+1); // September
                        }
                        
                        if (month_text[0] == 'O' && month_text[1] == 'c')
                        {
                                memcpy(&month_text, "  .Oktober", strlen("  .Oktober")+1); // October
                        }
                        
                        if (month_text[0] == 'N' && month_text[1] == 'o')
                        {
                                memcpy(&month_text, "  .November", strlen("  .November")+1); // November
                        }
                        
                        if (month_text[0] == 'D' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "  .Dezember", strlen("  .Dezember")+1); // December
                        }
                        
                        // Primitive hack to translate the day of week to another language
                        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
                        // Supported characters: A-Z, a-z, 0-9
                        if (weekday_text[0] == 'M')
                        {
                                memcpy(&weekday_text, "Montag", strlen("Montag")+1); // Monday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Dienstag", strlen("Dienstag")+1); // Tuesday
                        }
                        
                        if (weekday_text[0] == 'W')
                        {
                                memcpy(&weekday_text, "Mittwoch", strlen("Mittwoch")+1); // Wednesday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
                        {
                                memcpy(&weekday_text, "Donnerstag", strlen("Donnerstag")+1); // Thursday
                        }
                        
                        if (weekday_text[0] == 'F')
                        {
                                memcpy(&weekday_text, "Freitag", strlen("Freitag")+1); // Friday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
                        {
                                memcpy(&weekday_text, "Samstag", strlen("Samstag")+1); // Saturday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Sonntag", strlen("Sonntag")+1); // Sunday
                        }
                        
        } //END OF GERMAN                        
                else if (language[0] == 'C'){ //CZECH
					translate_sp= true;
                        if (month_text[0] == 'J' && month_text[1] == 'a')
                        {
                                memcpy(&month_text, "Leden ", strlen("Leden ")+1); // January
                        }
                        
                        if (month_text[0] == 'F' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "Únor ", strlen("Únor ")+1); // Febrary
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'r')
                        {
                                memcpy(&month_text, "Brezen ", strlen("Brezen ")+1); // March
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'p')
                        {
                                memcpy(&month_text, "Duben ", strlen("Duben ")+1); // April
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'y')
                        {
                                memcpy(&month_text, "Květen ", strlen("Květen ")+1); // May
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'n')
                        {
                                memcpy(&month_text, "Červen ", strlen("Červen ")+1); // June
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'l')
                        {
                                memcpy(&month_text, "Červenec ", strlen("Červenec ")+1); // July
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'u')
                        {
                                memcpy(&month_text, "Srpen ", strlen("Srpen ")+1); // August
                        }
                        
                        if (month_text[0] == 'S' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "Zárí ", strlen("Zárí ")+1); // September
                        }
                        
                        if (month_text[0] == 'O' && month_text[1] == 'c')
                        {
                                memcpy(&month_text, "Ríjen ", strlen("Ríjen ")+1); // October
                        }
                        
                        if (month_text[0] == 'N' && month_text[1] == 'o')
                        {
                                memcpy(&month_text, "Listopad ", strlen("Listopad ")+1); // November
                        }
                        
                        if (month_text[0] == 'D' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "Prosinec ", strlen("Prosinec ")+1); // December
                        }
                        
                        // Primitive hack to translate the day of week to another language
                        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
                        // Supported characters: A-Z, a-z, 0-9
                        if (weekday_text[0] == 'M')
                        {
                                memcpy(&weekday_text, "Pondělí", strlen("Pondělí")+1); // Monday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Úterý", strlen("Úterý")+1); // Tuesday
                        }
                        
                        if (weekday_text[0] == 'W')
                        {
                                memcpy(&weekday_text, "Streda", strlen("Streda")+1); // Wednesday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
                        {
                                memcpy(&weekday_text, "Čtvrtek", strlen("Čtvrtek")+1); // Thursday
                        }
                        
                        if (weekday_text[0] == 'F')
                        {
                                memcpy(&weekday_text, "Pátek", strlen("Pátek")+1); // Friday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
                        {
                                memcpy(&weekday_text, "Sobota", strlen("Sobota")+1); // Saturday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Neděle", strlen("Neděle")+1); // Sunday
                        }
                        
        } //END OF CZECH     
	 	else if (language[0] == 'F'){ //FRENCH
			translate_sp= true;
                        if (month_text[0] == 'J' && month_text[1] == 'a')
                        {
                                memcpy(&month_text, "   janvier", strlen("   janvier")+1); // January
                        }
                        
                        if (month_text[0] == 'F' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   février", strlen("   février")+1); // Febrary
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'r')
                        {
                                memcpy(&month_text, "   mars", strlen("   mars")+1); // March
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'p')
                        {
                                memcpy(&month_text, "   avril", strlen("   avril")+1); // April
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'y')
                        {
                                memcpy(&month_text, "   mai", strlen("   mai")+1); // May
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'n')
                        {
                                memcpy(&month_text, "   juin", strlen("   juin")+1); // June
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'l')
                        {
                                memcpy(&month_text, "   juillet", strlen("   juillet")+1); // July
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'u')
                        {
                                memcpy(&month_text, "   août", strlen("   août")+1); // August
                        }
                        
                        if (month_text[0] == 'S' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   septembre", strlen("   septembre")+1); // September
                        }
                        
                        if (month_text[0] == 'O' && month_text[1] == 'c')
                        {
                                memcpy(&month_text, "   octobre", strlen("   octobre")+1); // October
                        }
                        
                        if (month_text[0] == 'N' && month_text[1] == 'o')
                        {
                                memcpy(&month_text, "   novembre", strlen("   novembre")+1); // November
                        }
                        
                        if (month_text[0] == 'D' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   décembre", strlen("   décembre")+1); // December
                        }
                        
                        // Primitive hack to translate the day of week to another language
                        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
                        // Supported characters: A-Z, a-z, 0-9
                        if (weekday_text[0] == 'M')
                        {
                                memcpy(&weekday_text, "Lundi", strlen("Lundi")+1); // Monday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Mardi", strlen("Mardi")+1); // Tuesday
                        }
                        
                        if (weekday_text[0] == 'W')
                        {
                                memcpy(&weekday_text, "Mercredi", strlen("Mercredi")+1); // Wednesday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
                        {
                                memcpy(&weekday_text, "Jeudi", strlen("Jeudi")+1); // Thursday
                        }
                        
                        if (weekday_text[0] == 'F')
                        {
                                memcpy(&weekday_text, "Vendredi", strlen("Vendredi")+1); // Friday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
                        {
                                memcpy(&weekday_text, "Samedi", strlen("Samedi")+1); // Saturday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Dimanche", strlen("Dimanche")+1); // Sunday
                        }
                        
        } //END OF FRENCH        
		 	else if (language[0] == 'P'){ //PORTUGUESE
				translate_sp= true;
				
                        if (month_text[0] == 'J' && month_text[1] == 'a')
                        {
                                memcpy(&month_text, "   Janeiro", strlen("   Janeiro")+1); // January
                        }
                        
                        if (month_text[0] == 'F' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   Fevereiro", strlen("   Fevereiro")+1); // Febrary
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'r')
                        {
                                memcpy(&month_text, "   Março", strlen("   Março")+1); // March
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'p')
                        {
                                memcpy(&month_text, "   Abril", strlen("   Abril")+1); // April
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'y')
                        {
                                memcpy(&month_text, "   Maio", strlen("   Maio")+1); // May
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'n')
                        {
                                memcpy(&month_text, "   Junho", strlen("   Junho")+1); // June
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'l')
                        {
                                memcpy(&month_text, "   Julho", strlen("   Julho")+1); // July
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'u')
                        {
                                memcpy(&month_text, "   Agosto", strlen("   Agosto")+1); // August
                        }
                        
                        if (month_text[0] == 'S' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   Setembro", strlen("   Setembro")+1); // September
                        }
                        
                        if (month_text[0] == 'O' && month_text[1] == 'c')
                        {
                                memcpy(&month_text, "   Outubro", strlen("   Outubro")+1); // October
                        }
                        
                        if (month_text[0] == 'N' && month_text[1] == 'o')
                        {
                                memcpy(&month_text, "   Novembro", strlen("   Novembro")+1); // November
                        }
                        
                        if (month_text[0] == 'D' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   Dezembro", strlen("   Dezembro")+1); // December
                        }
                        
                        // Primitive hack to translate the day of week to another language
                        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
                        // Supported characters: A-Z, a-z, 0-9
                        if (weekday_text[0] == 'M')
                        {
                                memcpy(&weekday_text, "Segunda", strlen("Segunda")+1); // Monday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Terça", strlen("Terça")+1); // Tuesday
                        }
                        
                        if (weekday_text[0] == 'W')
                        {
                                memcpy(&weekday_text, "Quarta", strlen("Quarta")+1); // Wednesday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
                        {
                                memcpy(&weekday_text, "Quinta", strlen("Quinta")+1); // Thursday
                        }
                        
                        if (weekday_text[0] == 'F')
                        {
                                memcpy(&weekday_text, "Sexta", strlen("Sexta")+1); // Friday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
                        {
                                memcpy(&weekday_text, "Sábado", strlen("Sábado")+1); // Saturday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Domingo", strlen("Domingo")+1); // Sunday
                        }
                        
        } //END OF PORTUGUESE
			 	else if (language[0] == 'X'){ //FINNISH
					translate_sp= true;
					
                        if (month_text[0] == 'J' && month_text[1] == 'a')
                        {
                                memcpy(&month_text, "  . Tammikuu", strlen("  . Tammikuu")+1); // January
                        }
                        
                        if (month_text[0] == 'F' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "  . Helmikuu", strlen("  . Helmikuu")+1); // Febrary
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'r')
                        {
                                memcpy(&month_text, "  . Maaliskuu", strlen("  . Maaliskuu")+1); // March
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'p')
                        {
                                memcpy(&month_text, "  . Huhtikuu", strlen("  . Huhtikuu")+1); // April
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'y')
                        {
                                memcpy(&month_text, "  . Toukokuu", strlen("  . Toukokuu")+1); // May
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'n')
                        {
                                memcpy(&month_text, "  . Kesäkuu", strlen("  . Kesäkuu")+1); // June
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'l')
                        {
                                memcpy(&month_text, "  . Heinäkuu", strlen("  . Heinäkuu")+1); // July
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'u')
                        {
                                memcpy(&month_text, "  . Elokuu", strlen("  . Elokuu")+1); // August
                        }
                        
                        if (month_text[0] == 'S' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "  . Syyskuu", strlen("  . Syyskuu")+1); // September
                        }
                        
                        if (month_text[0] == 'O' && month_text[1] == 'c')
                        {
                                memcpy(&month_text, "  . Lokakuu", strlen("  . Lokakuu")+1); // October
                        }
                        
                        if (month_text[0] == 'N' && month_text[1] == 'o')
                        {
                                memcpy(&month_text, "  . Marraskuu", strlen("  . Marraskuu")+1); // November
                        }
                        
                        if (month_text[0] == 'D' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "  . Joulukuu", strlen("  . Joulukuu")+1); // December
                        }
                        
                        // Primitive hack to translate the day of week to another language
                        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
                        // Supported characters: A-Z, a-z, 0-9
                        if (weekday_text[0] == 'M')
                        {
                                memcpy(&weekday_text, "Maanantai", strlen("Maanantai")+1); // Monday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Tiistai", strlen("Tiistai")+1); // Tuesday
                        }
                        
                        if (weekday_text[0] == 'W')
                        {
                                memcpy(&weekday_text, "Keskiviikko", strlen("Keskiviikko")+1); // Wednesday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
                        {
                                memcpy(&weekday_text, "Torstai", strlen("Torstai")+1); // Thursday
                        }
                        
                        if (weekday_text[0] == 'F')
                        {
                                memcpy(&weekday_text, "Perjantai", strlen("Perjantai")+1); // Friday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
                        {
                                memcpy(&weekday_text, "Lauantai", strlen("Lauantai")+1); // Saturday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Sunnuntai", strlen("Sunnuntai")+1); // Sunday
                        }
                        
        } //END OF FINNISH
	
		else if (language[0] == 'D'){ //DUTCH
						translate_sp= true;
							
                        if (month_text[0] == 'J' && month_text[1] == 'a')
                        {
                                memcpy(&month_text, "   Januari", strlen("   Januari")+1); // January
                        }
                        
                        if (month_text[0] == 'F' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   Februari", strlen("   Februari")+1); // Febrary
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'r')
                        {
                                memcpy(&month_text, "   Maart", strlen("   Maart")+1); // March
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'p')
                        {
                                memcpy(&month_text, "   April", strlen("   April")+1); // April
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'y')
                        {
                                memcpy(&month_text, "   Mei", strlen("   Mei")+1); // May
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'n')
                        {
                                memcpy(&month_text, "   Juni", strlen("   Juni")+1); // June
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'l')
                        {
                                memcpy(&month_text, "   Juli", strlen("   Juli")+1); // July
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'u')
                        {
                                memcpy(&month_text, "   Augustus", strlen("   Augustus")+1); // August
                        }
                        
                        if (month_text[0] == 'S' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   September", strlen("   September")+1); // September
                        }
                        
                        if (month_text[0] == 'O' && month_text[1] == 'c')
                        {
                                memcpy(&month_text, "   Oktober", strlen("   Oktober")+1); // October
                        }
                        
                        if (month_text[0] == 'N' && month_text[1] == 'o')
                        {
                                memcpy(&month_text, "   November", strlen("   November")+1); // November
                        }
                        
                        if (month_text[0] == 'D' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   December", strlen("   December")+1); // December
                        }
                        
                        // Primitive hack to translate the day of week to another language
                        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
                        // Supported characters: A-Z, a-z, 0-9
                        if (weekday_text[0] == 'M')
                        {
                                memcpy(&weekday_text, "Maandag", strlen("Maandag")+1); // Monday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Dinsdag", strlen("Dinsdag")+1); // Tuesday
                        }
                        
                        if (weekday_text[0] == 'W')
                        {
                                memcpy(&weekday_text, "Woensdag", strlen("Woensdag")+1); // Wednesday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
                        {
                                memcpy(&weekday_text, "Donderdag", strlen("Donderdag")+1); // Thursday
                        }
                        
                        if (weekday_text[0] == 'F')
                        {
                                memcpy(&weekday_text, "Vrijdag", strlen("Vrijdag")+1); // Friday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
                        {
                                memcpy(&weekday_text, "Zaterdag", strlen("Zaterdag")+1); // Saturday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Zondag", strlen("Zondag")+1); // Sunday
                        }
                        
        } //END OF DUTCH
					else if (language[0] == '1'){ //POLISH
						translate_sp= true;
						
                        if (month_text[0] == 'J' && month_text[1] == 'a')
                        {
                                memcpy(&month_text, "   stycznia", strlen("   stycznia")+1); // January
                        }
                        
                        if (month_text[0] == 'F' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   lutego", strlen("   lutego")+1); // Febrary
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'r')
                        {
                                memcpy(&month_text, "   marca", strlen("   marca")+1); // March
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'p')
                        {
                                memcpy(&month_text, "   kwietnia", strlen("   kwietnia")+1); // April
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'y')
                        {
                                memcpy(&month_text, "   maja", strlen("   maja")+1); // May
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'n')
                        {
                                memcpy(&month_text, "   czerwca", strlen("   czerwca")+1); // June
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'l')
                        {
                                memcpy(&month_text, "   lipca", strlen("   lipca")+1); // July
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'u')
                        {
                                memcpy(&month_text, "   sierpnia", strlen("   sierpnia")+1); // August
                        }
                        
                        if (month_text[0] == 'S' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   wrzesnia", strlen("   wrzesnia")+1); // September
                        }
                        
                        if (month_text[0] == 'O' && month_text[1] == 'c')
                        {
                                memcpy(&month_text, "   pazdziernika", strlen("   pazdziernika")+1); // October
                        }
                        
                        if (month_text[0] == 'N' && month_text[1] == 'o')
                        {
                                memcpy(&month_text, "   listopada", strlen("   listopada")+1); // November
                        }
                        
                        if (month_text[0] == 'D' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   grudnia", strlen("   grudnia")+1); // December
                        }
                        
                        // Primitive hack to translate the day of week to another language
                        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
                        // Supported characters: A-Z, a-z, 0-9
                        if (weekday_text[0] == 'M')
                        {
                                memcpy(&weekday_text, "Poniedzialek", strlen("Poniedzialek")+1); // Monday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Wtorek", strlen("Wtorek")+1); // Tuesday
                        }
                        
                        if (weekday_text[0] == 'W')
                        {
                                memcpy(&weekday_text, "Sroda", strlen("Sroda")+1); // Wednesday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
                        {
                                memcpy(&weekday_text, "Czwartek", strlen("Czwartek")+1); // Thursday
                        }
                        
                        if (weekday_text[0] == 'F')
                        {
                                memcpy(&weekday_text, "Piątek", strlen("Piątek")+1); // Friday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
                        {
                                memcpy(&weekday_text, "Sobota", strlen("Sobota")+1); // Saturday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Niedziela", strlen("Niedziela")+1); // Sunday
                        }
                        
        } //END OF POLISH
				else if (language[0] == 'S'){ //SWEDISH
						translate_sp= true;
					
                        if (month_text[0] == 'J' && month_text[1] == 'a')
                        {
                                memcpy(&month_text, "   Januari", strlen("   Januari")+1); // January
                        }
                        
                        if (month_text[0] == 'F' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   Februari", strlen("   Februari")+1); // Febrary
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'r')
                        {
                                memcpy(&month_text, "   Mars", strlen("   Mars")+1); // March
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'p')
                        {
                                memcpy(&month_text, "   April", strlen("   April")+1); // April
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'y')
                        {
                                memcpy(&month_text, "   Maj", strlen("   Maj")+1); // May
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'n')
                        {
                                memcpy(&month_text, "   Juni", strlen("   Juni")+1); // June
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'l')
                        {
                                memcpy(&month_text, "   Juli", strlen("   Juli")+1); // July
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'u')
                        {
                                memcpy(&month_text, "   Augusti", strlen("   Augusti")+1); // August
                        }
                        
                        if (month_text[0] == 'S' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   September", strlen("   September")+1); // September
                        }
                        
                        if (month_text[0] == 'O' && month_text[1] == 'c')
                        {
                                memcpy(&month_text, "   Oktober", strlen("   Oktober")+1); // October
                        }
                        
                        if (month_text[0] == 'N' && month_text[1] == 'o')
                        {
                                memcpy(&month_text, "   November", strlen("   November")+1); // November
                        }
                        
                        if (month_text[0] == 'D' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   December", strlen("   December")+1); // December
                        }
                        
                        // Primitive hack to translate the day of week to another language
                        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
                        // Supported characters: A-Z, a-z, 0-9
                        if (weekday_text[0] == 'M')
                        {
                                memcpy(&weekday_text, "Måndag", strlen("Måndag")+1); // Monday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Tisdag", strlen("Tisdag")+1); // Tuesday
                        }
                        
                        if (weekday_text[0] == 'W')
                        {
                                memcpy(&weekday_text, "Onsdag", strlen("Onsdag")+1); // Wednesday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
                        {
                                memcpy(&weekday_text, "Torsdag", strlen("Torsdag")+1); // Thursday
                        }
                        
                        if (weekday_text[0] == 'F')
                        {
                                memcpy(&weekday_text, "Fredag", strlen("Fredag")+1); // Friday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
                        {
                                memcpy(&weekday_text, "Lördag", strlen("Lördag")+1); // Saturday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Söndag ", strlen("Söndag ")+1); // Sunday
                        }
                        
        } //END OF SWEDISH
	
				else if (language[0] == '2'){ //DANISH
						translate_sp= true;
					
                        if (month_text[0] == 'J' && month_text[1] == 'a')
                        {
                                memcpy(&month_text, "   . Januar", strlen("   . Januar")+1); // January
                        }
                        
                        if (month_text[0] == 'F' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   . Februar", strlen("   . Februar")+1); // Febrary
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'r')
                        {
                                memcpy(&month_text, "   . Marts", strlen("   . Marts")+1); // March
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'p')
                        {
                                memcpy(&month_text, "   . April", strlen("   . April")+1); // April
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'y')
                        {
                                memcpy(&month_text, "   . Maj", strlen("   . Maj")+1); // May
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'n')
                        {
                                memcpy(&month_text, "   . Juni", strlen("   . Juni")+1); // June
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'l')
                        {
                                memcpy(&month_text, "   . Juli", strlen("   . Juli")+1); // July
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'u')
                        {
                                memcpy(&month_text, "   . August", strlen("   . August")+1); // August
                        }
                        
                        if (month_text[0] == 'S' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   . September", strlen("   . September")+1); // September
                        }
                        
                        if (month_text[0] == 'O' && month_text[1] == 'c')
                        {
                                memcpy(&month_text, "   . Oktober", strlen("   . Oktober")+1); // October
                        }
                        
                        if (month_text[0] == 'N' && month_text[1] == 'o')
                        {
                                memcpy(&month_text, "   . November", strlen("   . November")+1); // November
                        }
                        
                        if (month_text[0] == 'D' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   . December", strlen("   . December")+1); // December
                        }
                        
                        // Primitive hack to translate the day of week to another language
                        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
                        // Supported characters: A-Z, a-z, 0-9
                        if (weekday_text[0] == 'M')
                        {
                                memcpy(&weekday_text, "Mandag", strlen("Mandag")+1); // Monday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Tirsdag", strlen("Tirsdag")+1); // Tuesday
                        }
                        
                        if (weekday_text[0] == 'W')
                        {
                                memcpy(&weekday_text, "Onsdag", strlen("Onsdag")+1); // Wednesday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
                        {
                                memcpy(&weekday_text, "Torsdag", strlen("Torsdag")+1); // Thursday
                        }
                        
                        if (weekday_text[0] == 'F')
                        {
                                memcpy(&weekday_text, "Fredag", strlen("Fredag")+1); // Friday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
                        {
                                memcpy(&weekday_text, "Lørdag", strlen("Lørdag")+1); // Saturday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Søndag ", strlen("Søndag ")+1); // Sunday
                        }
                        
        } //END OF DANISH
					else if (language[0] == '3'){ //CATALAN
						translate_sp= true;
					
                        if (month_text[0] == 'J' && month_text[1] == 'a')
                        {
                                memcpy(&month_text, "   Gener", strlen("   Gener")+1); // January
                        }
                        
                        if (month_text[0] == 'F' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   Febrer", strlen("   Febrer")+1); // Febrary
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'r')
                        {
                                memcpy(&month_text, "   Març", strlen("   Març")+1); // March
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'p')
                        {
                                memcpy(&month_text, "   Abril", strlen("   Abril")+1); // April
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'y')
                        {
                                memcpy(&month_text, "   Maig", strlen("   Maig")+1); // May
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'n')
                        {
                                memcpy(&month_text, "   Juny", strlen("   Juny")+1); // June
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'l')
                        {
                                memcpy(&month_text, "   Juliol", strlen("   Juliol")+1); // July
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'u')
                        {
                                memcpy(&month_text, "   Agost", strlen("   Agost")+1); // August
                        }
                        
                        if (month_text[0] == 'S' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   Setembre", strlen("   Setembre")+1); // September
                        }
                        
                        if (month_text[0] == 'O' && month_text[1] == 'c')
                        {
                                memcpy(&month_text, "   Octubre", strlen("   Octubre")+1); // October
                        }
                        
                        if (month_text[0] == 'N' && month_text[1] == 'o')
                        {
                                memcpy(&month_text, "   Novembre", strlen("   Novembre")+1); // November
                        }
                        
                        if (month_text[0] == 'D' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "   Desembre", strlen("   Desembre")+1); // December
                        }
                        
                        // Primitive hack to translate the day of week to another language
                        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
                        // Supported characters: A-Z, a-z, 0-9
                        if (weekday_text[0] == 'M')
                        {
                                memcpy(&weekday_text, "Dilluns", strlen("Dilluns")+1); // Monday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Dimarts", strlen("Dimarts")+1); // Tuesday
                        }
                        
                        if (weekday_text[0] == 'W')
                        {
                                memcpy(&weekday_text, "Dimecres", strlen("Dimecres")+1); // Wednesday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
                        {
                                memcpy(&weekday_text, "Dijous", strlen("Dijous")+1); // Thursday
                        }
                        
                        if (weekday_text[0] == 'F')
                        {
                                memcpy(&weekday_text, "Divendres", strlen("Divendres")+1); // Friday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
                        {
                                memcpy(&weekday_text, "Dissabte", strlen("Dissabte")+1); // Saturday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Diumenge ", strlen("Diumenge ")+1); // Sunday
                        }
                        
        } //END OF CATALAN
	            else if (language[0] == 'H'){ //HUNGARIAN
					translate_sp= true;
                        if (month_text[0] == 'J' && month_text[1] == 'a')
                        {
                                memcpy(&month_text, "január ", strlen("január ")+1); // January
                        }
                        
                        if (month_text[0] == 'F' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "február ", strlen("február ")+1); // Febrary
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'r')
                        {
                                memcpy(&month_text, "március ", strlen("március ")+1); // March
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'p')
                        {
                                memcpy(&month_text, "április ", strlen("április ")+1); // April
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'y')
                        {
                                memcpy(&month_text, "május ", strlen("május ")+1); // May
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'n')
                        {
                                memcpy(&month_text, "június ", strlen("június ")+1); // June
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'l')
                        {
                                memcpy(&month_text, "július ", strlen("július ")+1); // July
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'u')
                        {
                                memcpy(&month_text, "augusztus ", strlen("augusztus ")+1); // August
                        }
                        
                        if (month_text[0] == 'S' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "szeptember ", strlen("szeptember ")+1); // September
                        }
                        
                        if (month_text[0] == 'O' && month_text[1] == 'c')
                        {
                                memcpy(&month_text, "október ", strlen("október ")+1); // October
                        }
                        
                        if (month_text[0] == 'N' && month_text[1] == 'o')
                        {
                                memcpy(&month_text, "november ", strlen("november ")+1); // November
                        }
                        
                        if (month_text[0] == 'D' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "december ", strlen("december ")+1); // December
                        }
                        
                        // Primitive hack to translate the day of week to another language
                        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
                        // Supported characters: A-Z, a-z, 0-9
                        if (weekday_text[0] == 'M')
                        {
                                memcpy(&weekday_text, "Hétfo", strlen("Hétfo")+1); // Monday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Kedd", strlen("Kedd")+1); // Tuesday
                        }
                        
                        if (weekday_text[0] == 'W')
                        {
                                memcpy(&weekday_text, "Szerda", strlen("Szerda")+1); // Wednesday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
                        {
                                memcpy(&weekday_text, "Csütörtök", strlen("Csütörtök")+1); // Thursday
                        }
                        
                        if (weekday_text[0] == 'F')
                        {
                                memcpy(&weekday_text, "Péntek", strlen("Péntek")+1); // Friday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
                        {
                                memcpy(&weekday_text, "Szombat", strlen("Szombat")+1); // Saturday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Vasárnap", strlen("Vasárnap")+1); // Sunday
                        }
                        
        } //END OF HUNGARIAN  
		else if (language[0] == 'N'){ //NORWEGIAN
						translate_sp= true;
					
                        if (month_text[0] == 'J' && month_text[1] == 'a')
                        {
                                memcpy(&month_text, "  . januar", strlen("  . januar")+1); // January
                        }
                        
                        if (month_text[0] == 'F' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "  . februar", strlen("  . februar")+1); // Febrary
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'r')
                        {
                                memcpy(&month_text, "  . mars", strlen("  . mars")+1); // March
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'p')
                        {
                                memcpy(&month_text, "  . april", strlen("  . april")+1); // April
                        }
                        
                        if (month_text[0] == 'M' && month_text[2] == 'y')
                        {
                                memcpy(&month_text, "  . mai", strlen("  . mai")+1); // May
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'n')
                        {
                                memcpy(&month_text, "  . juni", strlen("  . juni")+1); // June
                        }
                        
                        if (month_text[0] == 'J' && month_text[2] == 'l')
                        {
                                memcpy(&month_text, "  . juli", strlen("  . juli")+1); // July
                        }
                        
                        if (month_text[0] == 'A' && month_text[1] == 'u')
                        {
                                memcpy(&month_text, "  . august", strlen("  . august")+1); // August
                        }
                        
                        if (month_text[0] == 'S' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "  . september", strlen("  . september")+1); // September
                        }
                        
                        if (month_text[0] == 'O' && month_text[1] == 'c')
                        {
                                memcpy(&month_text, "  . oktober", strlen("  . oktober")+1); // October
                        }
                        
                        if (month_text[0] == 'N' && month_text[1] == 'o')
                        {
                                memcpy(&month_text, "  . november", strlen("  . november")+1); // November
                        }
                        
                        if (month_text[0] == 'D' && month_text[1] == 'e')
                        {
                                memcpy(&month_text, "  . desember", strlen("  . desember")+1); // December
                        }
                        
                        // Primitive hack to translate the day of week to another language
                        // Needs to be exactly 3 characters, e.g. "Mon" or "Mo "
                        // Supported characters: A-Z, a-z, 0-9
                        if (weekday_text[0] == 'M')
                        {
                                memcpy(&weekday_text, "Mandag", strlen("Mandag")+1); // Monday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Tirsdag", strlen("Tirsdag")+1); // Tuesday
                        }
                        
                        if (weekday_text[0] == 'W')
                        {
                                memcpy(&weekday_text, "Onsdag", strlen("Onsdag")+1); // Wednesday
                        }
                        
                        if (weekday_text[0] == 'T' && weekday_text[1] == 'h')
                        {
                                memcpy(&weekday_text, "Torsdag", strlen("Torsdag")+1); // Thursday
                        }
                        
                        if (weekday_text[0] == 'F')
                        {
                                memcpy(&weekday_text, "Fredag", strlen("Fredag")+1); // Friday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'a')
                        {
                                memcpy(&weekday_text, "Lørdag", strlen("Lørdag")+1); // Saturday
                        }
                        
                        if (weekday_text[0] == 'S' && weekday_text[1] == 'u')
                        {
                                memcpy(&weekday_text, "Søndag ", strlen("Søndag ")+1); // Sunday
                        }
                        
        } //END OF NORWEGIAN

	else{translate_sp=false;} //If the language is not in the list of translations then keep english.
} //END OF Translate_Date

//**************************//
//** Get the current date **//
//**************************//
void getDate()
{
	
	//Get the date
	time_t actualPtr = time(NULL);
	struct tm *tz1Ptr = gmtime(&actualPtr);
	
	//Get the Weekday
	strftime(weekday_text,sizeof(weekday_text),"%A",tz1Ptr);
	//Get the Month + Day (English format)
	strftime(month_text,sizeof(month_text),"%B %e",tz1Ptr);
	//Get the Day + Month (Spanish format)
	strftime(day_month,sizeof(day_month),"%e %B",tz1Ptr);
	
	
	if(language[0] != '0'){
		//Get the Month
		strftime(month_text,sizeof(month_text),"%B",tz1Ptr);
		//Get the day
		strftime(day_text,sizeof(day_text),"%e",tz1Ptr);
		//Translate to Spanish
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
	
	
	text_layer_set_text(date_layer, month_text);
	text_layer_set_text(Weekday_Layer, weekday_text); //Update the weekday layer    
	
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
	  	  memcpy(&language, new_tuple->value->cstring, strlen(new_tuple->value->cstring));
		  persist_write_bool(language_key, new_tuple->value->cstring);
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
				TupletCString(language_key, "0"),
				TupletInteger(VIBES_KEY, persist_read_bool(VIBES_KEY)),
                }; //TUPLET INITIAL VALUES
        
                 app_sync_init(&sync, sync_buffer, sizeof(sync_buffer), initial_values,
                ARRAY_LENGTH(initial_values), sync_tuple_changed_callback,
                NULL, NULL);
  
		//load persistent storage options
		color_inverted = persist_read_bool(INVERT_COLOR_KEY);
		blnvibes = persist_read_bool(VIBES_KEY);
		persist_read_string(language_key, language, sizeof(language));
	
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
        
        //if (BT_image){gbitmap_destroy(BT_image);}
        //if (Batt_image){gbitmap_destroy(Batt_image);}
        //if (weather_image){gbitmap_destroy(weather_image);}
        
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



