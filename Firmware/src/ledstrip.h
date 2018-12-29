#ifndef __LEDSTRIP_H
#define __LEDSTRIP_H

#include <Adafruit_NeoPixel.h>

#define NP_PIN          4
#define NUMPIXELS      40
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NP_PIN, NEO_GRB + NEO_KHZ800);

#define ANI_TYPE_OFF   0
#define ANI_TYPE_ON    1
#define ANI_TYPE_BLINK 2
#define ANI_TYPE_PULSE 3
#define ANI_TYPE_RAMP  4

struct color_static {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct color_ani {
  uint8_t  r;
  uint8_t  g;
  uint8_t  b;
  uint8_t  ani_type;
  uint8_t  ani_min;
  uint8_t  ani_max;
  uint16_t ani_offset;
  uint16_t ani_time;
  uint16_t brightness;
};

// uint32_t colors[NUMPIXELS];
struct color_ani mypixels[NUMPIXELS];


void StartPixels() {
  pixels.begin();
  for (size_t i = 0; i < NUMPIXELS; i++) {
    mypixels[i].r = 0;
    mypixels[i].g = 0;
    mypixels[i].b = 0;
    mypixels[i].ani_type = ANI_TYPE_ON;
    mypixels[i].ani_min = 0;
    mypixels[i].ani_max = 255;
    mypixels[i].ani_offset = 0;
    mypixels[i].ani_time = 1000;
    mypixels[i].brightness = 255;
  }
}

void animatePixels() {
  long now = millis();
  uint8_t ro, go, bo;
  for (size_t i = 0; i < NUMPIXELS; i++) {
    switch (mypixels[i].ani_type) {
      case ANI_TYPE_OFF:
        mypixels[i].brightness = 0;
        break;
      case ANI_TYPE_ON:
        mypixels[i].brightness = mypixels[i].ani_max;
        break;
      case ANI_TYPE_BLINK:
        if ((now + mypixels[i].ani_offset) % mypixels[i].ani_time < mypixels[i].ani_time / 2)
          mypixels[i].brightness = mypixels[i].ani_max;
        else
          mypixels[i].brightness = mypixels[i].ani_min;
        break;
      case ANI_TYPE_PULSE:
        mypixels[i].brightness = (uint8_t)map((long)
                                     (255.0 * (0.5 * sin( (float)(now + mypixels[i].ani_offset) * 2.0 * 3.14159 / (float)mypixels[i].ani_time) + 0.5)),
                                     0, 255, mypixels[i].ani_min, mypixels[i].ani_max);
        break;
      default:
        mypixels[i].brightness = 255;
    }
    ro = (uint8_t)(((uint16_t)mypixels[i].r * mypixels[i].brightness) / 256);
    go = (uint8_t)(((uint16_t)mypixels[i].g * mypixels[i].brightness) / 256);
    bo = (uint8_t)(((uint16_t)mypixels[i].b * mypixels[i].brightness) / 256);
    pixels.setPixelColor(i, ro, go, bo);
    // if(i == 0) {
    //   Serial.println(ro);
    //   Serial.println(go);
    //   Serial.println(bo);
    // }
  }
  pixels.show();
}

void SetPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  pixels.setPixelColor(n, r, g, b);
}

void ShowPixels() {
  pixels.show();
}

#endif
