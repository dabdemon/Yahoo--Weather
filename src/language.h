#pragma once
#include <pebble.h>
//*********************//
// DEFINE THE WEEKDAYS //
//*********************// 
// Custom ASIAN FONT:  1234567890零号一二三四五六七八九十星期天月曜日火水木金土日


static const char *chinese_numbers[]={
	//日 is concatenated at the end of the number to express it is a month day
	"零", // 0 - líng
	"一日", // 1 - yī
	"二日", // 2 - èr
	"三日", // 3 - sān
	"四日", // 4 - sì
	"五日", // 5 - wǔ
	"六日", // 6 - liù
	"七日", // 7 - qī
	"八日", // 8 - bā
	"九日", // 9 - jiǔ
	"十日", // 10 - shí
	"十一日", // 11 - shí yī (10+1)
	"十二日", // 12 - shí èr (10+2)
	"十三日", // 13 - shí sān
	"十四日", // 14 - shí sì
	"十五日", // 15 - shí wǔ
	"十六日", // 16 - shí liù
	"十七日", // 17 - shí qī
	"十八日", // 18 - shí bā
	"十九日", // 19 - shí jiǔ
	"二十日", // 20 - èr shí (2*10)
	"二十一日", // 21 - èr shí yī (2*10+1)
	"二十二日", // 22 - èr shí èr
	"二十三日", // 23 - èr shí sān
	"二十四日", // 24 - èr shí sì
	"二十五日", // 25 - èr shí wǔ
	"二十六日", // 26 - èr shí liù
	"二十七日", // 27 - èr shí qī
	"二十八日", // 28 - èr shí bā
	"二十九日", // 29 - èr shí jiǔ
	"三十日", // 30 - sān shí (3*10)
	"三十一日", // 31 - sān shí yī (3*10+1)
};

static const char *japanese_numbers[]={
	//add 日 after the number to express it is a week day
	"0",
	"1日",
	"2日",
	"3日",
	"4日",
	"5日",
	"6日",
	"7日",
	"8日",
	"9日",
	"10日",
	"11日",
	"12日",
	"13日",
	"14日",
	"15日",
	"16日",
	"17日",
	"18日",
	"19日",
	"20日",
	"21日",
	"22日",
	"23日",
	"24日",
	"25日",
	"26日",
	"27日",
	"28日",
	"29日",
	"30日",
	"31日",
};

