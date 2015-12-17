#pragma once
#include <pebble.h>
#include <userInterface.h>

void battery_update_proc(Layer *layer, GContext *ctx);
void handle_battery(BatteryChargeState charge_state);