#include "ledstrip.h"
#include "weatherapi.h"
#include "weathercolors.h"

// extern "C" {
// #include "user_interface.h"
// }
// uint32_t free = system_get_free_heap_size();

int delayval = 20;

sint16_t temps[DATA_LEN] = {0};
sint16_t ids  [DATA_LEN] = {0};
// sint16_t icons[DATA_LEN] = {0};
sint16_t fakeids  [DATA_LEN] = {
800,
801,
802,
803,
804,
500,
501,
502,
212,
211,
210,
201,
200,
600,
601,
602
};
struct color_static tempcolors[DATA_LEN];
struct color_ani    idcolors  [DATA_LEN];
// struct color_ani    iconcolors[DATA_LEN];

#define SLEEP_DELAY 60000
uint32_t lastupdatetime = 0;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println(F("Hello World!"));
  StartPixels();
  Serial.print(F("Connecting to WiFi... "));
  connectWiFiInit();
}

void loop() {
  if (WF_status == W_TRY) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println(F("Connected!"));
      MDNS.begin(nodename);
      WF_status = W_READY;
      // get data from API
      get5DayForecast();
      // process data
      getTemperatures(temps);
      getIds(ids);
      // getIcons(icons);

      // for (size_t i = 0; i < DATA_LEN; i++) {
      //   ids[i] = fakeids[i];
      // }
      // myhour = 0;


      Serial.print(F("Timestamp: "));
      Serial.print(mytime);
      Serial.print(F("; Hour: "));
      Serial.println(myhour);

      for (size_t i = 0; i < DATA_LEN; i++) {
        if (i < NUMPIXELS) {
          tempcolors[i] = TempToColor(temps[i]);
          idcolors[i]   = IdToColor  (ids  [i]);
          // iconcolors[i] = IconToColor(icons[i]);

          // /*
          Serial.print(i);
          Serial.print('\t');
          Serial.print((myhour + 3*i) % 24);
          Serial.print('\t');
          Serial.print(temps[i]);
          Serial.print('\t');
          Serial.print(ids[i]);
          Serial.print('\t');
          // Serial.print(icons[i]);
          // Serial.print('\t');

          Serial.print('\n');
          if (i % 8 == 7)
            Serial.print('\n');
          // */

        }

      }
      int offset = 0;
      for (size_t i = 0; i < 15; i++) {
        // offset = i >= 8;
        offset = (myhour + i*3)/24;
        // show temperatures
        mypixels[i+offset].r = tempcolors[i].r;
        mypixels[i+offset].g = tempcolors[i].g;
        mypixels[i+offset].b = tempcolors[i].b;
        mypixels[i+offset].ani_type   = ANI_TYPE_ON;
        mypixels[i+offset].ani_max    = 255;
        mypixels[i+offset].brightness = 255;
        // show weather condition colors
        // in reverse because of the way the LEDs are wired
        mypixels[34-1-i-offset] = idcolors[i];
      }
      lastupdatetime = millis();
      // show animation until timeout
      while(millis() - lastupdatetime < SLEEP_DELAY) {
        animatePixels();
        delay(delayval);
      };
      // timeout occured, turn off all pixels...
      for (size_t i = 0; i < NUMPIXELS; i++) {
        mypixels[i].ani_type = ANI_TYPE_OFF;
      }
      animatePixels();
      // ...and sleep
      Serial.println(F("Time is up! Sleeping..."));
      ESP.deepSleep(0);
      while(true);
    }
  }
}
