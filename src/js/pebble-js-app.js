//////////////////////////////////
//DEFINE AND INITALIZE VARIABLES//
//////////////////////////////////

var CLEAR_DAY = 0;
var CLEAR_NIGHT = 1;
var WINDY = 2;
var COLD = 3;
var HOT = 4;
var PARTLY_CLOUDY_DAY = 5;
var PARTLY_CLOUDY_NIGHT = 6;
var FOG = 7;
var RAIN = 8;
var SNOW = 9;
var SLEET = 10;
var SNOW_SLEET = 11;
var RAIN_SLEET = 12;
var RAIN_SNOW = 13;
var CLOUDY = 14;
var STORM = 15;
var NA = 16;
var DRIZZLE = 17;

var imageId = {
  0 : STORM, //tornado
  1 : STORM, //tropical storm
  2 : STORM, //hurricane
  3 : STORM, //severe thunderstorms
  4 : STORM, //thunderstorms
  5 : RAIN_SNOW, //mixed rain and snow
  6 : RAIN_SLEET, //mixed rain and sleet
  7 : SNOW_SLEET, //mixed snow and sleet
  8 : RAIN_SLEET, //freezing drizzle
  9 : DRIZZLE, //drizzle
  10 : RAIN_SLEET, //freezing rain
  11 : RAIN, //showers
  12 : RAIN, //showers
  13 : SNOW, //snow flurries
  14 : SNOW, //light snow showers
  15 : SNOW, //blowing snow
  16 : SNOW, //snow
  17 : SLEET, //hail
  18 : SLEET, //sleet
  19 : FOG, //dust
  20 : FOG, //foggy
  21 : FOG, //haze
  22 : FOG, //smoky
  23 : WINDY, //blustery
  24 : WINDY, //windy
  25 : COLD, //cold
  26 : CLOUDY, //cloudy
  27 : CLOUDY, //mostly cloudy (night)
  28 : CLOUDY, //mostly cloudy (day)
  29 : PARTLY_CLOUDY_NIGHT, //partly cloudy (night)
  30 : PARTLY_CLOUDY_DAY, //partly cloudy (day)
  31 : CLEAR_NIGHT, //clear (night)
  32 : CLEAR_DAY, //sunny
  33 : CLEAR_NIGHT, //fair (night)
  34 : CLEAR_DAY, //fair (day)
  35 : SNOW_SLEET, //mixed rain and hail
  36 : HOT, //hot
  37 : STORM, //isolated thunderstorms
  38 : STORM, //scattered thunderstorms
  39 : STORM, //scattered thunderstorms
  40 : STORM, //scattered showers
  41 : SNOW, //heavy snow
  42 : SNOW, //scattered snow showers
  43 : SNOW, //heavy snow
  44 : CLOUDY, //partly cloudy
  45 : STORM, //thundershowers
  46 : SNOW, //snow showers
  47 : STORM, //isolated thundershowers
  3200 : NA, //not available
};

