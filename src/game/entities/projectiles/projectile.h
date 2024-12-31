#ifndef PROJECTILE
#define PROJECTILE 

struct ProjectileData{
    float direction;
    float velocity;
};
typedef struct ProjectileData ProjectileData;


void ProjectileInit(float x, float y, float direction, float velocity);

#endif