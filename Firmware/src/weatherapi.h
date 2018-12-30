#ifndef __WEATHER_H
#define __WEATHER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include "Time.h"
#include "OpenWeatherMap.h"
#include "config.h"
#include "weathercolors.h"

const char *ow_key = OWM_API_KEY;
const char *nodename = "esp8266-weather";
const char *wifi_ssid = WIFI_SSID;
const char *wifi_passwd = WIFI_PW;

#define DATA_LEN 16
int myhour = 0;
int mytime = 0;
int mytemp = 0;

typedef enum wifi_s {
  W_AP = 0, W_READY, W_TRY
} WifiStat;

WifiStat           WF_status;

OWMconditions      owCC;
OWMfiveForecast    owF5;
OWM_fiveForecast   *ow_fcast5;
byte entries;

void connectWiFiInit(void) {
  WF_status  = W_TRY;
  WiFi.hostname(nodename);
  String ssid   = wifi_ssid;
  String passwd = wifi_passwd;
  WiFi.begin(ssid.c_str(), passwd.c_str());
}

// String dateTime(String timestamp) {
//   time_t ts = timestamp.toInt();
//   char buff[30];
//   sprintf(buff, "%2d:%02d %02d-%02d-%4d", hour(ts), minute(ts), day(ts), month(ts), year(ts));
//   return String(buff);
// }
//
// void getCurrentConditions(void) {
//   OWM_conditions *ow_cond = new OWM_conditions;
//   owCC.updateConditions(ow_cond, ow_key, OWM_COUNTRY, OWM_CITY, "metric");
//   // Serial.println(dateTime(ow_cond->dt));
//   Serial.print("Latitude & Longtitude: ");
//   Serial.print("<" + ow_cond->longtitude + " " + ow_cond->latitude + "> @" + dateTime(ow_cond->dt) + ": ");
//   Serial.println("icon: " + ow_cond->icon + ", " + " temp.: " + ow_cond->temp + ", press.: " + ow_cond->pressure);
//   delete ow_cond;
// }
//
void get5DayForecast() {
  Serial.print(F("Getting Forecast... "));
  ow_fcast5 = new OWM_fiveForecast[40];
  entries = owF5.updateForecast(ow_fcast5, 40, ow_key, OWM_COUNTRY, OWM_CITY, "metric");
  mytime = (ow_fcast5->dt).toInt();
  myhour = hour(mytime);
  myhour++; // from UTC to CET
  myhour%=24; // prevent overflow
  Serial.println(F("Done!"));
}

void getTemperatures(sint16_t *buf) {
  for (byte i = 0; i < DATA_LEN; i++) {
    buf[i] = (int)round(ow_fcast5[i].temp.toFloat());
    // buf[i] = (int)round((ow_fcast5[i].t_min.toFloat() + ow_fcast5[i].t_max.toFloat()) / 2); // <- AVERAGE OF MIN AND MAX! IS THIS OK?
  }
}

void getIcons(sint16_t *buf) {
  for (byte i = 0; i < DATA_LEN; i++) {
    buf[i] = ow_fcast5[i].icon.toInt();
  }
}

void getIds(sint16_t *buf) {
  for (byte i = 0; i < DATA_LEN; i++) {
    buf[i] = ow_fcast5[i].id.toInt();
  }
}

#endif