var TWU = {
	
	"http://icons.wxug.com/i/c/k/chanceflurries.gif" : SNOW,
	"http://icons.wxug.com/i/c/k/chancerain.gif" : RAIN,
	"http://icons.wxug.com/i/c/k/chancesleet.gif" : SLEET,
	"http://icons.wxug.com/i/c/k/chancesnow.gif" : SNOW,
	"http://icons.wxug.com/i/c/k/chancetstorms.gif" : STORM,
	"http://icons.wxug.com/i/c/k/clear.gif" : CLEAR_DAY,
	"http://icons.wxug.com/i/c/k/cloudy.gif" : CLOUDY,
	"http://icons.wxug.com/i/c/k/flurries.gif" : SNOW,
	"http://icons.wxug.com/i/c/k/fog.gif" : FOG,
	"http://icons.wxug.com/i/c/k/hazy.gif" : FOG,
	"http://icons.wxug.com/i/c/k/mostlycloudy.gif" : PARTLY_CLOUDY_DAY,
	"http://icons.wxug.com/i/c/k/mostlysunny.gif" : CLEAR_DAY,
	"http://icons.wxug.com/i/c/k/partlycloudy.gif" : PARTLY_CLOUDY_DAY,
	"http://icons.wxug.com/i/c/k/partlysunny.gif" : PARTLY_CLOUDY_DAY,
	"http://icons.wxug.com/i/c/k/sleet.gif" : SLEET,
	"http://icons.wxug.com/i/c/k/rain.gif" : RAIN,
	"http://icons.wxug.com/i/c/k/snow.gif" : SNOW,
	"http://icons.wxug.com/i/c/k/sunny.gif" : CLEAR_DAY,
	"http://icons.wxug.com/i/c/k/tstorms.gif" : STORM,

	"http://icons.wxug.com/i/c/k/nt_chanceflurries.gif" : SNOW,
	"http://icons.wxug.com/i/c/k/nt_chancerain.gif" : RAIN,
	"http://icons.wxug.com/i/c/k/nt_chancesleet.gif" : SLEET,
	"http://icons.wxug.com/i/c/k/nt_chancesnow.gif" : SNOW,
	"http://icons.wxug.com/i/c/k/nt_chancetstorms.gif" : STORM,
	"http://icons.wxug.com/i/c/k/nt_clear.gif" : CLEAR_NIGHT,
	"http://icons.wxug.com/i/c/k/nt_cloudy.gif" : CLOUDY,
	"http://icons.wxug.com/i/c/k/nt_flurries.gif" : SNOW,
	"http://icons.wxug.com/i/c/k/nt_fog.gif" : FOG,
	"http://icons.wxug.com/i/c/k/nt_hazy.gif" : FOG,
	"http://icons.wxug.com/i/c/k/nt_mostlycloudy.gif" : PARTLY_CLOUDY_NIGHT,
	"http://icons.wxug.com/i/c/k/nt_mostlysunny.gif" : CLEAR_NIGHT,
	"http://icons.wxug.com/i/c/k/nt_partlycloudy.gif" : PARTLY_CLOUDY_NIGHT,
	"http://icons.wxug.com/i/c/k/nt_partlysunny.gif" : PARTLY_CLOUDY_NIGHT,
	"http://icons.wxug.com/i/c/k/nt_sleet.gif" : SLEET,
	"http://icons.wxug.com/i/c/k/nt_rain.gif" : RAIN,
	"http://icons.wxug.com/i/c/k/nt_snow.gif" : SNOW,
	"http://icons.wxug.com/i/c/k/nt_sunny.gif" : CLEAR_NIGHT,
	"http://icons.wxug.com/i/c/k/nt_tstorms.gif" : STORM,

	
};

//////////////////////////	
//Retrieve user settings//
//////////////////////////

var options = JSON.parse(localStorage.getItem('options'));
//console.log('read options: ' + JSON.stringify(options));
if (options === null) options = { "language" : 100, //default to "English"
								  "use_gps" : "true",
                                  "location" : "",
								  "units" : "celsius",
								  "invert_color" : "false",
								  "vibes" : "true",
								  "accuracy" : 16, //default to "Street"
								  "feelslike" : "false",
								  "ESDuration" : 5,
								  "wspeed" : "0",
								  "start" : "0",
								  "end" : "0",
								  "timer" : 30,
								  "hourly_vibe" : "false",
								  "alerts" : "true",
								  "seconds" : "false",
								  "forecast" : "false",
								  "weatherprovider" : "0", //Yahoo! Weather
								  "hide_bat" : "false",
								  "font" : 0,
								  "key" : ""};


/////////////////////////
//Retreive Weather data//
/////////////////////////

///////////////////////////
//The Weather Underground//
///////////////////////////

var twuk = "";

