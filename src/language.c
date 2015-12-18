#include <pebble.h>
#include <language.h>

char* translateDay(int weekday, int language, bool pblRound){

	static char translatedWeekday[12];
	int arrayPosition;
	
	//correct the tm->wday position. Sunday must be changed from 0 to 7 (so we start the week on Monday)
	if (weekday == 0){weekday = 7;}
	
	memset(&translatedWeekday[0], 0, sizeof(translatedWeekday));
	
	arrayPosition = (language*7)+weekday;
	
	if (pblRound) {
		#ifdef PBL_ROUND
			memcpy(&translatedWeekday, short_weekdays[arrayPosition], strlen(short_weekdays[arrayPosition]));
		#endif
	}
	else {memcpy(&translatedWeekday, WEEKDAYS[arrayPosition], strlen(WEEKDAYS[arrayPosition]));}
	
	
	return translatedWeekday;
}

char* translateMonth(int month, int language){

	static char translatedMonth[13];
	int arrayPosition;
	
	memset(&translatedMonth[0], 0, sizeof(translatedMonth));

	//get the right position within the months array based on the month number and language
	arrayPosition = (language*12)+month;
	//get the translated month
	memcpy(&translatedMonth, MONTHS[arrayPosition], strlen(MONTHS[arrayPosition])+1);
	return translatedMonth;
}