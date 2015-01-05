#pragma once

bool DoNotDisturb(int Hour, int Minutes, int DNDStart_KEY, int DNDEnd_KEY);
const char* formatSunset(char* strSunset);
const char* formatSunrise(char* strSunrise);
int moon_phase(int y, int m, int d);