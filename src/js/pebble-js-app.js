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

var forecastio = {
 
  "rain" : RAIN, //rain
  "snow" : SNOW, //snow 
  "sleet" : SLEET, //sleet
  "fog" : FOG, //foggy
  "wind" : WINDY, //windy
  "cloudy" : CLOUDY, //cloudy
  "partly-cloudy-night" : PARTLY_CLOUDY_NIGHT, //partly cloudy (night)
  "partly-cloudy-day" : PARTLY_CLOUDY_DAY, //partly cloudy (day)
  "clear-night" : CLEAR_NIGHT, //clear (night)
  "clear-day" : CLEAR_DAY, //sunny
  
		
};

var openweather = {


	200:STORM,
	201:STORM,
	202:STORM,
	210:STORM,
	211:STORM,
	212:STORM,
	221:STORM,
	230:STORM,
	231:STORM,
	232:STORM,

	300:RAIN,
	301:RAIN,
	302:RAIN,
	310:RAIN,
	311:RAIN,
	312:RAIN,
	313:RAIN,
	314:RAIN,
	321:RAIN,

	500:RAIN,
	501:RAIN,
	502:RAIN,
	503:RAIN,
	504:RAIN,
	511:RAIN_SNOW,
	520:RAIN,
	521:RAIN,
	522:RAIN,
	531:RAIN,

	600:SNOW,
	601:SNOW,
	602:SNOW,
	611:SLEET,
	612:SLEET,
	615:RAIN_SNOW,
	616:RAIN_SNOW,
	620:RAIN_SNOW,
	621:RAIN_SNOW,
	622:RAIN_SNOW,

	701:FOG,
	711:FOG,
	721:FOG,
	731:FOG,
	741:FOG,
	751:FOG,
	761:FOG,
	762:FOG,
	771:FOG,
	781:STORM,

	800:CLEAR_DAY,
	801:PARTLY_CLOUDY_DAY,
	802:CLOUDY,
	803:CLOUDY,
	804:CLOUDY,

	900:STORM,
	90:STORM,
	902:STORM,
	903:COLD,
	904:HOT,
	905:WINDY,
	906:SLEET,

	950:CLEAR_DAY,
	951:CLEAR_DAY,
	952:WINDY,
	953:WINDY,
	954:WINDY,
	955:WINDY,
	956:WINDY,
	957:STORM,
	958:STORM,
	959:STORM,
	960:STORM,
	961:STORM,
	962:STORM,

};

//////////////////////////	
//Retrieve user settings//
//////////////////////////

var options = JSON.parse(localStorage.getItem('options'));
//console.log('read options: ' + JSON.stringify(options));
if (options === null) options = { "language" : 100, //default to "Watch Language"
								"theme" : 1, //default to Digital
								"use_gps" : "false",
								"location" : "madrid",
								"units" : "celsius",
								"invert_color" : "false",
								"vibes" : 1,
								"accuracy" : 16, //default to "Street"
								"feelslike" : "false",
								"ESDuration" : 5,
								"wspeed" : "0",
								"start" : "0",
								"end" : "0",
								"timer" : 30,
								"hourly_vibe" : "false",
								"alerts" : "false",
								"seconds" : "false",
								"forecast" : "false",
								"weatherprovider" : "0", //Yahoo! Weather
								"hide_bat" : "false",
								"backlight" : "false",
								"CustomAPIKey" : "",
								//"font" : 0,
								"key" : ""};


function UNIX2Date(UNIXDt){
	
	var date = new Date(UNIXDt*1000);
	// hours part from the timestamp
	var hours = date.getHours();
	// minutes part from the timestamp
	var minutes = "0" + date.getMinutes();
	// seconds part from the timestamp
	var seconds = "0" + date.getSeconds();

	// will display time in 10:30:23 format
	var HumanDate = hours + ':' + minutes.substr(minutes.length-2); //+ ':' + seconds.substr(seconds.length-2);
	
	return HumanDate;
}