static const char *WEEKDAYS[] = {
	"NULL",
	//ENGLISH - 0
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday",
	//SPANISH - 1
	"Lunes",
	"Martes",
	"Miércoles",
	"Jueves",
	"Viernes",
	"Sábado", 
	"Domingo", 
	//ITALIAN - 2
	"Lunedi",
	"Martedi",
	"Mercoledi", 
	"Giovedi", 
	"Venerdi", 
	"Sabato", 
	"Domenica", 
	//GERMAN - 3
	"Montag", 
	"Dienstag", 
	"Mittwoch", 
	"Donnerstag", 
	"Freitag", 
	"Samstag", 
	"Sonntag",
	//CZECH - 4
	"Pondělí",
	"Úterý", 
	"Streda", 
	"Čtvrtek", 
	"Pátek", 
	"Sobota", 
	"Neděle", 
	//FRENCH - 5
	"Lundi",
	"Mardi", 
	"Mercredi",
	"Jeudi", 
	"Vendredi", 
	"Samedi", 
	"Dimanche", 
	//PORTUGUESE - 6
	"Segunda", 
	"Terça", 
	"Quarta",
	"Quinta", 
	"Sexta", 
	"Sábado", 
	"Domingo", 
	//FINNISH - 7
	"Maanantai", 
	"Tiistai", 
	"Keskiviikko",
	"Torstai", 
	"Perjantai",
	"Lauantai",
	"Sunnuntai", 
	//DUTCH - 8
	"Maandag", 
	"Dinsdag", 
	"Woensdag", 
	"Donderdag",
	"Vrijdag", 
	"Zaterdag", 
	"Zondag", 
	//POLISH - 9
	"Poniedzialek",
	"Wtorek", 
	"Sroda", 
	"Czwartek",
	"Piątek", 
	"Sobota",
	"Niedziela",
	//SWEDISH - 10
	"Måndag",
	"Tisdag", 
	"Onsdag", 
	"Torsdag", 
	"Fredag", 
	"Lördag",
	"Söndag ",
	//DANISH - 11
	"Mandag",
	"Tirsdag",
	"Onsdag",
	"Torsdag",
	"Fredag", 
	"Lørdag",
	"Søndag ",
	//CATALAN - 12
	"Dilluns", 
	"Dimarts",
	"Dimecres", 
	"Dijous", 
	"Divendres",
	"Dissabte",
	"Diumenge ",
	//HUNGARIAN - 13
	"Hétfo",
	"Kedd", 
	"Szerda",
	"Csütörtök",
	"Péntek", 
	"Szombat",
	"Vasárnap", 
	//NORWEGIAN - 14
	"Mandag",
	"Tirsdag",
	"Onsdag",
	"Torsdag",
	"Fredag", 
	"Lørdag",
	"Søndag ",  
	//TURKISH - 15
	"Pazartesi",
	"Salı",
	"Çarsamba",
	"Persembe",
	"Cuma",
	"Cumartesi",
	"Pazar",
	//SLOVAK - 16
	"Pondelok", 
	"Utorok", 
	"Streda", 
	"Stvrtok", 
	"Piatok", 
	"Sobota", 
	"Nedela",
	//ROMANIAN - 17
	"Luni", 
	"Marti", 
	"Miercuri", 
	"Joi", 
	"Vineri", 
	"Sâmbătă", 
	"Duminică",
	//RUSSIAN - 18
	"PonedelÝnik",//"Понедельник",
	"Vtornik",//"Вторник",
	"Sreda",//"Среда",
	"^etverg",//"Четверг",
	"PÔtnica",//"Пятница",
	"Subbota",//"Суббота",
	"VoskresenÝe",//"Воскресенье",

	//CHINESE - 19
	"星期一", //Monday
	"星期二", //Tuesday
	"星期三", //Wednesday
	"星期四", //Thursday
	"星期五", //Friday
	"星期六", //Saturday
	"星期天", //Sunday
/*
	//JAPANESE (KANA)- 20
	"げつようび", //Monday
	"かようび",  //Tuesday
	"すいようび", //Wednesday
	"もくようび", //Thursday
	"きんようび", //Friday
	"どようび", //Saturday
	"にちようび", //Sunday
*/
	//JAPANESE (KANJI) - 20
	"月曜日", //Monday
	"火曜日", //Tuesday
	"水曜日", //Wednesday
	"木曜日", //Thursday
	"金曜日", //Friday
	"土曜日", //Saturday
	"日曜日", //Sunday

	/*
	"Понедельник",
	"Вторник",
	"Среда",
	"Четверг",
	"Пятница",
	"Суббота",
	"Воскресенье",
	*/
};