function TWUFromLarLong(latitude, longitude){
	var celsius = options['units'] == 'celsius';
	var url = "http://api.wunderground.com/api/07128f2dabc68d9b/conditions/forecast/astronomy/q/"+latitude+","+longitude+".json";
	var accuracy = options['accuracy']; 
	var req = new XMLHttpRequest();
	req.open('GET', url, true);
	req.onload = function(e) {
		if (req.readyState == 4) {
			if (req.status == 200) {
				console.log(req.responseText);
        response = JSON.parse(req.responseText);
        if (response) {
			
			if (accuracy==6){city = response.current_observation.observation_location.state;}
			if (accuracy==11){city = response.current_observation.display_location.city;}
			if (accuracy==16){city = response.current_observation.display_location.city;}
			
			//Extract the data before sending to Pebble
			if (celsius){temperature = Math.round(response.current_observation.temp_c) + "\u00B0";}
			else {temperature = Math.round(response.current_observation.temp_f) + "\u00B0";}
			
			console.log ("icono: " + response.current_observation.icon_url);
			icon = TWU[response.current_observation.icon_url];

			
			if (celsius){wind = response.current_observation.wind_kph;}
			else{wind = response.current_observation.wind_mph;}
			wdirection = response.current_observation.wind_dir; 

			
			//if user wants to display the Feels Like, override the temperature.
			if (options["feelslike"] == "true"){
				if (celsius){temperature = Math.round(response.current_observation.feelslike_c) + "\u00B0";}
				else {temperature = Math.round(response.current_observation.feelslike_f) + "\u00B0";}
			}
			
			
			
			//if user wants to display the Beaufort scale, override the wind speed.
			if (options["wspeed"] == "3"){
				var beaufort_speed = Beaufort(wind, options['units']);
				wind=beaufort_speed;}
			//if user wants to display the wind speed in m/s, override the wind speed.
			else if(options["wspeed"] == "1"){
				if(celsius){wind=parseFloat(wind)/3.6;}
				else{wind=parseFloat(wind)/2.24;}
				//ensure the result never goes over 2 decimals
				wind=wind.toFixed(2);
			}
			//if user wants to display the wind speed in knots, override the wind speed.
			else if(options["wspeed"] == "2"){
				if(celsius){wind=parseFloat(wind)*0.54;}
				else{wind=parseFloat(wind)*0.87;}
				}
			
					

			
			//Forecast for the day
			if (celsius){high = response.forecast.simpleforecast.forecastday[0].high.celsius + "\u00B0";}
			else {high = response.forecast.simpleforecast.forecastday[0].high.fahrenheit + "\u00B0";}
			
			if (celsius){low = response.forecast.simpleforecast.forecastday[0].low.celsius + "\u00B0";}
			else {low = response.forecast.simpleforecast.forecastday[0].low.fahrenheit + "\u00B0";}
			
			sunrise = response.sun_phase.sunrise.hour+":"+response.sun_phase.sunrise.minute;
			sunset = ((response.sun_phase.sunset.hour)-12)+":"+response.sun_phase.sunset.minute;
			         	
			//Read the 3 days forecast values from the API
			code1 = TWU[response.forecast.simpleforecast.forecastday[1].icon_url]; 
			if (celsius){high1 = response.forecast.simpleforecast.forecastday[1].high.celsius + "\u00B0";}
			else {high1 = response.forecast.simpleforecast.forecastday[1].high.fahrenheit + "\u00B0";}
			
			if (celsius){low1 = response.forecast.simpleforecast.forecastday[1].low.celsius + "\u00B0";}
			else {low1 = response.forecast.simpleforecast.forecastday[1].low.fahrenheit + "\u00B0";}

			code2 = TWU[response.forecast.simpleforecast.forecastday[2].icon_url]; 
			if (celsius){high2 = response.forecast.simpleforecast.forecastday[2].high.celsius + "\u00B0";}
			else {high2 = response.forecast.simpleforecast.forecastday[2].high.fahrenheit + "\u00B0";}
			
			if (celsius){low2 = response.forecast.simpleforecast.forecastday[2].low.celsius + "\u00B0";}
			else {low2 = response.forecast.simpleforecast.forecastday[2].low.fahrenheit + "\u00B0";}

			code3 = TWU[response.forecast.simpleforecast.forecastday[3].icon_url]; 
			if (celsius){high3 = response.forecast.simpleforecast.forecastday[3].high.celsius + "\u00B0";}
			else {high3 = response.forecast.simpleforecast.forecastday[3].high.fahrenheit + "\u00B0";}
			
			if (celsius){low3 = response.forecast.simpleforecast.forecastday[3].low.celsius + "\u00B0";}
			else {low3 = response.forecast.simpleforecast.forecastday[3].low.fahrenheit + "\u00B0";}

			//add a blank space between the - and the temp to better display
			temperature = temperature.replace("-","- "); 
			high1 = high1.replace("-","- ");
			low1 = low1.replace("-","- ");
			high2 = high2.replace("-","- ");
			low2 = low2.replace("-","- ");
			high3 = high3.replace("-","- ");
			low3 = low3.replace("-","- ");
			
			//console logs
			console.log("icon: " + icon + " temp: " + temperature + " city: " + city);
			console.log("today's high: " + high + " today's low: " + low);
			console.log("sunrise: " + sunrise + " sunset: " + sunset);
			console.log("wspeed unit: " + options["wspeed"]);
			console.log("wind speed: " + wind + " wind direction: " + wdirection);
			console.log("icon1: " + code1 + " high1: " + high1 + " low1: " + low1);
			console.log("icon2: " + code2 + " high2: " + high2 + " low2: " + low2);
			console.log("icon3: " + code3 + " high3: " + high3 + " low3: " + low3);
			console.log("start: " + parseInt(options["start"]) + " end: " + parseInt(options["end"]));
			console.log("display battery: " + (options["hide_bat"] == "true" ? 1 : 0));
			
			//send the values to the Pebble!!
			Pebble.sendAppMessage({
				//Current conditions
				"icon":icon,
				"temperature":temperature, //Round the temperature
				"city":city,
				//User preferences
				"invert_color" : (options["invert_color"] == "true" ? 1 : 0),
				"language" : parseInt(options['language']),
				"vibes" : (options["vibes"] == "true" ? 1 : 0),
				//Forecast for the day
				"high":high,
				"low":low,
				"sunrise":sunrise,
				"sunset":sunset,
				"wind":wind.toString(),
				"wdirection" : wdirection,
				//3 days forecast data
				"day1code":code1,
				"day1H":high1,
				"day1L":low1,
				"day2code":code2,
				"day2H":high2,
				"day2L":low2,
				"day3code":code3,
				"day3H":high3,
				"day3L":low3,
				//Extra Features
				"ESDuration":parseInt(options['ESDuration']),
				"timer":parseInt(options['timer']),
				"seconds":(options["seconds"] == "true" ? 1 : 0),
				"hourly_vibe":(options["hourly_vibe"] == "true" ? 1 : 0),
				//YWeather v2.4 - Hourly Vibe Quiet Hours - START
				"start":parseInt(options["start"]),
				"end":parseInt(options["end"]),
				//YWeather v2.4 - Hourly Vibe Quiet Hours - END
				"forecast":(options["forecast"] == "true" ? 1 : 0),
				"hide_bat" : (options["hide_bat"] == "true" ? 1 : 0),
				"font" : parseInt(options['font']),
          });
			
        }
      } else {
        console.log("unable to get woeid from The Weather Underground API");
		if(options['alerts']== "true"){
			Pebble.showSimpleNotificationOnPebble("YWeather", "Yahoo! Weather seems to be down... is this the end of the world?");
		}
      }
    }
  }
  req.send(null);
}