function getLocationName(pos){
	
	var url = "http://maps.googleapis.com/maps/api/geocode/json?latlng=" + pos + "";
	console.log("get location URL: " + url);
	var response;
	var req = new XMLHttpRequest();
	req.open('GET', url, false);
	req.send();

		if (req.readyState == 4) {
			if (req.status == 200) {
				response = JSON.parse(req.responseText);
				if (response) {
					//var position = new Array({'lat' : response.results[0].geometry.location.lat,
					//						'long' : response.results[0].geometry.location.lng});

					var location = new Array(2);
					location[0] = response.results[0].address_components[1].short_name; //Street
					location[1] = response.results[0].address_components[2].short_name;//City
					location[2] = response.results[0].address_components[3].long_name; //Province
					//console.log("ya he rellenado el array y voy a leerlo");
					console.log("Street: " + location[0]);
					console.log("City: " + location[1]);
					console.log("Province: " + location[2]);
					return location;
					}
				}
			}
}

/////////////////////////
//Retreive Weather data//
/////////////////////////

///////////////////////////
//The Weather Underground//
///////////////////////////

var twuk = "3035a2f0eb84c254";

function TWUFromLarLong(latitude, longitude){
	var celsius = options['units'] == 'celsius';
	var APIKey = options['CustomAPIKey'];
	
	//Developer wildcard ;-)
	if (APIKey == "qwerty1234"){APIKey = twuk;}
	
	var url = "http://api.wunderground.com/api/"+APIKey+"/conditions/forecast/astronomy/q/"+latitude+","+longitude+".json";
	var accuracy = options['accuracy']; 
	var req = new XMLHttpRequest();
	req.open('GET', url, true);
	req.onload = function(e) {
		if (req.readyState == 4) {
			if (req.status == 200) {
				//console.log(req.responseText);
        		response = JSON.parse(req.responseText);
        if (response) {
			
			console.log(url);
			//console.log(response.error.type);
			//First, check if the provided key is valid. Otherwise skip all the code and send a message to the Pebble
			if (response===undefined){
				Pebble.sendAppMessage({
						//Current conditions
						"city": "Your API Key is not valid",
				});
				
			}
			else
			{
			
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
				
					//probability of precipitation (%)
					pop = response.forecast.simpleforecast.forecastday[0].pop + "%";

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
				/*
					temperature = temperature.replace("-","- "); 
					high1 = high1.replace("-","- ");
					low1 = low1.replace("-","- ");
					high2 = high2.replace("-","- ");
					low2 = low2.replace("-","- ");
					high3 = high3.replace("-","- ");
					low3 = low3.replace("-","- ");
*/
				
					//console logs
					console.log("icon: " + icon + " temp: " + temperature + " city: " + city);
					console.log("today's high: " + high + " today's low: " + low);
					console.log("Rain Probability: " + pop);
					console.log("sunrise: " + sunrise + " sunset: " + sunset);
					console.log("wspeed unit: " + options["wspeed"]);
					console.log("wind speed: " + wind + " wind direction: " + wdirection);
					console.log("icon1: " + code1 + " high1: " + high1 + " low1: " + low1);
					console.log("icon2: " + code2 + " high2: " + high2 + " low2: " + low2);
					console.log("icon3: " + code3 + " high3: " + high3 + " low3: " + low3);
					console.log("start: " + parseInt(options["start"]) + " end: " + parseInt(options["end"]));
					console.log("display battery: " + (options["hide_bat"] == "true" ? 1 : 0));
					console.log("theme: " + (options.theme));

					//send the values to the Pebble!!
					Pebble.sendAppMessage({
						//Current conditions
						"icon":icon,
						"temperature":temperature, //Round the temperature
						"city":city,
						"theme": parseInt(options.theme),
						//User preferences
						"invert_color" : (options["invert_color"] == "true" ? 1 : 0),
						"language" : parseInt(options['language']),
						"vibes" : parseInt(options['vibes']),
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
						"backlight" : (options["backlight"] == "true" ? 1 : 0),
						"pop" : pop,
					//	"font" : parseInt(options['font']),
				  });
			}
			
        }
      } else {
        console.log("unable to get woeid from The Weather Underground API");
      }
    }
  }
  req.send(null);
}

