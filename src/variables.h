#pragma once
#include <pebble.h>

/********************/
/* COMMON VARIABLES */
/********************/

    //Font Resources
	ResHandle res_d;
  	ResHandle res_t;
	ResHandle res_temp;
	ResHandle res_u;
	ResHandle res_russian;
	ResHandle res_d_rus_forecast; //for russian forecast
	ResHandle res_asian;

	GFont font_date; // Font for date
	GFont font_time; // Font for time
	GFont font_temperature;
	GFont font_update;
	GFont font_russian;
	GFont font_russian_date_forecast; //Font for date in russian
	GFont font_asian;
	

	//Date & Time
	static char weekday_text[] = "XXXXXXXXXXXX";
	static char month_text[] = "XXXXXXXXXXXXXX";
	static char time_text[] = "00:00";
	static char seconds_text[] = "00";
	static char ampm_text[] = "   ";
	int intLanguage = 100; //Defaults to English U.S.
	int intLangCounter = 22; 
	int intWDay = 0;
	int intDay = 0;
	int intMonth = 0;
	char day_month[13];

	//Miscellaneous
	bool blnHourlyVibe = false;
	int TapCount = 0;
	bool blnBacklight = false;
	bool blnseconds = false;

	//Weather
	static char temp[]="     ";
	int ICON_CODE = 16;
	static char city[100]= "YWeather v3.3";
	static char last_update[]="00:00 ";
	static AppTimer *weatherTimer;
	static AppTimer *forecastTimer;
	uint32_t timeout_ms = 1800000; //30min (1min = 60000)
	bool blnForecast = false;
	uint32_t ESDuration_ms = 5000; //5sec (1min = 60000)


	//Forecast
	static char high[]="     ";
	static char low[]="    ";
	static char sunrise[]="     ";
	static char sunset[]="     ";
	static char wind[]="     ";
	static int wdirection;
	static char strwdirection[100];
	static char city[100];
	static char PoP[] = "    ";

	//3-day forecast
	bool bln3daysForecast = false;

	#ifdef PBL_ROUND
		static char weekday1_text[] = "XXX";
		static char weekday2_text[] = "XXX";
		static char weekday3_text[] = "XXX";
	#else
		static char weekday1_text[] = "XXXXXXXXXXXXX";
		static char weekday2_text[] = "XXXXXXXXXXXXX";
		static char weekday3_text[] = "XXXXXXXXXXXXX";
	#endif

	static char day1H[] = "      ";
	static char day1L[] = "      ";
	static char day2H[] = "      ";
	static char day2L[] = "      ";
	static char day3H[] = "      ";
	static char day3L[] = "      ";

	int code1;
	int code2;
	int code3;