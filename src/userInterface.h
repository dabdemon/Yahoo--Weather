#pragma once
#include <pebble.h>

/*************************/
/* DEFINE USER INTERFACE */
/*************************/

	//Windows
	Window *mainWindow;

	//DATE AND TIME

	#define WEEKDAY_FRAME 			PBL_IF_ROUND_ELSE(GRect(30, 20, 120, 168-145),GRect(5, 2, 110, 168-145))
	//#define BT_FRAME        		PBL_IF_ROUND_ELSE(GRect(20, 109, 140, 2),GRect(127, 13, 23, 168-146))
	#define BT_FRAME        		PBL_IF_ROUND_ELSE(GRect(20, 109, 140, 2),GRect(120, 3, 23, 23))
	#define TIME_FRAME      		PBL_IF_ROUND_ELSE(GRect(0, 48, 180, 168-16),GRect(0, 15, 144, 168-16))
	#define TIME_FRAME_ANIMATED     GRect(0, 20, 180, 168-16)
	#define DATE_FRAME      		PBL_IF_ROUND_ELSE(GRect(25, 35, 130, 168-62),GRect(1, 70, 139, 168-62))
	#define BATT_FRAME      		PBL_IF_ROUND_ELSE(GRect(1000, 1, 1000, 1),GRect(119, 8, 25, 10))

	TextLayer *date_layer;          //Layer for the date
	TextLayer *Time_Layer;          //Layer for the time
	TextLayer *Weekday_Layer;       //Layer for the weekday
	TextLayer *line;                //Layer for the bluetooth line on Chalk
	GBitmap *BT_image;				//Phone disconnection image handler
	BitmapLayer *BT_icon_layer;		//Layer for the BT connection
	TextLayer *Batt_Layer;          //Layer for the Battery Level (Rectangular watches)
	Layer *battery_layer;			//Layer for the Battery Level (Round watches)

	//Miscellaneous
	

	//WEATHER

	#define WEATHER_FRAME     	PBL_IF_ROUND_ELSE(GRect(110, 142, 20, 20),GRect(5, 90, 60, 60))
	#define TEMPERATURE_FRAME 	PBL_IF_ROUND_ELSE(GRect(0, 117, 128, 60),GRect(58, 95, 94, 60))
	#define LOCATION_FRAME		PBL_IF_ROUND_ELSE(GRect(0, 112, 180, 20),GRect(1, 148, 110, 20))
	#define LAST_UPDATE_FRAME 	PBL_IF_ROUND_ELSE(GRect(1000, 1, 1000, 1),GRect(110, 148, 34, 20))

	static GBitmap *weather_image;			//Bitmap for the Weather Icon	
    static BitmapLayer *weather_icon_layer; //Layer for the weather info	
	TextLayer *Temperature_Layer;			//Layer for the Temperature
	TextLayer * Location_Layer;				//Layer for the Location
	TextLayer *Last_Update;             	// Layer for the last update

	//FORECAST

	#define LOW_FRAME			PBL_IF_ROUND_ELSE((GRect(110, 90, 47, 168-108)),(GRect(100, 93, 47, 168-108))) 
	#define LOW_ICON_FRAME 		PBL_IF_ROUND_ELSE((GRect(101, 86, 26, 26)),(GRect(81, 92, 26, 26)))
	#define HIGH_FRAME 			PBL_IF_ROUND_ELSE((GRect(110, 113, 47, 168-108)),(GRect(100, 115, 47, 168-108)))
	#define HIGH_ICON_FRAME 	PBL_IF_ROUND_ELSE((GRect(101, 109, 26, 26)),(GRect(81, 115, 26, 26))) 
	#define SUNRISE_FRAME 		PBL_IF_ROUND_ELSE((GRect(50, 90, 50, 168-108)),(GRect(30, 95, 50, 168-108))) 
	#define SUNRISE_ICON_FRAME 	PBL_IF_ROUND_ELSE((GRect(21, 92, 26, 17)),(GRect(1, 98, 26, 17))) 
	#define SUNSET_FRAME 		PBL_IF_ROUND_ELSE((GRect(48, 113, 50, 168-108)),(GRect(28, 115, 50, 168-108))) 
	#define SUNSET_ICON_FRAME 	PBL_IF_ROUND_ELSE((GRect(21, 112, 26, 17)),(GRect(1, 118, 26, 17))) 
	#define WIND_FRAME 			PBL_IF_ROUND_ELSE((GRect(70, 135, 50, 168-108)),(GRect(30, 135, 50, 168-108))) 
	#define WIND_ICON_FRAME 	PBL_IF_ROUND_ELSE((GRect(40, 130, 26, 26)),(GRect(1, 138, 26, 26))) 
	#define WDIRECTION_FRAME 	PBL_IF_ROUND_ELSE((GRect(50, 155, 50, 168-108)),(GRect(30, 155, 50, 168-108))) 
	#define POP_FRAME 			PBL_IF_ROUND_ELSE((GRect(100, 135, 45, 168-108)),(GRect(100, 135, 45, 168-108))) 
	#define RAIN_ICON_FRAME 	PBL_IF_ROUND_ELSE((GRect(101, 130, 26, 26)),(GRect(81, 135, 26, 26))) 	
	
	TextLayer *High_Layer;        	//Layer for the High Temperature
	TextLayer *Low_Layer;        	//Layer for the Low Temperature
	TextLayer *Sunrise_Layer;       //Layer for the High Temperature
	TextLayer *Sunset_Layer;        //Layer for the Low Temperature
	TextLayer *Wind_Layer;        	//Layer for the Wind speed 
	TextLayer *WDirection_Layer;    //Layer for the Wind direction
	TextLayer *PoP_Layer;			//Layer for the Probability of Precipitation

 	 GBitmap *sunset_image;
     BitmapLayer *sunset_icon_layer; //Layer for the sunset info
	 GBitmap *sunrise_image;
     BitmapLayer *sunrise_icon_layer; //Layer for the sunrise info
	 GBitmap *high_image;
     BitmapLayer *high_icon_layer; //Layer for the high info
     GBitmap *low_image;
     BitmapLayer *low_icon_layer; //Layer for the low info
     GBitmap *wind_image;
	 BitmapLayer *wind_icon_layer; //Layer for the wind info
 	 GBitmap *rain_image;
     BitmapLayer *rain_icon_layer; //Layer for the wind info

	//3-DAY FORECAST


	#define FORECAST_DAY1_FRAME PBL_IF_ROUND_ELSE((GRect( 35, 90, 50, 23)),(GRect(5, 93, 92, 23))) 
	#define FORECAST_DAY2_FRAME PBL_IF_ROUND_ELSE((GRect( 79, 90, 50, 23)),(GRect(5, 114, 92, 23))) 
	#define FORECAST_DAY3_FRAME PBL_IF_ROUND_ELSE((GRect(117, 90, 50, 23)),(GRect(5, 135, 92, 23))) 	

	#define FORECAST_CODE1_FRAME PBL_IF_ROUND_ELSE((GRect( 40, 110, 22, 22)),(GRect(97, 93, 22, 22))) 
	#define FORECAST_CODE2_FRAME PBL_IF_ROUND_ELSE((GRect( 80, 110, 22, 22)),(GRect(97, 114, 22, 22))) 
	#define FORECAST_CODE3_FRAME PBL_IF_ROUND_ELSE((GRect(120, 110, 22, 22)),(GRect(97, 135, 22, 22))) 

	#define FORECAST_HIGH1_FRAME PBL_IF_ROUND_ELSE((GRect( 40, 140, 45, 60)),(GRect(100, 103, 45, 60))) 
	#define FORECAST_HIGH2_FRAME PBL_IF_ROUND_ELSE((GRect( 80, 140, 45, 60)),(GRect(100, 125, 45, 60))) 
	#define FORECAST_HIGH3_FRAME PBL_IF_ROUND_ELSE((GRect(120, 140, 45, 60)),(GRect(100, 145, 45, 60))) 

	#define FORECAST_LOW1_FRAME  PBL_IF_ROUND_ELSE((GRect( 40, 130, 45, 60)),(GRect(100, 93, 45, 60))) 
	#define FORECAST_LOW2_FRAME  PBL_IF_ROUND_ELSE((GRect( 80, 130, 45, 60)),(GRect(100, 115, 45, 60)))  
	#define FORECAST_LOW3_FRAME  PBL_IF_ROUND_ELSE((GRect(120, 130, 45, 60)),(GRect(100, 135, 45, 60))) 


	TextLayer *Day1_Layer;
	TextLayer *High1_Layer;
	TextLayer *Low1_Layer;
	TextLayer *Day2_Layer;
	TextLayer *High2_Layer;
	TextLayer *Low2_Layer;
	TextLayer *Day3_Layer;
	TextLayer *High3_Layer;
	TextLayer *Low3_Layer;

	static GBitmap *forecast1;
	static BitmapLayer *forecast1_layer;
	static GBitmap *forecast2;
	static BitmapLayer *forecast2_layer;
	static GBitmap *forecast3;
	static BitmapLayer *forecast3_layer;