//////////////////
//Yahoo! Weather//
//////////////////

//Retrieve the WOEID & City name from Yahoo! when GPS is OFF
function getWeatherFromLatLong(latitude, longitude) {
  var response;
  var woeid = -1;
  var accuracy = options['accuracy']; 
  var query = encodeURI("select woeid, county, city, street from geo.placefinder where text=\"" + latitude + "," + longitude +"\" and gflags=\"R\"");
	console.log("geo query: " + query);
  var url = "http://query.yahooapis.com/v1/public/yql?q=" + query + "&format=json";
  var req = new XMLHttpRequest();
  req.open('GET', url, true);
  req.onload = function(e) {
    if (req.readyState == 4) {
      if (req.status == 200) {
        console.log(req.responseText);
        response = JSON.parse(req.responseText);
        if (response) {
			woeid = response.query.results.Result.woeid;
			
			if (accuracy==6){city = response.query.results.Result.county;}
			if (accuracy==11){city = response.query.results.Result.city;}
			if (accuracy==16){city = response.query.results.Result.street;}
			
			getWeatherFromWoeid(woeid, city);
        }
      } else {
        console.log("unable to get woeid from Yahoo! API");
		if(options['alerts']== "true"){
			Pebble.showSimpleNotificationOnPebble("YWeather", "I cannot retrieve the weather from Yahoo! Weather.");
		}
      }
    }
  }
  req.send(null);
}



//Retrieve the WOEID & City name from Yahoo! when GPS is OFF
function getWeatherFromLocation(location_name) {
  var response;
  var woeid = -1;
  var query = encodeURI("select woeid, name from geo.places(1) where text=\"" + location_name + "\"");
  var url = "http://query.yahooapis.com/v1/public/yql?q=" + query + "&format=json";
  var req = new XMLHttpRequest();
  req.open('GET', url, true);
  req.onload = function(e) {
    if (req.readyState == 4) {
      if (req.status == 200) {
        console.log(req.responseText);
        response = JSON.parse(req.responseText);
        if (response) {
			woeid = response.query.results.place.woeid;
			city = response.query.results.place.name;
			
			getWeatherFromWoeid(woeid, city);
        }
      } else {
        console.log("unable to get woeid from Yahoo! API");
		if(options['alerts']== "true"){
			Pebble.showSimpleNotificationOnPebble("YWeather", "I cannot retrieve the weather data from Yahoo! Weather");
		}
      }
    }
  }
  req.send(null);
}

