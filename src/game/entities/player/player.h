#ifndef Player
#define Player


struct PlayerData{

    float xVelocity;
    float yVelocity;
    int fireCooldown;
    int dashCooldown;

}; typedef struct PlayerData PlayerData;

void PlayerInit(float x, float y);



#endif