static const char *MONTHS[] = {
	NULL,
	//ENGLISH - 0
	" january",
	" february",
	" march",
	" april",
	" may",
	" june",
	" july",
	" august",
	" september",
	" october",
	" november",
	" december",
	 //SPANISH - 1
	" enero",
	" febrero",
	" marzo",
	" abril",
	" mayo",
	" junio",
	" julio",
	" agosto", 
	" septiembre",
	" octubre", 
	" noviembre", 
	" diciembre", 
	//ITALIAN - 2
	" gennaio", 
	" febbraio",
	" marzo",
	" aprile",
	" maggio",
	" giugno",
	" luglio",
	" agosto",
	" settembre",
	" ottobre",
	" novembre",
	" dicembre",
	//GERMAN - 3
	".Januar",
	".Februar",
	".März",
	".April",
	".Mai", 
	".Juni", 
	".Juli", 
	".August",
	".September",
	".Oktober",
	".November",
	".Dezember",
	//CZECH - 4
	"Leden ",
	"Únor ",
	"Brezen ",
	"Duben ", 
	"Květen ", 
	"Červen ",
	"Červenec ", 
	"Srpen ",
	"Zárí ",
	"Ríjen ",
	"Listopad ",
	"Prosinec ",
	//FRENCH - 5
	" janvier",
	" février", 
	" mars", 
	" avril", 
	" mai", 
	" juin", 
	" juillet", 
	" août", 
	" septembre", 
	" octobre",
	" novembre", 
	" décembre", 
	//PORTUGUESE - 6
	" Janeiro", 
	" Fevereiro", 
	" Março", 
	" Abril",
	" Maio",
	" Junho",
	" Julho",
	" Agosto",
	" Setembro",
	" Outubro",
	" Novembro",
	" Dezembro",
	//FINNISH - 7
	". Tammikuu",
	". Helmikuu", 
	". Maaliskuu",
	". Huhtikuu", 
	". Toukokuu", 
	". Kesäkuu", 
	". Heinäkuu", 
	". Elokuu", 
	". Syyskuu", 
	". Lokakuu", 
	". Marraskuu", 
	". Joulukuu", 
	//DUTCH - 8
	" Januari", 
	" Februari",
	" Maart",
	" April",
	" Mei", 
	" Juni", 
	" Juli", 
	" Augustus", 
	" September", 
	" Oktober", 
	" November",
	" December", 
	//POLISH - 9
	" stycznia",
	" lutego", 
	" marca", 
	" kwietnia", 
	" maja", 
	" czerwca",
	" lipca", 
	" sierpnia",
	" wrzesnia",
	" pazdziernika",
	" listopada", 
	" grudnia", 
	//SWEDISH - 10
	" Januari", 
	" Februari",
	" Mars", 
	" April", 
	" Maj", 
	" Juni",
	" Juli", 
	" Augusti",
	" September", 
	" Oktober",
	" November", 
	" December", 
	//DANISH - 11
	". Januar",
	". Februar", 
	". Marts", 
	". April", 
	". Maj", 
	". Juni", 
	". Juli",
	". August",
	". September", 
	". Oktober", 
	". November",
	". December",
	//CATALAN - 12
	" Gener", 
	" Febrer", 
	" Març", 
	" Abril", 
	" Maig", 
	" Juny",
	" Juliol", 
	" Agost", 
	" Setembre", 
	" Octubre", 
	" Novembre", 
	" Desembre", 
	//HUNGARIAN - 13
	"január ", 
	"február ", 
	"március ",
	"április ", 
	"május ", 
	"június ", 
	"július ", 
	"augusztus ", 
	"szeptember ", 
	"október ",
	"november ", 
	"december ", 
	//NORWEGIAN - 14
	". januar", 
	". februar", 
	". mars", 
	". april", 
	". mai", 
	". juni", 
	". juli", 
	". august", 
	". september", 
	". oktober", 
	". november", 
	". desember", 
	//TURKISH - 15
	" Ocak",
	" Subat",
	" Mart",
	" Nisan",
	" Mayıs",
	" Haziran",
	" Temmuz",
	" Ağustos",
	" Eylül",
	" Ekim",
	" Kasım",
	" Aralık",
	//SLOVAK - 16
	". Januar", 
	". Februar", 
	". Marec", 
	". April", 
	". Maj", 
	". Jun", 
	". Jul", 
	". August", 
	". September", 
	". Oktober", 
	". November", 
	". December",
	//ROMANIAN - 17
	" Ianuarie",
	" Februarie",
	" Martie",
	" Aprilie",
	" Mai",
	" Iunie",
	" Iulie",
	" August",
	" Septembrie",
	" Octombrie",
	" Noiembrie",
	" Decembrie",
	//RUSSIAN - 18
	" ÂnvarÔ",//" ÂnvarÝ",//" Январь",
	" FevralÔ",//" FevralÝ",//" Февраль",
	" Marta",//" Mart",//" Март",
	" AprelÔ",//" AprelÝ",//" Апрель",
	" MaÔ",//" Maÿ",//" Май",
	" I¥nÔ",//" I¥nÝ",//"Июнь",
	" I¥lÔ",//" I¥lÝ",//" Июль",
	" Avgusta",//" Avgust",//" Август",
	" SentÔbrÔ",//" SentÔbrÝ",//" Сентябрь",
	" OktÔbrÔ",//" OktÔbrÝ",//" Октябрь",
	" NoÔbrÔ",//" NoÔbrÝ",//" Ноябрь",
	" DekabrÔ",//" DekabrÝ",//" Декабрь",

	//CHINESE - 19
/*
	"一月 ", //January
	"二月 ", //February 
	"三月 ", //March
	"四月 ", //April
	"五月 ", //May
	"六月 ", //June
	"七月 ", //July
	"八月 ", //August
	"九月 ", //September
	"十月 ", //October
	"十一月 ", //November
	"十二月 ", //December
*/
	"1月 ", //January
	"2月 ", //February
	"3月 ", //March
	"4月 ", //April
	"5月 ", //May
	"6月 ", //June
	"7月 ", //July
	"8月 ", //August
	"9月 ", //September
	"10月 ", //October
	"11月 ", //November
	"12月 ", //December
/*
	//JAPANESE (KANA) - 20
	"いちがつ", //January
	"にがつ", //February
	"さんがつ", //March
	"しがつ", //April
	"ごがつ", //May
	"ろくがつ", //June
	"しちがつ", //July
	"はちがつ", //August
	"くがつ", //September
	"じゅうがつ", //October
	"じゅういちがつ", //November
	"じゅうにがつ", //December
*/
	//JAPANESE (KANJI)- 20
	"1月 ", //January
	"2月 ", //February
	"3月 ", //March
	"4月 ", //April
	"5月 ", //May
	"6月 ", //June
	"7月 ", //July
	"8月 ", //August
	"9月 ", //September
	"10月 ", //October
	"11月 ", //November
	"12月 ", //December

	/*
	" Январь",
	" Февраль",
	" Март",
	" Апрель",
	" Май",
	" Июнь",
	" Июль",
	" Август",
	" Сентябрь",
	" Октябрь",
	" Ноябрь",
	" Декабрь",
	*/
};