//Retrieves the Weather data from Yahoo! Weather//
function getWeatherFromWoeid(woeid, city) {
	
	/*if Hong Kong then override the woeid with a valid one*/
	if (woeid ==24865698){woeid=12467924};
	/*if Ottawa the override the woeid with a valid one*/
	if (woeid ==91982014){woeid=29375164};
	
  var celsius = options['units'] == 'celsius';
	
	
	//get today's conditions	
	var query = encodeURI("select  item.condition, item.forecast, astronomy, wind, atmosphere from weather.forecast where woeid = " + woeid +
                        " and u = " + (celsius ? "\"c\"" : "\"f\"") + " |truncate(count=4)");
	
  var url = "http://query.yahooapis.com/v1/public/yql?q=" + query + "&format=json";

  var response;
  var req = new XMLHttpRequest();
  console.log(url);
  req.open('GET', url, true);
  req.onload = function(e) {
    if (req.readyState == 4) {
      if (req.status == 200) {
        response = JSON.parse(req.responseText);
        if (response) {
			var channel = response.query.results.channel;

			temperature = channel[0].item.condition.temp + "\u00B0";
			//if current conditions are not retrieved, get the forecasted for the day icon
			if (channel[0].item.condition.code == 3200){icon = imageId[channel[0].item.forecast.code];}
			else {icon = imageId[channel[0].item.condition.code];}

			//Forecast for the day
			high = channel[0].item.forecast.high + "\u00B0";
			low = channel[0].item.forecast.low + "\u00B0";
			sunrise = channel[0].astronomy.sunrise;
			sunset = channel[0].astronomy.sunset;
			wind = channel[0].wind.speed;
			wdirection = windDirection(channel[0].wind.direction);
			

			//Feels Like
			wind_chill = channel[0].wind.chill;
			humidity =  channel[0].atmosphere.humidity;
			
			//override defaults based on settings
			
			//if user wants to display the Feels Like, override the temperature.
			if (options["feelslike"] == "true"){
				var Feels_Like = FeelsLike(wind_chill,humidity, options['units']);
				temperature=Feels_Like + "\u00B0";}
			
			
			//if user wants to display the Beaufort scale, override the wind speed.
			if (options["wspeed"] == "3"){
				var beaufort_speed = Beaufort(wind, options['units']);
				wind=beaufort_speed;}
			//if user wants to display the wind speed in m/s, override the wind speed.
			else if(options["wspeed"] == "1"){
				if(celsius){wind=parseFloat(wind)/3.6;}
				else{wind=parseFloat(wind)/2.24;}
				//ensure the result never goes over 2 decimals
				wind = wind.toFixed(2);
			}
			//if user wants to display the wind speed in knots, override the wind speed.
			else if(options["wspeed"] == "2"){
				if(celsius){wind=parseFloat(wind)*0.54;}
				else{wind=parseFloat(wind)*0.87;}
				
				}
			

			         	
			//Read the 3 days forecast values from the API
			code1 = imageId[channel[1].item.forecast.code];
			high1 = channel[1].item.forecast.high + "\u00B0";
			low1 = channel[1].item.forecast.low + "\u00B0";

			code2 = imageId[channel[2].item.forecast.code];
			high2 = channel[2].item.forecast.high + "\u00B0";
			low2 = channel[2].item.forecast.low + "\u00B0";

			code3 = imageId[channel[3].item.forecast.code];
			high3 = channel[3].item.forecast.high + "\u00B0";
			low3 = channel[3].item.forecast.low + "\u00B0";

			//add a blank space between the - and the temp to better display
			temperature = temperature.replace("-","- "); 
			high1 = high1.replace("-","- ");
			low1 = low1.replace("-","- ");
			high2 = high2.replace("-","- ");
			low2 = low2.replace("-","- ");
			high3 = high3.replace("-","- ");
			low3 = low3.replace("-","- ");
			
			//console logs
			console.log("icon: " + icon + " temp: " + temperature + " city: " + city);
			console.log("wind chill: " + wind_chill + " humidiy: " + humidity +  " Feels Like: " + Feels_Like);
			console.log("today's high: " + high + " today's low: " + low);
			console.log("sunrise: " + sunrise + " sunset: " + sunset);
			console.log("wspeed unit: " + options["wspeed"]);
			console.log("wind speed: " + wind + " wind direction: " + wdirection);
			console.log("icon1: " + code1 + " high1: " + high1 + " low1: " + low1);
			console.log("icon2: " + code2 + " high2: " + high2 + " low2: " + low2);
			console.log("icon3: " + code3 + " high3: " + high3 + " low3: " + low3);
			console.log("start: " + parseInt(options["start"]) + " end: " + parseInt(options["end"]));
			
			//send the values to the Pebble!!
			Pebble.sendAppMessage({
				//Current conditions
				"icon":icon,
				"temperature":temperature,
				"city":city,
				//User preferences
				"invert_color" : (options["invert_color"] == "true" ? 1 : 0),
				"language" : parseInt(options['language']),
				"vibes" : (options["vibes"] == "true" ? 1 : 0),
				//Forecast for the day
				"high":high,
				"low":low,
				"sunrise":sunrise,
				"sunset":sunset,
				"wind":wind,
				"wdirection" : wdirection,
				//3 days forecast data
				"day1code":code1,
				"day1H":high1,
				"day1L":low1,
				"day2code":code2,
				"day2H":high2,
				"day2L":low2,
				"day3code":code3,
				"day3H":high3,
				"day3L":low3,
				//Extra Features
				"ESDuration":parseInt(options['ESDuration']),
				"timer":parseInt(options['timer']),
				"seconds":(options["seconds"] == "true" ? 1 : 0),
				"hourly_vibe":(options["hourly_vibe"] == "true" ? 1 : 0),
				//YWeather v2.4 - Hourly Vibe Quiet Hours - START
				"start":parseInt(options["start"]),
				"end":parseInt(options["end"]),
				//YWeather v2.4 - Hourly Vibe Quiet Hours - END
				"forecast":(options["forecast"] == "true" ? 1 : 0),
				"hide_bat" : (options["hide_bat"] == "true" ? 1 : 0),
				"font" : parseInt(options['font']),
          });
        }
      } else {
        console.log("Error WFW");
	//YWeather 2.4 - Enable/Disable Alerts - START
	if(options['alerts']== "true"){
		Pebble.showSimpleNotificationOnPebble("YWeather", "I cannot fetch the weather data. Are you online?");
	}
	//YWeather 2.4 - Enable/Disable Alerts - END
      }
    }
  }
  req.send(null);
}


