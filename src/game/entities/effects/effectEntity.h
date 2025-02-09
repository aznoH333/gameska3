#ifndef EFFECT_ENTITY
#define EFFECT_ENTITY


#define MAX_FRAMES 10

struct EffectEntityData{
    const char* animationLookup[MAX_FRAMES];
    int frameCount;
    int animationTimer;
    int animationSpeed;
    float xMovement;
    float yMovement;
};
typedef struct EffectEntityData EffectEntityData;

void InitGoreExplosion(float x, float y);
void InitCoinSparkle(float x, float y);

#undef MAX_FRAMES
#endif