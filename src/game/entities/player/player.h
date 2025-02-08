#ifndef Player
#define Player


struct PlayerData{

    float xVelocity;
    float yVelocity;
    int fireCooldown;
    int dashCooldown;
    unsigned int ammoCount;
    unsigned int reloadTimer;
    unsigned int stunTimer;
    unsigned int invincibilityTimer;
}; typedef struct PlayerData PlayerData;

void PlayerInit(float x, float y);



#endif