//////////////////////
// open weather map //
//////////////////////
var owmk = "14d5ef44410ddbf8687a1f51d26234bf";

function openweatherByLatLong(latitude, longitude)
{
	
	var celsius = options['units'] == 'celsius';
	var units = "auto";
	var accuracy = options['accuracy']; 
	
	if (celsius){ units = "metric";}
	else{ units = "imperial";}
	
	var url = "http://api.openweathermap.org/data/2.5/weather?lat="+latitude+"&lon="+longitude+"&units="+units;
	console.log("openweather URL: " + url);
	
	var req = new XMLHttpRequest();
	req.open('GET', url, true);
	req.onload = function(e) {
		if (req.readyState == 4) {
			if (req.status == 200) {
				console.log(req.responseText);
        		response = JSON.parse(req.responseText);
        if (response) {
			
			
					
			//if user wants to display the Feels Like, override the temperature.
			temperature = Math.round(response.main.temp) + "\u00B0";
			
			icon = openweather[response.weather.id];
			high = Math.round(response.main.temp_max) + "\u00B0";
			low = Math.round(response.main.temp_min) + "\u00B0";
				
			
			sunrise = UNIX2Date(response.sys.sunrise);
			//remove 12h to properly format the 12h/24h mode in the watchface
			sunset = UNIX2Date(response.sys.sunset - 43200); 
			
			wind = response.wind.speed;
			
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
			
			wdirection = windDirection(response.wind.deg);
			
			//code1 = forecastio[response.daily.data[arrIndex+1].icon];
			//high1 = Math.round(response.daily.data[arrIndex+1].temperatureMax) + "\u00B0"
			//low1 = Math.round(response.daily.data[arrIndex+1].temperatureMin) + "\u00B0"
			//code2 = forecastio[response.daily.data[arrIndex+2].icon];
			//high2 = Math.round(response.daily.data[arrIndex+2].temperatureMax) + "\u00B0"
			//low2 = Math.round(response.daily.data[arrIndex+2].temperatureMin) + "\u00B0"
			//code3 = forecastio[response.daily.data[arrIndex+3].icon];
			//high3 = Math.round(response.daily.data[arrIndex+3].temperatureMax) + "\u00B0"
			//low3 = Math.round(response.daily.data[arrIndex+3].temperatureMin) + "\u00B0"
			
			
			//add a blank space between the - and the temp to better display
			/*
		
			temperature = temperature.replace("-","- "); 
			high1 = high1.replace("-","- ");
			low1 = low1.replace("-","- ");
			high2 = high2.replace("-","- ");
			low2 = low2.replace("-","- ");
			high3 = high3.replace("-","- ");
			low3 = low3.replace("-","- ");
			*/
			
			city = response.name;
			
			//console logs
			console.log("city: " + city);
			console.log("icon: " + icon + " temp: " + temperature);
			console.log("today's high: " + high + " today's low: " + low);
			console.log("sunrise: " + sunrise + " sunset: " + sunset);
			console.log("wind speed: " + wind + "wind direction: " + wdirection);
			//console.log("icon1: " + code1 + " high1: " + high1 + " low1: " + low1);
			//console.log("icon2: " + code2 + " high2: " + high2 + " low2: " + low2);
			//console.log("icon3: " + code3 + " high3: " + high3 + " low3: " + low3);
			console.log("start: " + parseInt(options["start"]) + " end: " + parseInt(options["end"]));
			console.log("display battery: " + (options["hide_bat"] == "true" ? 1 : 0));
			console.log("theme: " + (options.theme));
			
			//send the values to the Pebble!!
			Pebble.sendAppMessage({
				//Current conditions
				"icon":icon,
				"temperature":temperature, //Round the temperature
				"city":city, 
				"theme": parseInt(options.theme),
				//User preferences
				"invert_color" : (options["invert_color"] == "true" ? 1 : 0),
				"language" : parseInt(options['language']),
				"vibes" : parseInt(options['vibes']),
				//Forecast for the day
				"high":high,
				"low":low,
				"sunrise":sunrise,
				"sunset":sunset,
				"wind":wind.toString(),
				"wdirection" : wdirection,
				//3 days forecast data
				//"day1code":code1,
				//"day1H":high1,
				//"day1L":low1,
				//"day2code":code2,
				//"day2H":high2,
				//"day2L":low2,
				//"day3code":code3,
				//"day3H":high3,
				//"day3L":low3,
				//Extra Features
				"ESDuration":parseInt(options['ESDuration']),
				"timer":parseInt(options['timer']),
				"seconds":(options["seconds"] == "true" ? 1 : 0),
				"hourly_vibe":(options["hourly_vibe"] == "true" ? 1 : 0),
				"start":parseInt(options["start"]),
				"end":parseInt(options["end"]),
				"forecast":(options["forecast"] == "true" ? 1 : 0),
				"hide_bat" : (options["hide_bat"] == "true" ? 1 : 0),
				"backlight" : (options["backlight"] == "true" ? 1 : 0),
				"pop" : "N/A",
	
          });
			
		} else {
        console.log("unable to get woeid from The Weather Underground API");
      }
    }
  }
	}
  req.send(null);

}


