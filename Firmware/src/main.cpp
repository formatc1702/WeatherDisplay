#include "ledstrip.h"
#include "weather.h"
#include "weathercolors.h"

int delayval = 20;

#define DATA_LEN 40
sint16_t temps[DATA_LEN] = {0};
sint16_t icons[DATA_LEN] = {0};
struct color_static tempcolors[DATA_LEN];
struct color_ani    iconcolors[DATA_LEN];

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Hello World!");
  StartPixels();
  for (size_t i = 0; i < DATA_LEN; i++) {
    temps[i] = 0;
    icons[i] = 0;
  }
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
      for (size_t i = 0; i < DATA_LEN; i++) {
        if (i < NUMPIXELS) {
          tempcolors[i] = TempToColor(temps[i]);
          iconcolors[i] = IconToColor(icons[i]);
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
          // Serial.print(temps[i]);
          Serial.print('\t');
          Serial.print(icons[i]);
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

          Serial.print(iconcolors[i].r);
          Serial.print('\t');
          Serial.print(iconcolors[i].g);
          Serial.print('\t');
          Serial.print(iconcolors[i].b);
          Serial.print('\t');
        }

        Serial.print('\n');
        if (i % 8 == 7)
          Serial.print('\n');
      }
      // ShowPixels();
      while(true) {
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
            mypixels[i]  = iconcolors[i];
          }
        }
        animatePixels();
        delay(delayval);
      };
    }
  }
}

/*

void setup() {
  Serial.begin(115200);
  // pixels.begin();


  // for (size_t i = 0; i < NUMPIXELS; i++) {
  //   ri[i]=0;
  //   gi[i]=255;
  //   bi[i]=0;
  //   ani_type[i]=ANI_TYPE_OFF;
  //   ani_min[i]=0;
  //   ani_max[i]=255;
  //   ani_offset[i]=0;
  //   ani_time[i]=1000;
  // }
  //
  // ani_type[0]=ANI_TYPE_OFF;
  // ani_type[1]=ANI_TYPE_ON;
  // ani_type[2]=ANI_TYPE_BLINK;
  // ani_type[3]=ANI_TYPE_BLINK;
  // ani_offset[3]=500;
  // ani_type[4]=ANI_TYPE_BLINK;
  // ani_min[4]=64;
  // ani_max[4]=192;
  // ani_type[7]=ANI_TYPE_PULSE;
  // ani_type[8]=ANI_TYPE_PULSE;
  // ani_type[9]=ANI_TYPE_PULSE;
  // ani_offset[7]=0;
  // ani_offset[8]=500;
  // ani_offset[9]=0;
  // ani_time[9]=2000;

  // colors[0] = pixels.Color(255,0,0);
  // colors[1] = pixels.Color(255,128,0);
  // colors[2] = pixels.Color(255,255,0);
  // colors[3] = pixels.Color(128,255,0);
  // colors[4] = pixels.Color(0,255,0);
  // colors[5] = pixels.Color(0,255,128);
  // colors[6] = pixels.Color(0,255,255);
  // colors[7] = pixels.Color(0,0,255);
  // colors[8] = pixels.Color(128,0,255);
  // colors[9] = pixels.Color(255,0,255);
  //
  // for (size_t i = 0; i < NUMPIXELS; i++) {
  //   brightness[i]=255;
  // }

}


void loop() {
  // for(int i=0;i<NUMPIXELS;i++){
  //   uint8_t r = (150.0 * (0.5 * sin((millis() + 100 * i + 000) * 2.0 * 3.14159 / 1000.0) + 0.5));
  //   uint8_t g = (150.0 * (0.5 * sin((millis() + 100 * i + 333) * 2.0 * 3.14159 / 1000.0) + 0.5));
  //   uint8_t b = (150.0 * (0.5 * sin((millis() + 100 * i + 667) * 2.0 * 3.14159 / 1000.0) + 0.5));
  //   pixels.setPixelColor(i, pixels.Color(r,g,b));
  // }
  // animate();
  // pixels.show();
  // Serial.println(
  //   map((long)(
  //     255.0 * (0.5 * sin(
  //       (float)(millis()) * 2.0 * 3.14159 / 1000
  //     ) + 0.5)
  //   ), 0, 255, 1, 254)
  // );
  // delay(delayval);
}

// */
