#ifndef __ANIMATIONS_H
#define __ANIMATIONS_H

#include <Arduino.h>

#define ANI_TYPE_CONST 0
#define ANI_TYPE_BLINK 1
#define ANI_TYPE_PULSE 2
#define ANI_TYPE_LOAD  3

class AnimationBrightness {
public:
  AnimationBrightness(uint16_t num, uint8_t type);
protected:
  uint8_t  type;
};

#endif