/////////////////
// forecast.io //
/////////////////

var fiok = "810bdb86c6a46075245248c3e6c5b0d5";

function forecastioByLatLong(latitude, longitude)
{
	
	var celsius = options['units'] == 'celsius';
	var units = "auto";
	var accuracy = options['accuracy']; 
	
	if (celsius){ units = "si";}
	else{ units = "us";}
	
	var APIKey = options['CustomAPIKey'];
	
	//Developer wildcard ;-)
	if (APIKey == "qwerty1234"){APIKey = fiok;}
	
	var url = "https://api.forecast.io/forecast/"+APIKey+"/"+latitude+","+longitude+"?units="+units;
	console.log("forecast.io URL: " + url);
	
	var req = new XMLHttpRequest();
	req.open('GET', url, true);
	req.onload = function(e) {
		if (req.readyState == 4) {
			if (req.status == 200) {
				console.log(req.responseText);
        		response = JSON.parse(req.responseText);
        if (response) {
			
			
			//Get today's UNIX TIME
			var unixTime = Date.now() / 1000 | 0;
			var arrIndex;
			
			console.log("unix time: " + unixTime);
			
			//Get the correct array index based on UnixTime
			for (i = 0; 6; i++) {
				//console.log("iteration " + i + " response time: "+response.daily.data[i].time);
    			if (response.daily.data[i].time > unixTime){
					arrIndex = i;
					break;
				}
			}
			
			//fix the arrIndex for Mondays
			if(arrIndex <0) {arrIndex = 0;}
			//console.log ("arrIndex: " + arrIndex);
			
			//if user wants to display the Feels Like, override the temperature.
			if (options["feelslike"] == "true"){temperature = Math.round(response.currently.apparentTemperature) + "\u00B0";}
			else{temperature = Math.round(response.currently.temperature) + "\u00B0";}
			
			icon = forecastio[response.currently.icon];
			high = Math.round(response.daily.data[arrIndex].temperatureMax) + "\u00B0";
			low = Math.round(response.daily.data[arrIndex].temperatureMin) + "\u00B0"; 
			
			pop = Math.round(response.daily.data[arrIndex].precipProbability * 100) + "%";
				
			
			sunrise = UNIX2Date(response.daily.data[arrIndex].sunriseTime);
			//remove 12h to properly format the 12h/24h mode in the watchface
			sunset = UNIX2Date(response.daily.data[arrIndex].sunsetTime - 43200); 
			
			wind = response.currently.windSpeed;
			
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
			
			wdirection = windDirection(response.currently.windBearing);
			
			code1 = forecastio[response.daily.data[arrIndex+1].icon];
			high1 = Math.round(response.daily.data[arrIndex+1].temperatureMax) + "\u00B0"
			low1 = Math.round(response.daily.data[arrIndex+1].temperatureMin) + "\u00B0"
			code2 = forecastio[response.daily.data[arrIndex+2].icon];
			high2 = Math.round(response.daily.data[arrIndex+2].temperatureMax) + "\u00B0"
			low2 = Math.round(response.daily.data[arrIndex+2].temperatureMin) + "\u00B0"
			code3 = forecastio[response.daily.data[arrIndex+3].icon];
			high3 = Math.round(response.daily.data[arrIndex+3].temperatureMax) + "\u00B0"
			low3 = Math.round(response.daily.data[arrIndex+3].temperatureMin) + "\u00B0"
			
			
			//add a blank space between the - and the temp to better display
			/*
		
			temperature = temperature.replace("-","- "); 
			high1 = high1.replace("-","- ");
			low1 = low1.replace("-","- ");
			high2 = high2.replace("-","- ");
			low2 = low2.replace("-","- ");
			high3 = high3.replace("-","- ");
			low3 = low3.replace("-","- ");
			*/
			
			location = getLocationName(latitude +","+ longitude);
			
			if (accuracy==6){city = location[2];}
			if (accuracy==11){city = location[1];}
			if (accuracy==16){city = location[0];}
			
			//console logs
			console.log("city: " + city);
			console.log("icon: " + icon + " temp: " + temperature);
			console.log("today's high: " + high + " today's low: " + low);
			console.log("Rain Probability: " + pop);
			console.log("sunrise: " + sunrise + " sunset: " + sunset);
			console.log("wind speed: " + wind + "wind direction: " + wdirection);
			console.log("icon1: " + code1 + " high1: " + high1 + " low1: " + low1);
			console.log("icon2: " + code2 + " high2: " + high2 + " low2: " + low2);
			console.log("icon3: " + code3 + " high3: " + high3 + " low3: " + low3);
			console.log("start: " + parseInt(options["start"]) + " end: " + parseInt(options["end"]));
			console.log("display battery: " + (options["hide_bat"] == "true" ? 1 : 0));
			console.log("theme: " + (options.theme));
			
			//send the values to the Pebble!!
			Pebble.sendAppMessage({
				//Current conditions
				"icon":icon,
				"temperature":temperature, //Round the temperature
				"city":city, 
				"theme": parseInt(options.theme),
				//User preferences
				"invert_color" : (options["invert_color"] == "true" ? 1 : 0),
				"language" : parseInt(options['language']),
				"vibes" : parseInt(options['vibes']),
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
				"start":parseInt(options["start"]),
				"end":parseInt(options["end"]),
				"forecast":(options["forecast"] == "true" ? 1 : 0),
				"hide_bat" : (options["hide_bat"] == "true" ? 1 : 0),
				"backlight" : (options["backlight"] == "true" ? 1 : 0),
				"pop" : pop,
	
          });
			
		} else {
        console.log("unable to get woeid from The Weather Underground API");
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
	console.log("Retrieving WOEID");
  var response;
  var woeid = -1;
  var accuracy = options['accuracy']; 
  var query = encodeURI("select woeid, county, city, street from geo.placefinder where text=\"" + latitude + "," + longitude +"\" and gflags=\"R\"");
  console.log("geo query: " + query);
  var url = "http://query.yahooapis.com/v1/public/yql?q=" + query + "&format=json";
	console.log("fetching woeid from yahoo: " + url);
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
			
			console.log("Call GetWeatherFromWoeid: woeid=" + woeid + " and city=" + city);
			getWeatherFromWoeid(woeid, city);
        }
      } else {
        console.log("unable to get woeid from Yahoo! API");
      }
    }
  }
  req.send(null);
}