//On Round devices, the 3 day forecast uses the 3 char short dates. If we shrink the long weekday to 3 chars special accents are failing (like Mié or Sáb).
//Until I found a more fancy way to do this on C, I will create a PBL_ROUND specific 3 char array.
#ifdef PBL_ROUND 
static const char *short_weekdays[] = {
	"NULL",
	//ENGLISH - 0
	"MON",
	"TUE",
	"WED",
	"THU",
	"FRI",
	"SAT",
	"SUN",
	//SPANISH - 1
	"LUN",
	"MAR",
	"MIE",
	"JUE",
	"VIE",
	"SAB", 
	"DOM", 
	//ITALIAN - 2
	"LUN",
	"MAR",
	"MER", 
	"GIO", 
	"VEN", 
	"SAB", 
	"DOM", 
	//GERMAN - 3
	"MON", 
	"DIE", 
	"MIT", 
	"DON", 
	"FRE", 
	"SAM", 
	"SON",
	//CZECH - 4
	"PON",
	"UTE", 
	"STR", 
	"CTV", 
	"PAT", 
	"SOB", 
	"NED", 
	//FRENCH - 5
	"LUN",
	"MAR", 
	"MER",
	"JEU", 
	"VEN", 
	"SAM", 
	"DIM", 
	//PORTUGUESE - 6
	"SEG", 
	"TER", 
	"QUA",
	"QUI", 
	"SEX", 
	"SAB", 
	"DOM", 
	//FINNISH - 7
	"MAA", 
	"TII", 
	"KES",
	"TOR", 
	"PER",
	"LAU",
	"SUN", 
	//DUTCH - 8
	"MAA", 
	"DIN", 
	"WOE", 
	"DON",
	"VRI", 
	"ZAT", 
	"ZON", 
	//POLISH - 9
	"PON",
	"WTO", 
	"SRO", 
	"CZW",
	"PIA", 
	"SOB",
	"NIE",
	//SWEDISH - 10
	"MAN",
	"TIS", 
	"ONS", 
	"TOR", 
	"FRE", 
	"LOR",
	"SON",
	//DANISH - 11
	"MAN",
	"TIR",
	"ONS",
	"TOR",
	"FRE", 
	"LOR",
	"SON",
	//CATALAN - 12
	"DIL", 
	"DIM",
	"DIM", 
	"DIJ", 
	"DIV",
	"DIS",
	"DIU ",
	//HUNGARIAN - 13
	"HET",
	"KED", 
	"SZE",
	"CSU",
	"PEN", 
	"SZO",
	"VAS", 
	//NORWEGIAN - 14
	"MAN",
	"TIR",
	"ONS",
	"TOR",
	"FRE", 
	"LOR",
	"SON",  
	//TURKISH - 15
	"PAZ",
	"SAL",
	"CAR",
	"PER",
	"CUM",
	"CUM",
	"PAZ",
	//SLOVAK - 16
	"PON", 
	"UTO", 
	"STR", 
	"STV", 
	"PIA", 
	"SOB", 
	"NED",
	//ROMANIAN - 17
	"LUN", 
	"MAR", 
	"MIE", 
	"JOI", 
	"VIN", 
	"SAM", 
	"DUM",
	//RUSSIAN - 18
	"Pon",//"Понедельник",
	"Vto",//"Вторник",
	"Sre",//"Среда",
	"^et",//"Четверг",
	"PÔt",//"Пятница",
	"Sub",//"Суббота",
	"Vos",//"Воскресенье",

	//CHINESE - 19
	"MON", //Monday
	"TUE", //Tuesday
	"WED", //Wednesday
	"THU", //Thursday
	"FRI", //Friday
	"SAT", //Saturday
	"SUN", //Sunday

	//JAPANESE (KANJI) - 20
	"MON", //Monday
	"TUE", //Tuesday
	"WED", //Wednesday
	"THU", //Thursday
	"FRI", //Friday
	"SAT", //Saturday
	"SUN", //Sunday
};
#endif
	

char* translateDay(int weekday, int language, bool pblRound);
char* translateMonth(int month, int language);