//Retrieve the weather based on the selected settings (GPS on/off)
function updateWeather() {
  if (options['use_gps'] == "true") {
	console.log("Getting GPS current position");
    window.navigator.geolocation.getCurrentPosition(locationSuccess,
                                                    locationError,
                                                    locationOptions);
  } else {
    getWeatherFromLocation(options["location"]);
  }
}

var locationOptions = { "timeout": 15000, "maximumAge": 60000, "enableHighAccuracy": true};

function locationSuccess(pos) {
  var coordinates = pos.coords;
  console.log("location success");

	//call the weather function based on the selected provider (defaulted to Yahoo! Weather)
	if (options['weatherprovider']=="1"){TWUFromLarLong(coordinates.latitude, coordinates.longitude);}
	else {getWeatherFromLatLong(coordinates.latitude, coordinates.longitude);}
}

function locationError(err) {
  console.warn('location error (' + err.code + '): ' + err.message);
  Pebble.sendAppMessage({
//YWeather 2.3 - FIX01. Never blank out a location on disconect - START
   // "icon":16,
   // "temperature":"",
	"city":"location error",
//YWeather 2.3 - FIX01. Never blank out a location on disconect - END
	    //Put here the output parameters to "Main.C"
  });
//YWeather 2.4 - Enable/Disable Alerts - START
	if(options['alerts']== "true"){
//YWeather 2.3 - FIX01. Never blank out a location on disconect - START
	Pebble.showSimpleNotificationOnPebble("YWeather", "I cannot locate you. Are you inside a building?");
//YWeather 2.3 - FIX01. Never blank out a location on disconect - END
	}
//YWeather 2.4 - Enable/Disable Alerts - END
}



