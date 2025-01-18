#ifndef NUMBER_UTILS
#define NUMBER_UTILS

#include <stdbool.h>

unsigned int hashInt(unsigned int input);
unsigned long hashLong(unsigned long input);
float limitedIncrement(float  value, float target, float increment);
float sign(float input);
int boolToSign(bool input);
float distanceTo(float x1, float y1, float x2, float y2);
float randomFloat();
float randomFloatRange(float min, float max);



#endif