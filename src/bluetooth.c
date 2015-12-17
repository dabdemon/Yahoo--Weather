#include <bluetooth.h>

//Define variables
int blnConnected = false;
//const char *batt;

//******************************//
// Handle Bluetooth Connection //
//*****************************//

void handle_bluetooth(bool connected)
{
        
      //draw the phone disconnected icon (when not connected)       
      if(connected == false)
        {
      
      #ifdef PBL_RECT
          if (BT_image !=NULL) {gbitmap_destroy(BT_image);}
          BT_image = gbitmap_create_with_resource(RESOURCE_ID_PHONE_DISCONNECTED);
          bitmap_layer_set_bitmap(BT_icon_layer, BT_image);
		  //remove the battery text layer
		  //batt = text_layer_get_text(Batt_Layer);
		  //text_layer_set_text(Batt_Layer, "");
		  text_layer_set_text_color(Batt_Layer, GColorBlack);
  
          //#ifdef PBL_BW
          //bitmap_layer_set_compositing_mode(BT_icon_layer, GCompOpAssign);
          //#elif PBL_COLOR
          bitmap_layer_set_compositing_mode(BT_icon_layer, GCompOpSet);
          //#endif
      #else
            text_layer_set_background_color(line, GColorRed);   
      #endif
		  
		  //check if we need to vibe or not
		  vibes();
        }
        else
        {
          #ifdef PBL_RECT
            //Kill the previous image
            bitmap_layer_set_bitmap(BT_icon_layer, NULL);
			//Set back the battery text layer
			//text_layer_set_text(Batt_Layer, batt);
			text_layer_set_text_color(Batt_Layer, GColorWhite);
          #else
            text_layer_set_background_color(line, GColorWhite);
          #endif
			
		  //check if we need to vibe or not
		  vibes();
		}
        
}

/**************************/
// Vibes on disconnection //
/**************************/

static void vibes()
{


	//Vibes to aler the user if its the first time it vibes OR if the user selected to
	//vibe until the connection is restored.
	
	if (persist_read_int(VIBES_KEY) == 2){
	
			//Vibes to alert disconnection and do this every minute until the connection is restored
			if (bluetooth_connection_service_peek()== false){
					//alert the user about the BT connection
					vibes_long_pulse();}			
	}
	else if (persist_read_int(VIBES_KEY) == 1){
			//Vibes on connection
			if (blnConnected == false){
				if (bluetooth_connection_service_peek() == true){
					blnConnected = true;
				}
			}
			//Vibes on disconnect (just once)
			if (blnConnected == true){
				//Vibes to alert disconnection
				if (bluetooth_connection_service_peek()== false){
					//alert the user about the BT connection
					vibes_long_pulse();			
					blnConnected = false;
				}
			}
	
}

}	


