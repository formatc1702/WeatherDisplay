#include <Adafruit_NeoPixel.h>

// #include <ESP8266WiFi.h>
// #include <ESP8266WiFiMulti.h>

#include "ledstrip.h"

#define PIN            4
#define NUMPIXELS      10
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define ANI_TYPE_OFF   0
#define ANI_TYPE_ON    1
#define ANI_TYPE_BLINK 2
#define ANI_TYPE_PULSE 3
#define ANI_TYPE_RAMP  4

int delayval = 20;

uint32_t colors[NUMPIXELS];

// input colors
uint8_t  ri[NUMPIXELS];
uint8_t  gi[NUMPIXELS];
uint8_t  bi[NUMPIXELS];

// animation parameters
uint8_t  ani_type   [NUMPIXELS];
uint8_t  ani_min    [NUMPIXELS];
uint8_t  ani_max    [NUMPIXELS];
uint16_t ani_offset [NUMPIXELS];
uint16_t ani_time   [NUMPIXELS];

// internal variables
uint16_t  brightness[NUMPIXELS];

// input colors
uint8_t  ro[NUMPIXELS];
uint8_t  go[NUMPIXELS];
uint8_t  bo[NUMPIXELS];

void animate() {
  long now = millis();
  for (size_t i = 0; i < NUMPIXELS; i++) {
    switch (ani_type[i]) {
      case ANI_TYPE_OFF:
        brightness[i] = 0;
        break;
      case ANI_TYPE_ON:
        brightness[i] = ani_max[i];
        break;
      case ANI_TYPE_BLINK:
        if ((now + ani_offset[i]) % ani_time[i] < ani_time[i] / 2)
          brightness[i] = ani_max[i];
        else
          brightness[i] = ani_min[i];
        break;
      case ANI_TYPE_PULSE:

      brightness[i] = (uint8_t)map((long)
                                   (255.0 * (0.5 * sin( (float)(now + ani_offset[i]) * 2.0 * 3.14159 / (float)ani_time[i]) + 0.5)),
                                   0, 255, ani_min[i], ani_max[i]);
        break;
      default:
        brightness[i] = 255;
    }
    ro[i] = (uint8_t)(((uint16_t)ri[i] * brightness[i]) / 256);
    go[i] = (uint8_t)(((uint16_t)gi[i] * brightness[i]) / 256);
    bo[i] = (uint8_t)(((uint16_t)bi[i] * brightness[i]) / 256);
    pixels.setPixelColor(i, pixels.Color(ro[i], go[i], bo[i]));
  }
}

void setup() {
  Serial.begin(115200);
  pixels.begin();

  for (size_t i = 0; i < NUMPIXELS; i++) {
    ri[i]=0;
    gi[i]=255;
    bi[i]=0;
    ani_type[i]=ANI_TYPE_OFF;
    ani_min[i]=0;
    ani_max[i]=255;
    ani_offset[i]=0;
    ani_time[i]=1000;
  }

  ani_type[0]=ANI_TYPE_OFF;
  ani_type[1]=ANI_TYPE_ON;
  ani_type[2]=ANI_TYPE_BLINK;
  ani_type[3]=ANI_TYPE_BLINK;
  ani_offset[3]=500;
  ani_type[4]=ANI_TYPE_BLINK;
  ani_min[4]=64;
  ani_max[4]=192;
  ani_type[7]=ANI_TYPE_PULSE;
  ani_type[8]=ANI_TYPE_PULSE;
  ani_type[9]=ANI_TYPE_PULSE;
  ani_offset[7]=0;
  ani_offset[8]=500;
  ani_offset[9]=0;
  ani_time[9]=2000;

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
  animate();
  pixels.show();
  Serial.println(
    map((long)(
      255.0 * (0.5 * sin(
        (float)(millis()) * 2.0 * 3.14159 / 1000
      ) + 0.5)
    ), 0, 255, 1, 254)
  );
  delay(delayval);
}