//Retrieve the WOEID & City name from Yahoo! when GPS is OFF
function getWeatherFromLocation(location_name) {
	
//check the weather provider to define how to proceed

	//The Weather Underground
	if(options['weatherprovider']=="1"){
		console.log("Getting weather from TWU");
		var position;
		//get the GPS coordinates based on the location and invoke the weather service
		position = getPosition(location_name);
		
		//get the weather
		TWUFromLarLong(position[0],position[1]);
		
	}
	//forecast.io
	else if (options['weatherprovider']=="2"){
		console.log("Getting weather from forecast.io");
		var position;
		//get the GPS coordinates based on the location and invoke the weather service
		position = getPosition(location_name);
		
		//get the weather
		forecastioByLatLong(position[0],position[1]);
		
	}
	//Yahoo! Weather	
	else{
		  console.log("Getting weather from Yahoo Weather");
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

					console.log("Call GetWeatherFromWoeid: woeid=" + woeid + " and city=" + city);
					getWeatherFromWoeid(woeid, city);
				}
			  } else {
				console.log("unable to get woeid from Yahoo! API");
			  }
			}
		  }
		  req.send(null);
	}

}

//Retrieves the Weather data from Yahoo! Weather//
function getWeatherFromWoeid(woeid, city) {
	
	/*if Hong Kong then override the woeid with a valid one*/
	if (woeid ==24865698){woeid=12467924};
	/*if Ottawa the override the woeid with a valid one*/
	if (woeid ==91982014){woeid=29375164};
	
  var celsius = options['units'] == 'celsius';
	
	console.log("Getting Weather from Woeid (Yahoo Weather)");
	
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
			/*
			temperature = temperature.replace("-","- "); 
			high1 = high1.replace("-","- ");
			low1 = low1.replace("-","- ");
			high2 = high2.replace("-","- ");
			low2 = low2.replace("-","- ");
			high3 = high3.replace("-","- ");
			low3 = low3.replace("-","- ");
			*/
			
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
			console.log("theme: " + (options.theme));
			
			//send the values to the Pebble!!
			Pebble.sendAppMessage({
				//Current conditions
				"icon":icon,
				"temperature":temperature,
				"city":city,
				"theme": parseInt(options.theme),
				//User preferences
				"invert_color" : (options["invert_color"] == "true" ? 1 : 0),
				"language" : parseInt(options['language']),
				"vibes" : parseInt(options['vibes']),
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
				"backlight" : (options["backlight"] == "true" ? 1 : 0),
				"pop" : "N/A",
			//	"font" : parseInt(options['font']),
          });
          
          console.log("data sent to Pebble");
        }
      } else {
        console.log("Error WFW");
      }
    }
  }
  req.send(null);
}


