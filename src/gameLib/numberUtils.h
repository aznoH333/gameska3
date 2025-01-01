#ifndef NUMBER_UTILS
#define NUMBER_UTILS

#include <stdbool.h>

unsigned int hashInt(unsigned int input);
unsigned long hashLong(unsigned long input);
float limitedIncrement(float  value, float target, float increment);
float sign(float input);
int boolToSign(bool input);


#endif