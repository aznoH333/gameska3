#ifndef Player
#define Player

#include "gun.h"
#include "../../../gameLib/worldObject.h"

struct PlayerData{
    float xVelocity;
    float yVelocity;
    int dashCooldown;
    unsigned int stunTimer;
    unsigned int invincibilityTimer;
    Gun gun;
}; typedef struct PlayerData PlayerData;




void PlayerInit(float x, float y);
Gun* PlayerGetGun(WorldObject* player);


#endif