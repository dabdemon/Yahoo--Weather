#pragma once
#include <pebble.h>

int main(void);
void handle_deinit(void);
void handle_init(void);
void loadFontResources();
void loadForecastIcons();
void unloadForecastIcons();
void unloadFontResource();
void LoadDigital();
void unloadDigital();
void getDate();
void getTime();
void SubscribeTickEvent();
void handle_tick(struct tm *tick_time, TimeUnits units_changed);
static void main_window_load(Window *window);
static void main_window_unload(Window *window);
void LoadTemperature();
void UnloadTemperature();
void LoadForecast();
void UnloadForecast();
void load3DaysIcons();
void unload3DaysIcons();
void Load3Days();
void Unload3Days();
void loadPersistentData(bool refresh, int intKEY);
void refreshLayers();
static void fetchWeather(void);
static void weatherTimer_callback(void *context);
static void forecast_callback(void *context);
static void forecast3Days_callback(void *context);
void accel_tap_handler(AccelAxisType axis, int32_t direction);