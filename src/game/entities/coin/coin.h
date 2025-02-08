#ifndef COIN 
#define COIN 


#include <stdbool.h>


struct CoinData{
    int coinValue;
    int animationTimer;
    float xMovement;
    float yMovement;
    float z;
    float zMovement;
    float realY;
    bool isAirborne;    
};
typedef struct CoinData CoinData ;


void CoinInit(float x, float y, int coinValue);

#endif