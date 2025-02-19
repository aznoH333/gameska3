#ifndef Player
#define Player

#include "gun.h"

struct PlayerData{
    float xVelocity;
    float yVelocity;
    int dashCooldown;
    unsigned int stunTimer;
    unsigned int invincibilityTimer;
    Gun gun;
}; typedef struct PlayerData PlayerData;




void PlayerInit(float x, float y);



#endif