function getPosition(cityname){
	
	cityname = encodeURIComponent(cityname);
	var url = "http://maps.googleapis.com/maps/api/geocode/json?address=[" + cityname.replace(" ","%20") + "]";
	console.log("get positon URL: " + url);
	var response;
	var req = new XMLHttpRequest();
	req.open('GET', url, false);
	req.setRequestHeader("Content-Type", "text/plain;charset=UTF-8");
	req.send();

		if (req.readyState == 4) {
			if (req.status == 200) {
				response = JSON.parse(req.responseText);
				if (response) {
					//var position = new Array({'lat' : response.results[0].geometry.location.lat,
					//						'long' : response.results[0].geometry.location.lng});

					var position = new Array(2);
					position[0] = response.results[0].geometry.location.lat;
					position[1] = response.results[0].geometry.location.lng;
					position[2] = response.results[0].geometry.location.lat + ',' + response.results[0].geometry.location.lng;
					//console.log("ya he rellenado el array y voy a leerlo");
					console.log("latitude: " + position[0]);
					console.log("longitude: " + position[1]);
					console.log("position: " + position[2]);
					return position;
					}
				}
			}

}


//Retrieve the weather based on the selected settings (GPS on/off)
var locationOptions = { enableHighAccuracy: false,
  						maximumAge: 0};


function updateWeather() {
  if (options['use_gps'] == "true") {
	console.log("Getting GPS current position");
    window.navigator.geolocation.getCurrentPosition(locationSuccess,
                                                    locationError,
                                                    locationOptions);
  } else {
	console.log("getting weather from manual location: " + options["location"]); 
    getWeatherFromLocation(options["location"]);
  }
}

