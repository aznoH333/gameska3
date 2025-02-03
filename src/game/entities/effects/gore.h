#ifndef GORE 
#define GORE 

#include <stdbool.h>

struct GoreData{
    float xVelocity;
    float yVelocity;
    float zVelocity;
    float z;
    int bounceCount;
    bool isAirborne;
    float realY;
    int lifeTime;
};
typedef struct GoreData GoreData;

void InitGore(float x, float y, int bounceCount);

#endif