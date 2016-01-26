#pragma once
#include <pebble.h>
struct InverterLayer;
typedef struct InverterLayer InverterLayer;
InverterLayer* inverter_layer_create(GRect frame);
void inverter_layer_destroy(InverterLayer* inverter_layer);
Layer* inverter_layer_get_layer(InverterLayer *inverter_layer);