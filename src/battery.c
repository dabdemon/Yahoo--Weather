#include <battery.h>
#include <bluetooth.h>

//Define private variable to share the battery level to the graphic control (for PTR)
int intBatteryLevel;

void battery_update_proc(Layer *layer, GContext *ctx){

#ifdef PBL_SDK_3
	
	int lineWidth = 1;
	GRect rect = GRect(0,0,0,0);
	
	#ifdef PBL_ROUND
		rect = GRect (2, 2, 176, 176);
		lineWidth = 15;
	#else
		rect = GRect (120, 3, 23, 23);
		lineWidth = 2;
	#endif
	
  //When Charging
  if (intBatteryLevel == -1){
      graphics_context_set_stroke_color(ctx, GColorYellow);
      graphics_context_set_stroke_width(ctx, lineWidth);
      graphics_draw_arc(ctx, rect, GOvalScaleModeFitCircle,0, TRIG_MAX_ANGLE);
    
  }
  //When Discharging
  else{
  
	  #ifdef PBL_RECT
	  //Draw the outfill battery circle (on squared watches only)
	  	#ifdef PBL_COLOR
		  graphics_context_set_stroke_color(ctx, GColorDarkGray);
		  graphics_context_set_stroke_width(ctx, lineWidth);
		  graphics_draw_arc(ctx, rect, GOvalScaleModeFitCircle,0, TRIG_MAX_ANGLE);
	  /*
	  	#else
	   	  graphics_context_set_stroke_color(ctx, GColorWhite);
		  graphics_context_set_stroke_width(ctx, 1);
		  graphics_draw_arc(ctx, rect, GOvalScaleModeFitCircle,0, TRIG_MAX_ANGLE);
	 */
	  	#endif

	  #endif
	  
     int maxAngle = intBatteryLevel * TRIG_MAX_ANGLE / 100;
    //set the stroke color based on the remaining battery life
	 
	#ifdef PBL_COLOR
    if (intBatteryLevel < 30){
      graphics_context_set_stroke_color(ctx, GColorRed);
    }
    else if (intBatteryLevel < 50) {
      graphics_context_set_stroke_color(ctx, GColorOrange);
    }
    else if (intBatteryLevel < 70) {
      graphics_context_set_stroke_color(ctx, GColorYellow);
    }
    else{
      graphics_context_set_stroke_color(ctx, GColorGreen);
    }
	#else
	   graphics_context_set_stroke_color(ctx, GColorWhite);
	#endif
      
	  //Draw the battery level
      graphics_context_set_stroke_width(ctx, lineWidth);
      graphics_draw_arc(ctx, rect, GOvalScaleModeFitCircle,0, maxAngle);
	 
  }
#else
	  graphics_context_set_stroke_color(ctx, GColorWhite);
	  graphics_draw_circle(ctx, GPoint(131, 14), 12);
#endif
	
	//finally, on APLITE check the BT status to override the new Battery Level with the "NC" message if needed
	  handle_bluetooth(connection_service_peek_pebble_app_connection());
	
	
}
void handle_battery(BatteryChargeState charge_state) {
    
	//Define variable to display the Battery level (forget about icons... it is not so cool anymore)
	static char battery_text[9];
	

  if (charge_state.is_charging) {
    #ifdef PBL_RECT
    	//snprintf(battery_text, sizeof(battery_text), "CHRG");
	  	snprintf(battery_text, sizeof(battery_text), "chr");
	#endif
	
	#ifdef PBL_SDK_3
	  //set th battery level indicator to (-1 charging)
      	intBatteryLevel = -1;
    #endif
    
  } else {
    #ifdef PBL_SDK_3
      	intBatteryLevel = charge_state.charge_percent; 
	#endif
	  
	#ifdef PBL_RECT
	  	snprintf(battery_text, sizeof(battery_text), "%d", charge_state.charge_percent);
    #endif
	  
  }
  
  //We just need to refresh the layer on Pebble Time Round. On the original Pebble and Pebble Time(Steel) we are just
  //refreshing the icon on the handle_battery. Refreshing the layer on squared screens is actually crashing the app.
  	
	//#ifdef PBL_SDK_3
    	layer_mark_dirty(battery_layer);
	//#endif
	
	#ifdef PBL_RECT
		//refresh the battery layer
		text_layer_set_text(Batt_Layer, battery_text);
  	#endif
}


	