// Heat index computed using air temperature and RH%
function FeelsLike(wind_chill, humidity, unit){

	//console.log("unit: " + unit)
	if (unit == 'celsius'){
		//convert to Fareheith to run the calculations
		var tempair_in_fahrenheit = 1.80 * wind_chill + 32.0;
	}
	else   {
		var tempair_in_fahrenheit = wind_chill;
	}

    var hitemp = 61.0+((tempair_in_fahrenheit-68.0)*1.2)+(humidity*0.094);
	var fptemp = parseFloat(tempair_in_fahrenheit);
    var hifinal = 0.5*(fptemp+hitemp);
	
	console.log("tempair_in_fahrenheit: " + tempair_in_fahrenheit + " hitemp: " + hitemp + " fptemp: " + fptemp + " hifinal: " + hifinal)

    if(hifinal > 79.0){
        var hi = -42.379 + 2.04901523 * tempair_in_fahrenheit + 10.14333127 * 
				humidity - 0.22475541 * tempair_in_fahrenheit * humidity - 6.83783 * 
				(Math.pow(10, -3)) * (Math.pow(tempair_in_fahrenheit, 2)) - 5.481717 * 
				(Math.pow(10, -2)) * (Math.pow(humidity, 2)) + 1.22874 * 
				(Math.pow(10, -3)) * (Math.pow(tempair_in_fahrenheit, 2)) * humidity + 8.5282 * 
				(Math.pow(10, -4)) * tempair_in_fahrenheit * (Math.pow(humidity, 2)) - 1.99 * 
				(Math.pow(10, -6)) * (Math.pow(tempair_in_fahrenheit, 2)) * (Math.pow(humidity,2));

            if((humidity <= 13) && (tempair_in_fahrenheit >= 80.0) && (tempair_in_fahrenheit <= 112.0)) {
                var adj1 = (13.0-humidity)/4.0;
                var adj2 = Math.sqrt((17.0-Math.abs(tempair_in_fahrenheit-95.0))/17.0);
                var adj = adj1 * adj2;
                var hi = hi - adj;
            }
            else if ((humidity > 85.0) && (tempair_in_fahrenheit >= 80.0) && (tempair_in_fahrenheit <= 87.0)) {
                var adj1 = (humidity-85.0)/10.0;
                var adj2 = (87.0-tempair_in_fahrenheit)/5.0;
                var adj = adj1 * adj2;
                var hi = hi + adj;
            }
        }
        else{
            var hi = hifinal;
        }

	if (unit=='celsius'){
		hi = Math.round((hi - 32) * .556);
	}
	
	return Math.round(hi);
}

function Beaufort(speed, unit){
	
	if (unit != 'celsius'){speed = speed*1.378628808;}
	
	var beaufort_sp = "0";
	
	if (speed < 2) {beaufort_sp = "0";}
	else if ((speed >= 2) && (speed <6)) { beaufort_sp = "1";}
	else if ((speed >= 6) && (speed <12)) { beaufort_sp = "2";}
	else if ((speed >= 12) && (speed <20)) { beaufort_sp = "3";}
	else if ((speed >= 20) && (speed <29)) { beaufort_sp = "4";}
	else if ((speed >= 29) && (speed <39)) { beaufort_sp = "5";}
	else if ((speed >= 39) && (speed <50)) { beaufort_sp = "6";}
	else if ((speed >= 50) && (speed <62)) { beaufort_sp = "7";}
	else if ((speed >= 62) && (speed <75)) { beaufort_sp = "8";}
	else if ((speed >= 75) && (speed <89)) { beaufort_sp = "9";}
	else if ((speed >= 89) && (speed <103)) { beaufort_sp = "10";}
	else if ((speed >= 103) && (speed <118)) { beaufort_sp = "11";}
	else if (speed >= 118) { beaufort_sp = "12";}
	
	return beaufort_sp;
}


/*****************************/
/* Decode the Wind Direction */
/*****************************/

