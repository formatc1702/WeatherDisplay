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

void StartPixels() {
  pixels.begin();
}

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

void SetPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  pixels.setPixelColor(n, r, g, b);
}

void ShowPixels() {
  pixels.show();
}

#endif
