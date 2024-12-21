#include "numberUtils.h"

unsigned int hashInt(unsigned int input){
    input = ((input >> 16) ^ input) * 0x45d9f3b;
    input = ((input >> 16) ^ input) * 0x45d9f3b;
    input = (input >> 16) ^ input;
    return input;
}
