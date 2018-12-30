#ifndef __WEATHERCOLORS_H
#define __WEATHERCOLORS_H

#include <Arduino.h>
#include "ledstrip.h"
#include "weatherids.h"

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
