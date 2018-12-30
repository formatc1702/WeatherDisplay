#ifndef __WEATHERCOLORS_H
#define __WEATHERCOLORS_H

#include <Arduino.h>
#include "ledstrip.h"
#include "weatherids.h"

#define COLOR_OFF              {  0,   0,   0, ANI_TYPE_OFF,     0, 255,   0, 1000, 0, 255}
#define COLOR_UNKNOWN          {255,   0,   0, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}
#define COLOR_CLEAR            {255, 255,   0, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}
#define COLOR_CLOUDS_FEW       {255, 255, 128, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}
#define COLOR_CLOUDS_SCATTERED {255, 255, 255, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}
#define COLOR_CLOUDS_BROKEN    {  0,   0, 255, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}
#define COLOR_RAIN_SHOWER      {  0, 255, 255, ANI_TYPE_PULSE,  128, 255,   0, 1000, 0, 255}
#define COLOR_RAIN_RAIN        {  0,   0, 255, ANI_TYPE_PULSE,   64, 255,   0, 1000, 0, 255}
#define COLOR_THUNDERSTORM     {255, 255,   0, ANI_TYPE_BLINK,   0, 255,   0, 666, 40, 255}
#define COLOR_SNOW             {255, 255, 255, ANI_TYPE_PULSE,  128, 255,   0, 1000, 0, 255}
#define COLOR_MIST             {128, 128, 128, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}

/* 200 */ #define COLOR_THUNDERSTORM_WITH_LIGHT_RAIN {  0, 128, 255, ANI_TYPE_PULSE,  192, 255,   0, 1000, 0, 255, 16}
/* 201 */ #define COLOR_THUNDERSTORM_WITH_RAIN       {  0,  64, 255, ANI_TYPE_PULSE,  128, 255,   0, 1000, 0, 255, 16}
/* 202 */ #define COLOR_THUNDERSTORM_WITH_HEAVY_RAIN {  0,   0, 255, ANI_TYPE_PULSE,    0, 255,   0, 1000, 0, 255, 16}
/* 210 */ #define COLOR_LIGHT_THUNDERSTORM           {  0, 128, 255, ANI_TYPE_PULSE,  192, 255,   0, 1000, 0, 255, 8}
/* 211 */ #define COLOR_THUNDERSTORM                 {  0,  64, 255, ANI_TYPE_PULSE,  128, 255,   0, 1000, 0, 255, 16}
/* 212 */ #define COLOR_HEAVY_THUNDERSTORM           {  0,   0, 255, ANI_TYPE_PULSE,    0, 255,   0, 1000, 0, 255, 24}
/* 221 */ #define COLOR_RAGGED_THUNDERSTORM          {  0,   0, 255, ANI_TYPE_PULSE,    0, 255,   0,  500, 0, 255, 32}

/* 500 */ #define COLOR_LIGHT_RAIN           {255, 128,   0, ANI_TYPE_PULSE_WHITE,  192, 255,   0, 1000, 0, 255}
/* 501 */ #define COLOR_MODERATE_RAIN        {  0,  64, 255, ANI_TYPE_PULSE,        128, 255,   0, 1000, 0, 255}
/* 502 */ #define COLOR_HEAVY_INTENSITY_RAIN {  0,   0, 255, ANI_TYPE_PULSE,          0, 255,   0, 1000, 0, 255}
/* 503 */ #define COLOR_VERY_HEAVY_RAIN      {  0,   0, 255, ANI_TYPE_PULSE,          0, 255,   0,  500, 0, 255}
/* 504 */ #define COLOR_EXTREME_RAIN         {  0,   0, 255, ANI_TYPE_PULSE,          0, 255,   0,  250, 0, 255}
/* 511 */ #define COLOR_FREEZING_RAIN        {255, 128,   0, ANI_TYPE_PULSE_WHITE,    0, 255,   0, 1000, 0, 255} // COLOR INVERTED FOR WHITE PULSE

/* 600 */ #define COLOR_LIGHT_SNOW {255, 255, 255, ANI_TYPE_PULSE,  192, 255,   0, 1000, 0, 255}
/* 601 */ #define COLOR_SNOW       {255, 255, 255, ANI_TYPE_PULSE,  128, 255,   0, 1000, 0, 255}
/* 602 */ #define COLOR_HEAVY_SNOW {255, 255, 255, ANI_TYPE_PULSE,    0, 255,   0, 1000, 0, 255}


/* 800 */ #define COLOR_CLEAR_SKY        {255, 255,   0, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}
/* 801 */ #define COLOR_FEW_CLOUDS       {255, 255, 128, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}
/* 802 */ #define COLOR_SCATTERED_CLOUDS {255, 255, 192, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}
/* 803 */ #define COLOR_BROKEN_CLOUDS    {128, 128, 128, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}
/* 804 */ #define COLOR_OVERCAST_CLOUDS  { 64,  64,  64, ANI_TYPE_ON,      0, 255,   0, 1000, 0, 255}

struct color_static TempToColor(sint16_t temp) {
  struct color_static result;
  result = HSV2RGB_3((temp * -6 + 180 + 360)  % 360, 255, 255);
  return result;
}

struct color_ani IconToColor(sint16_t icon) {
  struct color_ani result;
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
  switch(id) {
    case 200:
    result = COLOR_THUNDERSTORM_WITH_LIGHT_RAIN;
    break;
    case 201:
    result = COLOR_THUNDERSTORM_WITH_RAIN;
    break;
    case 202:
    result = COLOR_THUNDERSTORM_WITH_HEAVY_RAIN;
    break;
    case 210:
    result = COLOR_LIGHT_THUNDERSTORM;
    break;
    case 211:
    result = COLOR_THUNDERSTORM;
    break;
    case 212:
    result = COLOR_HEAVY_THUNDERSTORM;
    break;
    case 221:
    result = COLOR_RAGGED_THUNDERSTORM;
    break;
    case 500:
    result = COLOR_LIGHT_RAIN;
    break;
    case 501:
    result = COLOR_MODERATE_RAIN;
    break;
    case 502:
    result = COLOR_HEAVY_INTENSITY_RAIN;
    break;
    case 503:
    result = COLOR_VERY_HEAVY_RAIN;
    break;
    case 504:
    result = COLOR_EXTREME_RAIN;
    break;
    case 511:
    result = COLOR_FREEZING_RAIN;
    break;
    case 600:
    result = COLOR_LIGHT_SNOW;
    break;
    case 601:
    result = COLOR_SNOW;
    break;
    case 602:
    result = COLOR_HEAVY_SNOW;
    break;
    case 800:
    result = COLOR_CLEAR_SKY;
    break;
    case 801:
    result = COLOR_FEW_CLOUDS;
    break;
    case 802:
    result = COLOR_SCATTERED_CLOUDS;
    break;
    case 803:
    result = COLOR_BROKEN_CLOUDS;
    break;
    case 804:
    result = COLOR_OVERCAST_CLOUDS;
    break;
    default:
    result = COLOR_UNKNOWN;
    break;
  }
  return result;
}

#endif
