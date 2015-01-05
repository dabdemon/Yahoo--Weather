#include <pebble.h>
#include "functions.h"

////////////////////
// DO NOT DISTURB //
////////////////////
	
bool DoNotDisturb(int Hour, int Minutes, int DNDStart_KEY, int DNDEnd_KEY){
	//Define the variables
	bool blnNextDay = 0;

	//Read the Hourly Vibe Quiet Hours setup
	int intDNDStart = persist_read_int(DNDStart_KEY);
	int intDNDEnd = persist_read_int(DNDEnd_KEY);
	
	//Determine if the DND End is the next day
	if(intDNDStart>intDNDEnd){blnNextDay = 1;}
	
	if (blnNextDay){
	//if the DND End is next day, DND period is when the Current Hour is greater than Start Hour
		if ((Hour>=intDNDStart)||(Hour<intDNDEnd)){return true; } //DND period
		else {return false;} //Not DND period
	}
	else{
	//if the DND End is the same day, DND period is when the Current Hour is between Start and End Hours
		if ((Hour>=intDNDStart)&&(Hour<intDNDEnd)){return true;} //DND period
		else {return false;} //Not DND period
	}
	
}


/*********************************************************/
/* Format Sunrise/Sunset time based on Pebble's settings */
/*********************************************************/
const char* formatSunset(char* strSunset){
	
	time_t actualPtr = time(NULL);
	static char formatedsunset[]="     ";
	int iHours;
	int iHours2;
	int iMinutes;
	int iMinutes2;
	
	//Split the sunset hour and minutes (assume sunset is always after noon)
	
	if (strSunset[1]==':'){
		
	
		//hours
		iHours = strSunset[0] - '0';
		//minutes
		iMinutes = strSunset[2] - '0';
		iMinutes2 = strSunset[3] - '0';
		
		iMinutes = ((iMinutes*10)+iMinutes2);
	}
	else{
		//hours
		iHours = strSunset[0] - '0';
		iHours2 = strSunset[1] - '0';
		
		iHours = ((iHours*10)+iHours2);
		
		//minutes
		iMinutes = strSunset[3] - '0';
		iMinutes2 = strSunset[4] - '0';
		
		iMinutes = ((iMinutes*10)+iMinutes2);
		
	}

	//SUNSET
	struct tm *tz1Ptr = gmtime(&actualPtr);
	tz1Ptr->tm_hour = iHours+12; //assume sunset is always after noon
	tz1Ptr->tm_min = iMinutes;
	
	
	if (clock_is_24h_style()){strftime(formatedsunset, sizeof(formatedsunset), "%H:%M", tz1Ptr);}
	else {strftime(formatedsunset, sizeof(formatedsunset), "%I:%M", tz1Ptr);}	
	
	//Remove the leading 0s
	if (formatedsunset[0]=='0') {memcpy(&formatedsunset," ",1);}
	
	return formatedsunset;
	
}

const char* formatSunrise(char* strSunrise){
	
	time_t actualPtr2 = time(NULL);
	static char formatedsunrise[]="     ";
	int iHours;
	int iHours2;
	int iMinutes;
	int iMinutes2;
	
	//Split the sunset hour and minutes (assume sunrise is always before noon)
	
	if (strSunrise[1]==':'){
		
	
		//hours
		iHours = strSunrise[0] - '0';
		//minutes
		iMinutes = strSunrise[2] - '0';
		iMinutes2 = strSunrise[3] - '0';
		
		iMinutes = ((iMinutes*10)+iMinutes2);
	}
	else{
		//hours
		iHours = strSunrise[0] - '0';
		iHours2 = strSunrise[1] - '0';
		
		iHours = ((iHours*10)+iHours2);
		
		//minutes
		iMinutes = strSunrise[3] - '0';
		iMinutes2 = strSunrise[4] - '0';
		
		iMinutes = ((iMinutes*10)+iMinutes2);
		
	}


	//SUNRISE
	struct tm *tz2Ptr = gmtime(&actualPtr2);
	tz2Ptr->tm_hour = iHours; //assume sunrise is always before noon
	tz2Ptr->tm_min = iMinutes;
	
	
	if (clock_is_24h_style()){strftime(formatedsunrise, sizeof(formatedsunrise), "%H:%M", tz2Ptr);}
	else {strftime(formatedsunrise, sizeof(formatedsunrise), "%I:%M", tz2Ptr);}	
	
	//Remove the leading 0s
	if (formatedsunrise[0]=='0') {memcpy(&formatedsunrise," ",1);}
	
	return formatedsunrise;
	
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
 //   jd = c+e+d-694039.09;  	/* jd is total days elapsed */
	jd = c+e+d-694038.09;  	/* jd is total days elapsed */
    jd /= 29.53;        	/* divide by the moon cycle (29.53 days) */
    b = jd;		   			/* int(jd) -> b, take integer part of jd */
    jd -= b;		   		/* subtract integer part to leave fractional part of original jd */
    b = jd*8 + 0.5;	   		/* scale fraction from 0-8 and round by adding 0.5 */
    b = b & 7;		   		/* 0 and 8 are the same so turn 8 into 0 */
    return b;
}