function windDirection(wdirection)
{
/*
Wind directions
	
N 348.75 - 11.25
NNE 11.25 - 33.75
NE 33.75 - 56.25
ENE 56.25 - 78.75
E 78.75 - 101.25
ESE 101.25 - 123.75
SE 123.75 - 146.25
SSE 146.25 - 168.75
S 168.75 - 191.25
SSW 191.25 - 213.75
SW 213.75 - 236.25
WSW 236.25 - 258.75
W 258.75 - 281.25
WNW 281.25 - 303.75
NW 303.75 - 326.25
NNW 326.25 - 348.75

*/
	
	//correct the wind direction if blank
	if (wdirection == ""){wdirection=0;}
	
	var strwdirection;
	
	if((wdirection>348)||(wdirection<12)){strwdirection = "N";}
	else if((wdirection>11)&&(wdirection<34)){strwdirection = "NNE";}
	else if((wdirection>33)&&(wdirection<57)){strwdirection = "NE";}
	else if((wdirection>56)&&(wdirection<79)){strwdirection = "ENE";}
	else if((wdirection>78)&&(wdirection<102)){strwdirection = "E";}
	else if((wdirection>101)&&(wdirection<124)){strwdirection = "ESE";}
	else if((wdirection>123)&&(wdirection<147)){strwdirection = "SE";}
	else if((wdirection>146)&&(wdirection<169)){strwdirection = "SSE";}
	else if((wdirection>168)&&(wdirection<191)){strwdirection = "S";}
	else if((wdirection>191)&&(wdirection<214)){strwdirection ="SSW";}
	else if((wdirection>214)&&(wdirection<237)){strwdirection = "SW";}
	else if((wdirection>237)&&(wdirection<259)){strwdirection = "WSW";}
	else if((wdirection>259)&&(wdirection<282)){strwdirection = "W";}
	else if((wdirection>282)&&(wdirection<304)){strwdirection = "WNW";}
	else if((wdirection>304)&&(wdirection<327)){strwdirection = "NW";}
	else if((wdirection>326)&&(wdirection<349)){strwdirection = "NNW";}
	
	return strwdirection;

}




///////////////////////////////////////
//Setup the connection with the watch//
///////////////////////////////////////

//Displays the configuration page in the phone
Pebble.addEventListener('showConfiguration', function(e) {
  var uri = 'http://dabdemon.github.io/Yahoo--Weather/development.html?' + //Here you need to enter your configuration webservice
    'language=' + encodeURIComponent(options['language']) +
	'&use_gps=' + encodeURIComponent(options['use_gps']) +
    '&location=' + encodeURIComponent(options['location']) +
    '&units=' + encodeURIComponent(options['units']) +
    '&invert_color=' + encodeURIComponent(options['invert_color']) +
	'&vibes=' + encodeURIComponent(options['vibes']) +
	'&accuracy=' + encodeURIComponent(options['accuracy']) +
	'&feelslike=' + encodeURIComponent(options['feelslike']) +
	'&ESDuration=' + encodeURIComponent(options['ESDuration']) +
	'&wspeed=' + encodeURIComponent(options['wspeed']) +	
	'&start=' + encodeURIComponent(options['start']) +	
	'&end=' + encodeURIComponent(options['end']) +	
	'&timer=' + encodeURIComponent(options['timer']) +
	'&UUID=' + encodeURIComponent(Pebble.getAccountToken()) +
	'&lt=' + encodeURIComponent(CheckUserKey()) +
	'&key=' + encodeURIComponent(options['key']) +
//YWeather 2.3 - REQ02. Hourly Vibe - START
	'&hourly_vibe=' + encodeURIComponent(options['hourly_vibe']) +
//YWeather 2.3 - REQ02. Hourly Vibe - END
//YWeather 2.4 - Enable/Disable Alerts - START
	'&alerts=' + encodeURIComponent(options['alerts']) +
//YWeather 2.4 - Enable/Disable Alerts - END
//YWeather 2.3 - REQ01. Display Seconds - START
	'&seconds=' + encodeURIComponent(options['seconds']) +
//YWeather 2.3 - REQ01. Display Seconds - END
	'&weatherprovider=' + encodeURIComponent(options['weatherprovider']) +
	'&hide_bat=' + encodeURIComponent(options['hide_bat']) +
	'&start=' + encodeURIComponent(options['start']) +
	'&end=' + encodeURIComponent(options['end']) +
	'&font=' + encodeURIComponent(options['font']) +
	'&forecast=' + encodeURIComponent(options['forecast']);

	//console.log('showing configuration at uri: ' + uri);

  Pebble.openURL(uri);
});

//Retrieve user settings after submitting
Pebble.addEventListener('webviewclosed', function(e) {
  if (e.response) {
    options = JSON.parse(decodeURIComponent(e.response));
    localStorage.setItem('options', JSON.stringify(options));
    console.log('storing options: ' + JSON.stringify(options));
    updateWeather();
  } else {
    console.log('no options received');
  }
});

//Receive the Pebble's call to refresh the weather info
Pebble.addEventListener("appmessage",
                        function(e) {
                          updateWeather();
                        });

//Initiate the Appsync (This event is called just once)
Pebble.addEventListener("ready", function(e) {
  console.log("connect!" + e.ready);
  console.log("Pebble Account Token: " + Pebble.getAccountToken());
	
  updateWeather();
	


});
