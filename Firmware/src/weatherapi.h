#ifndef __WEATHER_H
#define __WEATHER_H

#include <Arduino.h>

#include "userkeys.h"
#include "weathercolors.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include "Time.h"
#include "OpenWeatherMap.h"

const char *ow_key = OWM_API_KEY;
const char *nodename = "esp8266-weather";
const char *wifi_ssid = WIFI_SSID;
const char *wifi_passwd = WIFI_PW;

sint16_t temperatures[40];

typedef enum wifi_s {
  W_AP = 0, W_READY, W_TRY
} WifiStat;

OWMconditions      owCC;
OWMfiveForecast    owF5;
OWMsixteenForecast owF16;
WifiStat           WF_status;

void connectWiFiInit(void) {
  WF_status  = W_TRY;
  WiFi.hostname(nodename);
  String ssid   = wifi_ssid;
  String passwd = wifi_passwd;
  WiFi.begin(ssid.c_str(), passwd.c_str());
}

String dateTime(String timestamp) {
  time_t ts = timestamp.toInt();
  char buff[30];
  sprintf(buff, "%2d:%02d %02d-%02d-%4d", hour(ts), minute(ts), day(ts), month(ts), year(ts));
  return String(buff);
}

void currentConditions(void) {
  OWM_conditions *ow_cond = new OWM_conditions;
  owCC.updateConditions(ow_cond, ow_key, OWM_COUNTRY, OWM_CITY, "metric");
  Serial.print("Latitude & Longtitude: ");
  Serial.print("<" + ow_cond->longtitude + " " + ow_cond->latitude + "> @" + dateTime(ow_cond->dt) + ": ");
  Serial.println("icon: " + ow_cond->icon + ", " + " temp.: " + ow_cond->temp + ", press.: " + ow_cond->pressure);
  delete ow_cond;
}

void fiveDayFcast(void) {
  OWM_fiveForecast *ow_fcast5 = new OWM_fiveForecast[40];
  byte entries = owF5.updateForecast(ow_fcast5, 40, ow_key, OWM_COUNTRY, OWM_CITY, "metric");
  Serial.print("Entries: "); Serial.println(entries+1);
  for (byte i = 0; i <= entries; ++i) {
    Serial.print(dateTime(ow_fcast5[i].dt) + ": icon: ");
    Serial.print(ow_fcast5[i].icon + ", temp.: [" + ow_fcast5[i].t_min + ", " + ow_fcast5[i].t_max + "], p=" + ow_fcast5[i].pressure);
    Serial.print(", " + ow_fcast5[i].id + " = " + ow_fcast5[i].description + ":: " + ow_fcast5[i].cond + " " + ow_fcast5[i].cond_value);
    Serial.println();
    // Serial.print("\t" + ( + ow_fcast5[i].t_max.toInt()) / 2);
    Serial.println((int)round((ow_fcast5[i].t_min.toFloat() + ow_fcast5[i].t_max.toFloat()) / 2));
    Serial.println();
  }
  delete[] ow_fcast5;
}

void sixteedDayFcast(void) {
  OWM_sixteenLocation *location   = new OWM_sixteenLocation;
  OWM_sixteenForecast *ow_fcast16 = new OWM_sixteenForecast[7];
  byte entries = owF16.updateForecast(location, ow_fcast16, 7, ow_key, OWM_COUNTRY, OWM_CITY, "metric");
  Serial.print("Entries: "); Serial.println(entries+1);
  Serial.print(location->city_name + ", " + location->country +"(" + location->city_id);
  Serial.println(") <" + location->longtitude + ", " + location->latitude + "> :");
  for (byte i = 0; i <= entries; ++i) {
    Serial.print(dateTime(ow_fcast16[i].dt) + ": icon: ");
    Serial.print(ow_fcast16[i].icon + ", temp.: ");
    Serial.print("{" + ow_fcast16[i].t_min + ", " + ow_fcast16[i].t_max + "}, temp. change: ");
    Serial.print(ow_fcast16[i].t_night + " -> " + ow_fcast16[i].t_morning + " -> " + ow_fcast16[i].t_day + " -> " + ow_fcast16[i].t_evening);
    Serial.println("; pressure: " + ow_fcast16[i].pressure + ", descr.:" + ow_fcast16[i].description);
  }
  delete location;
  delete[] ow_fcast16;
}

OWM_fiveForecast *ow_fcast5;
byte entries;

void get5DayForecast() {
  Serial.print("Getting Forecast... ");
  ow_fcast5 = new OWM_fiveForecast[40];
  entries = owF5.updateForecast(ow_fcast5, 40, ow_key, OWM_COUNTRY, OWM_CITY, "metric");
  Serial.println("Done!");
}

void getTemperatures(sint16_t *buf) {
  for (byte i = 0; i <= entries; ++i) {
    buf[i] = (int)round(ow_fcast5[i].temp.toFloat()); // <- AVERAGE OF MIN AND MAX! IS THIS OK?
    // buf[i] = (int)round((ow_fcast5[i].t_min.toFloat() + ow_fcast5[i].t_max.toFloat()) / 2); // <- AVERAGE OF MIN AND MAX! IS THIS OK?
  }
}

void getIcons(sint16_t *buf) {
  // OWM_fiveForecast *ow_fcast5 = new OWM_fiveForecast[40];
  // byte entries = owF5.updateForecast(ow_fcast5, 40, ow_key, OWM_COUNTRY, OWM_CITY, "metric");
  for (byte i = 0; i <= entries; ++i) {
    buf[i] = ow_fcast5[i].icon.toInt();
  }
}

void getIds(sint16_t *buf) {
  // OWM_fiveForecast *ow_fcast5 = new OWM_fiveForecast[40];
  // byte entries = owF5.updateForecast(ow_fcast5, 40, ow_key, OWM_COUNTRY, OWM_CITY, "metric");
  for (byte i = 0; i <= entries; ++i) {
    buf[i] = ow_fcast5[i].id.toInt();
  }
}

#endif
