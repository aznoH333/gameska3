#include "numberUtils.h"
#include <math.h>
#include <stdint.h>
#include "math.h"

unsigned int hashInt(unsigned int input){
    input = ((input >> 16) ^ input) * 0x45d9f3b;
    input = ((input >> 16) ^ input) * 0x45d9f3b;
    input = (input >> 16) ^ input;
    return input;
}


unsigned long hashLong(unsigned long input){
    input = (input ^ (input >> 31) ^ (input >> 62)) * UINT64_C(0x319642b2d24d8ec3);
    input = (input ^ (input >> 27) ^ (input >> 54)) * UINT64_C(0x96de1b173f119089);
    input = input ^ (input >> 30) ^ (input >> 60);
    return input;
}


float limitedIncrement(float value, float target, float increment){
    int direction = sign(target- value);
    value += direction * increment;

    if (fabs(value - target) < 0.15f){
        return target;
    }
    return value;
}


float sign(float input){
    return (input > 0) + (input >= 0) - 1; 
}


int boolToSign(bool input){
    return input * 2 - 1;
}


float distanceTo(float x1, float y1, float x2, float y2){
    return sqrtf(pow((x1-x2), 2) + pow(y1 - y2, 2));
}