function locationSuccess(pos) {
  var coordinates = pos.coords;
  console.log("location success");
	
	//set the options for the last seen
	//if (options['find']=="true"){options['latlong']=coordinates.latitude+","+coordinates.longitude;}
	//if not enabled, then set the last seen to the Pebble Technology HQ ;)
	//else{options['latlong']="37.440392,-122.158672";}

	//call the weather function based on the selected provider (defaulted to Yahoo! Weather)
	if (options['weatherprovider']=="1"){TWUFromLarLong(coordinates.latitude, coordinates.longitude);}
	else if (options['weatherprovider']=="2"){forecastioByLatLong(coordinates.latitude, coordinates.longitude);}
	else if (options['weatherprovider']=="3"){openweatherByLatLong(coordinates.latitude, coordinates.longitude);}
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

function CheckUserKey()
{
	var lt = 0;
	var key = options['key'];
	var token = Pebble.getAccountToken();
	var decrypt;
	var app = 1; //1 means YWeather.
	
	//if there is not user key, then license is 0
	if ((key==undefined)||(key==null)||(key=="")||(key=="undefined")||(key=="false")){key="00000000000"}
	//check the user key
	
	if (key.length = 11) {
		//old key; use original decrypt mode
		decrypt = token.substring(1,2) + token.substring(2,3) + token.substring(2,3) + token.substring(14,15) + token.substring(10,11);
		decrypt = decrypt + key.substring(3,4);
		decrypt = decrypt + token.substring(0,1) + token.substring(6,7) + token.substring(5,6) + token.substring(3,4) + token.substring(9,10)
	}

	else {
		//invalid key... what is this?
		decrypt = "999999999999";
	}
	

	if (decrypt == key) {lt = key.substring(5,6);}
	else {lt = 0;}
	
	//confirm that the javascript code works fine
	//options['key']=decrypt;

	
	console.log("Key: " + key + " Decrypt: " + decrypt + " LT: " + lt);
	
	return lt;
}


function getLocationName(pos){
	
	var url = "http://maps.googleapis.com/maps/api/geocode/json?latlng=" + pos + "";
	console.log("get location URL: " + url);
	var response;
	var req = new XMLHttpRequest();
	req.open('GET', url, false);
	req.send();

		if (req.readyState == 4) {
			if (req.status == 200) {
				response = JSON.parse(req.responseText);
				if (response) {
					//var position = new Array({'lat' : response.results[0].geometry.location.lat,
					//						'long' : response.results[0].geometry.location.lng});

					var location = response.results[0].formatted_address;
					console.log("Street: " + location);
					return location;
					}
				}
			}
}

///////////////////////////////////////
//Setup the connection with the watch//
///////////////////////////////////////


//Displays the configuration page in the phone
Pebble.addEventListener('showConfiguration', function(e) {
	
	//Set default values
	var optlanguage =  options['language'];
	if ((optlanguage ==null)||(optlanguage == "null")){optlanguage = 100;} //set to english if null

	var optgps = options['use_gps'];
	if ((optgps == null)||(optgps=="null")){optgps = "true";}

	var optlocation = options['location'];
	if ((optlocation == null)||(optlocation=="null")){optlocation="";}
	
	var optunits = options['units'];
	if ((optunits == null)||(optunits=="null")){optunits = "celsius";}
	
	var optinvert = options['invert_color'];
	if ((optinvert == null)||(optinvert=="null")){optinvert = "false";}
	
	var optvibes = options['vibes'];
	if ((optvibes==null)||(optvibes=="null")) {optvibes = 0;}
	
	var optaccuracy = options['accuracy'];
	if ((optaccuracy==null)||(optaccuracy=="null")){optaccuracy=16;}
	
	var optfeelslike = options['feelslike'];
	if ((optfeelslike ==null)||(optfeelslike=="null")){optfeelslike = "false";}
	
	var optESDuration = options['ESDuration'];
	if ((optESDuration == null)||(optESDuration=="null")){optESDuration = 5;}
	
	var optwspeed = options['wspeed'];
	if ((optwspeed == null)||(optwspeed=="null")){optwspeed = "0";}
	
	var optstart = options['start'];
	if ((optstart == null)||(optstart == "null")) {optstart="0";}
	
	var optend = options['end'];
	if((optend ==null)||(optend=="null")){optend ="0";}
	
	var opttimer = options['timer'];
	if ((opttimer == null)||(opttimer=="null")){opttimer=30;}
	
	var opthvibe = options['hourly_vibe'];
	if ((opthvibe == null)||(opthvibe=="null")){opthvibe="false";}
	
	var optalert = options['alerts'];
	if((optalert == null)||(optalert=="null")){optalert = "false";}
	
	var optseconds = options['seconds'];
	if ((optseconds == null)||(optseconds=="null")){optseconds = "false";}
	
	var optforecast = options['forecast'];
	if ((optforecast == null)||(optforecast=="null")){optforecast = "false";}
	
	var optprovider = options['weatherprovider'];
	if ((optprovider == null)||(optprovider=="null")){optprovider = "0";}
	
	var opthidebat = options['hide_bat'];
	if ((opthidebat == null)||(opthidebat =="null")){opthidebat="false";}
	
	var optbacklight = options['backlight'];
	if ((optbacklight==null)||(optbacklight=="null")){optbacklight = "false";}
	
	var optcustomapikey = options['CustomAPIKey'];
	if ((optcustomapikey==null)||(optcustomapikey=="null")){optcustomapikey = ""}
	
	var optkey = options['key'];
	if ((optkey == null)||(optkey=="null")){optkey="";}
	
	var optTheme = options['theme'];
	if ((optTheme == null)||(optTheme=="null")){optTheme="1";}
	
 
	var uri = 'http://dabdemon.github.io/Yahoo--Weather/development.html?' + //Here you need to enter your configuration webservice
    //var uri = 'http://yweather.es/ywsettings.html?' + 
	'language=' + encodeURIComponent(optlanguage) +
	'&theme=' + encodeURIComponent(optTheme) +
	'&use_gps=' + encodeURIComponent(optgps) +
  '&location=' + encodeURIComponent(optlocation) +
  '&units=' + encodeURIComponent(optunits) +
  '&invert_color=' + encodeURIComponent(optinvert) +
	'&vibes=' + encodeURIComponent(optvibes) +
	'&accuracy=' + encodeURIComponent(optaccuracy) +
	'&feelslike=' + encodeURIComponent(optfeelslike) +
	'&ESDuration=' + encodeURIComponent(optESDuration) +
	'&wspeed=' + encodeURIComponent(optwspeed) +	
	'&start=' + encodeURIComponent(optstart) +	
	'&end=' + encodeURIComponent(optend) +	
	'&timer=' + encodeURIComponent(opttimer) +
	'&UUID=' + encodeURIComponent(Pebble.getAccountToken()) +
	'&lt=' + encodeURIComponent(CheckUserKey()) +
	'&key=' + encodeURIComponent(optkey) +
	'&hourly_vibe=' + encodeURIComponent(opthvibe) +
	'&alerts=' + encodeURIComponent(optalert) +
	'&seconds=' + encodeURIComponent(optseconds) +
	'&weatherprovider=' + encodeURIComponent(optprovider) +
	'&CustomAPIKey=' + encodeURIComponent(optcustomapikey) +
	'&hide_bat=' + encodeURIComponent(opthidebat) +
	'&backlight=' + encodeURIComponent(optbacklight) +
	'&forecast=' + encodeURIComponent(optforecast);

	console.log('showing configuration at uri: ' + uri);
  	Pebble.openURL(uri);
	
});

//Retrieve user settings after submitting
Pebble.addEventListener('webviewclosed', function(e) {
  if (e.response) {
    options = JSON.parse(decodeURIComponent(e.response));
	  //clear the cached data
	  console.log("clearing cached data...");
	  localStorage.clear();
	  //save the new options
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

