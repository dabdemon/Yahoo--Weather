//******************//
// DEFINE THE ICONS //
//******************//  
const int MOON_IMAGE_RESOURCE_IDS[] = {
  RESOURCE_ID_MOON_0,
  RESOURCE_ID_MOON_1,
  RESOURCE_ID_MOON_2,
  RESOURCE_ID_MOON_3,
  RESOURCE_ID_MOON_4,
  RESOURCE_ID_MOON_5,
  RESOURCE_ID_MOON_6,
  RESOURCE_ID_MOON_7
};

static const uint32_t WEATHER_ICONS[] = {
  RESOURCE_ID_ICON_CLEAR_DAY,
  RESOURCE_ID_ICON_CLEAR_NIGHT,
  RESOURCE_ID_ICON_WIND,
  RESOURCE_ID_ICON_COLD,
  RESOURCE_ID_ICON_HOT,
  RESOURCE_ID_ICON_PARTLY_CLOUDY_DAY,
  RESOURCE_ID_ICON_PARTLY_CLOUDY_NIGHT,
  RESOURCE_ID_ICON_FOG,
  RESOURCE_ID_ICON_RAIN,
  RESOURCE_ID_ICON_SNOW,
  RESOURCE_ID_ICON_SLEET,
  RESOURCE_ID_ICON_SNOW_SLEET,
  RESOURCE_ID_ICON_RAIN_SLEET,
  RESOURCE_ID_ICON_RAIN_SNOW,
  RESOURCE_ID_ICON_CLOUDY,
  RESOURCE_ID_ICON_THUNDER,
  RESOURCE_ID_ICON_NOT_AVAILABLE,
  RESOURCE_ID_ICON_DRIZZLE,
}; 

		static GBitmap *BT_image;
        static BitmapLayer *BT_icon_layer; //Layer for the BT connection
        
        static GBitmap *Batt_image;
        static BitmapLayer *Batt_icon_layer; //Layer for the Battery status
        
        static GBitmap *weather_image;
        static BitmapLayer *weather_icon_layer; //Layer for the weather info

        static GBitmap *sunset_image;
        static BitmapLayer *sunset_icon_layer; //Layer for the sunset info

        static GBitmap *sunrise_image;
        static BitmapLayer *sunrise_icon_layer; //Layer for the sunrise info

        static GBitmap *high_image;
        static BitmapLayer *high_icon_layer; //Layer for the high info

        static GBitmap *low_image;
        static BitmapLayer *low_icon_layer; //Layer for the low info

        static GBitmap *wind_image;
        static BitmapLayer *wind_icon_layer; //Layer for the wind info

        static GBitmap *moon_image;
        static BitmapLayer *moon_icon_layer; //Layer for the wind info

        static GBitmap *chinese_day;
        static BitmapLayer *chinese_day_layer; //Layer for the weather info