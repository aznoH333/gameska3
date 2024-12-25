#include "numberUtils.h"
#include <stdint.h>

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
