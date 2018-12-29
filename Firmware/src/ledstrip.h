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

const byte dim_curve[] = {
    0,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,
    3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   4,   4,
    4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   6,   6,
    6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,
    8,   8,   9,   9,   9,   9,   9,   9,   10,  10,  10,  10,  10,  11,  11,  11,
    11,  11,  12,  12,  12,  12,  12,  13,  13,  13,  13,  14,  14,  14,  14,  15,
    15,  15,  16,  16,  16,  16,  17,  17,  17,  18,  18,  18,  19,  19,  19,  20,
    20,  20,  21,  21,  22,  22,  22,  23,  23,  24,  24,  25,  25,  25,  26,  26,
    27,  27,  28,  28,  29,  29,  30,  30,  31,  32,  32,  33,  33,  34,  35,  35,
    36,  36,  37,  38,  38,  39,  40,  40,  41,  42,  43,  43,  44,  45,  46,  47,
    48,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,
    63,  64,  65,  66,  68,  69,  70,  71,  73,  74,  75,  76,  78,  79,  81,  82,
    83,  85,  86,  88,  90,  91,  93,  94,  96,  98,  99,  101, 103, 105, 107, 109,
    110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
    146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
    193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
};

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
  uint16_t ani_duty;
  uint16_t brightness;
};

struct color_ani mypixels[NUMPIXELS];

struct color_static HSV2RGB(int hue, int sat, int val) {
  struct color_static result;
  /* convert hue, saturation and brightness ( HSB/HSV ) to RGB
     The dim_curve is used only on brightness/value and on saturation (inverted).
     This looks the most natural.
  */

  val = dim_curve[val];
  sat = 255-dim_curve[255-sat];

  int r = 0;
  int g = 0;
  int b = 0;
  int base;

  if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
    result.r=val;
    result.g=val;
    result.b=val;
  } else  {

    base = ((255 - sat) * val)>>8;

    switch(hue/60) {
    case 0:
        r = val;
        g = (((val-base)*hue)/60)+base;
        b = base;
    break;

    case 1:
        r = (((val-base)*(60-(hue%60)))/60)+base;
        g = val;
        b = base;
    break;

    case 2:
        r = base;
        g = val;
        b = (((val-base)*(hue%60))/60)+base;
    break;

    case 3:
        r = base;
        g = (((val-base)*(60-(hue%60)))/60)+base;
        b = val;
    break;

    case 4:
        r = (((val-base)*(hue%60))/60)+base;
        g = base;
        b = val;
    break;

    case 5:
        r = val;
        g = base;
        b = (((val-base)*(60-(hue%60)))/60)+base;
    break;
    }

    result.r=r;
    result.g=g;
    result.b=b;
  }

  return result;
}

struct color_static HSV2RGB_2(int hue, int sat, int val) {
  struct color_static result;
  result = HSV2RGB(hue, sat, val);
  result.r=dim_curve[result.r];
  result.g=dim_curve[result.g];
  result.b=dim_curve[result.b];
  return result;
}

struct color_static HSV2RGB_3(int hue, int sat, int val) {
  struct color_static result;
  result = HSV2RGB(hue, sat, val);
  result.r=result.r / 2 + dim_curve[result.r] / 2;
  result.g=result.g / 2 + dim_curve[result.g] / 2;
  result.b=result.b / 2 + dim_curve[result.b] / 2;
  return result;
}

struct color_static dimCurve_3(color_static color_in) {
  struct color_static result;
  result.r=color_in.r / 2 + dim_curve[color_in.r] / 2;
  result.g=color_in.g / 2 + dim_curve[color_in.g] / 2;
  result.b=color_in.b / 2 + dim_curve[color_in.b] / 2;
  return result;
}

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
    mypixels[i].ani_duty = 1000;
    mypixels[i].brightness = 255;
  }
}

void animatePixels() {
  long now = millis();
  color_static color_out;
  for (size_t i = 0; i < NUMPIXELS; i++) {
    switch (mypixels[i].ani_type) {
      case ANI_TYPE_OFF:
        mypixels[i].brightness = 0;
        break;
      case ANI_TYPE_ON:
        mypixels[i].brightness = mypixels[i].ani_max;
        break;
      case ANI_TYPE_BLINK:
        if ((now + mypixels[i].ani_offset) % mypixels[i].ani_time < mypixels[i].ani_duty)
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
    color_out.r = (uint8_t)(((uint16_t)mypixels[i].r * mypixels[i].brightness) / 256);
    color_out.g = (uint8_t)(((uint16_t)mypixels[i].g * mypixels[i].brightness) / 256);
    color_out.b = (uint8_t)(((uint16_t)mypixels[i].b * mypixels[i].brightness) / 256);
    color_out = dimCurve_3(color_out);
    pixels.setPixelColor(i, color_out.r, color_out.g, color_out.b);
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
