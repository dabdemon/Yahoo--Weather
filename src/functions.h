#pragma once
#include <pebble.h>

void hourlyVibe(bool disabled);
bool DoNotDisturb(int Hour, int Minutes, int DNDStart_KEY, int DNDEnd_KEY);
char * itoa (int value, char *result);
const char* formatSunset(char* strSunset);
const char* formatSunrise(char* strSunrise);
int moon_phase(int y, int m, int d);
void ExtendBackLight();
AppTimer *BackLightTimer;