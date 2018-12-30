#include "ledstrip.h"
#include "weatherapi.h"
#include "weathercolors.h"

// extern "C" {
// #include "user_interface.h"
// }
// uint32_t free = system_get_free_heap_size();

int delayval = 20;

#define DATA_LEN 40
sint16_t temps[DATA_LEN] = {0};
sint16_t icons[DATA_LEN] = {0};
sint16_t ids  [DATA_LEN] = {0};
// sint16_t ids  [DATA_LEN] = {200, 201, 202, 210, 211, 212, 221, 230, 231, 232, 600, 601, 602, 310, 311, 312, 313, 314, 321, 500, 501, 502, 511, 520, 521, 522, 531, 800, 801, 802, 803, 804};
struct color_static tempcolors[DATA_LEN];
struct color_ani    iconcolors[DATA_LEN];
struct color_ani    idcolors  [DATA_LEN];

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Hello World!");
  StartPixels();
  // for (size_t i = 0; i < DATA_LEN; i++) {
  //   temps[i] = 0;
  //   icons[i] = 0;
  //   ids  [i] = 0;
  // }
  Serial.print("Connecting to WiFi... ");
  connectWiFiInit();
}

void loop() {
  if (WF_status == W_TRY) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Connected!");
      MDNS.begin(nodename);
      WF_status = W_READY;
      get5DayForecast();
      getTemperatures(temps);
      getIcons(icons);
      getIds(ids);
      for (size_t i = 0; i < DATA_LEN; i++) {
        if (i < NUMPIXELS) {
          tempcolors[i] = TempToColor(temps[i]);
          iconcolors[i] = IconToColor(icons[i]);
          idcolors[i]   = IdToColor  (ids  [i]);

          // iconcolors[0] = COLOR_CLEAR;
          // iconcolors[1] = COLOR_CLOUDS_FEW;
          // iconcolors[2] = COLOR_CLOUDS_SCATTERED;
          // iconcolors[3] = COLOR_CLOUDS_BROKEN;
          // iconcolors[4] = COLOR_RAIN_SHOWER;
          // iconcolors[5] = COLOR_RAIN_RAIN;
          // iconcolors[6] = COLOR_THUNDERSTORM;
          // iconcolors[7] = COLOR_SNOW;
          // iconcolors[8] = COLOR_MIST;

          Serial.print(i);
          Serial.print(" :\t");
          Serial.print(temps[i]);
          Serial.print('\t');
          Serial.print(icons[i]);
          Serial.print('\t');
          Serial.print(ids[i]);
          Serial.print('\t');
          // Serial.print('\t');
          // Serial.print(tempcolors[i].r);
          // Serial.print('\t');
          // Serial.print(tempcolors[i].g);
          // Serial.print('\t');
          // Serial.print(tempcolors[i].b);
          // Serial.print('\t');
          // Serial.print('\t');
          // Serial.print('\t');

          // Serial.print(iconcolors[i].r);
          // Serial.print('\t');
          // Serial.print(iconcolors[i].g);
          // Serial.print('\t');
          // Serial.print(iconcolors[i].b);
          // Serial.print('\t');
          Serial.print('\n');
          if (i % 8 == 7)
            Serial.print('\n');
        }

      }
      // ShowPixels();
      while(true) {
        // show weather id colors
        // for (size_t i = 0; i < NUMPIXELS; i++) {
        //   mypixels[i]  = idcolors[i];
        // }
        if (millis() % 10000 < 5000) {
          // show temperatures
          for (size_t i = 0; i < NUMPIXELS; i++) {
            mypixels[i].r = tempcolors[i].r;
            mypixels[i].g = tempcolors[i].g;
            mypixels[i].b = tempcolors[i].b;
            mypixels[i].ani_type = ANI_TYPE_ON;
            mypixels[i].ani_max = 255;
            mypixels[i].brightness = 255;
          }
        } else {
          // show weather condition colors
          for (size_t i = 0; i < NUMPIXELS; i++) {
            mypixels[i]  = idcolors[i];
          }
        }
        animatePixels();
        delay(delayval);
      };
    }
  }
}
