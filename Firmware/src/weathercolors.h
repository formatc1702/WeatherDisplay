#ifndef __WEATHERCOLORS_H
#define __WEATHERCOLORS_H

#include <Arduino.h>
#include "ledstrip.h"

#define ID_CLEAR 800
// Group 3xx: Rain
#define ID_LIGHT_DRIZZLE 300
#define ID_DRIZZLE 301
#define ID_HEAVY_DRIZZLE 302
#define ID_LIGHT_DRIZZLE_RAIN 310
#define ID_DRIZZLE_RAIN 311
#define ID_HEAVY_DRIZZLE_RAIN 312
#define ID_SHOWER_RAIN_AND_DRIZZLE 313
#define ID_HEAVY_SHOWER_RAIN_AND_DRIZZLE 314
#define ID_SHOWER_DRIZZLE 321
// Group 5xx: Rain
#define ID_LIGHT_RAIN 500
#define ID_MODERATE_RAIN 501
#define ID_HEAVY_INTENSITY_RAIN 502
#define ID_VERY_HEAVY_RAIN 503
#define ID_EXTREME_RAIN 504
#define ID_FREEZING_RAIN 511
#define ID_LIGHT_INTENSITY_SHOWER_RAIN 520
#define ID_SHOWER_RAIN 521
#define ID_HEAVY_INTENSITY_SHOWER_RAIN 522
#define ID_RAGGED_SHOWER_RAIN 531


#define COLOR_OFF              {255,   0,   0, ANI_TYPE_PULSE,   0, 255,   0, 1000, 0, 255}
#define COLOR_CLEAR            {255, 255,   0, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}
#define COLOR_CLOUDS_FEW       {255, 255, 128, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}
#define COLOR_CLOUDS_SCATTERED {255, 255, 255, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}
#define COLOR_CLOUDS_BROKEN    {  0,   0, 255, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}
#define COLOR_RAIN_SHOWER      {  0, 255, 255, ANI_TYPE_PULSE,  128, 255,   0, 1000, 0, 255}
#define COLOR_RAIN_RAIN        {  0,   0, 255, ANI_TYPE_PULSE,   64, 255,   0, 1000, 0, 255}
#define COLOR_THUNDERSTORM     {255, 255,   0, ANI_TYPE_BLINK,   0, 255,   0, 666, 40, 255}
#define COLOR_SNOW             {255, 255, 255, ANI_TYPE_PULSE,  128, 255,   0, 1000, 0, 255}
#define COLOR_MIST             {128, 128, 128, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}

struct color_static TempToColor(sint16_t temp) {
  struct color_static result;
  result = HSV2RGB_3((temp * -6 + 180 + 360)  % 360, 255, 255);
  return result;
}

struct color_ani IconToColor(sint16_t icon) {
  struct color_ani result;
  result = COLOR_OFF;
  switch(icon) {
    case  1:  result = COLOR_CLEAR;            break;
    case  2:  result = COLOR_CLOUDS_FEW;       break;
    case  3:  result = COLOR_CLOUDS_SCATTERED; break;
    case  4:  result = COLOR_CLOUDS_BROKEN;    break;
    case  9:  result = COLOR_RAIN_SHOWER;      break;
    case 10:  result = COLOR_RAIN_RAIN;        break;
    case 11:  result = COLOR_THUNDERSTORM;     break;
    case 13:  result = COLOR_SNOW;             break;
    case 50:  result = COLOR_MIST;             break;
    default:  result = COLOR_OFF;              break;
  }
  return result;
}

struct color_ani IdToColor(sint16_t id) {
  struct color_ani result;
  result = COLOR_OFF;
  switch(id) {
    // TODO 
  }
  return result;
}

#endif
