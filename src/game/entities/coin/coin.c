#include "coin.h"
#include "gameLib/gamelibInclude.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include "game/gameEnums/enumsInclude.h"
#include "math.h"
#include "game/entities/effects/effectEntity.h"


#define ANIMATION_FRAME_LENGTH 3
#define ANIMATION_FRAME_COUNT 20
#define EXISTANCE_TIMER 1800
#define FADE_TIMER 600

void CoinUpdate(WorldObject* this, CoinData* data);
void CoinCollide(WorldObject* this, CoinData* data, WorldObject* other);
void CoinDestroy(WorldObject* this, CoinData* data);



void CoinInit(float x, float y, int coinValue){
    WorldObject* this = InitWorldObject(x, y, 16.0f, 16.0f);
    this->objectTag = OBJECT_TAG_NEUTRAL;
    this->spriteIndex = getSpriteIndex("coin_0001");
    this->layer = LAYER_PICKUPS;

    ObjectController* controller = ObjectControllerInit();
    controller->objectUpdate = (ControllerUpdateFunction) &CoinUpdate;
    controller->objectCollide = (ControllerCollideFunction) &CoinCollide;
    controller->objectDestroy = (ControllerUpdateFunction) &CoinDestroy;

    CoinData* data = malloc(sizeof(CoinData));
    data->coinValue = coinValue;
    data->animationTimer = 0;
    
    float direction = randomFloatRange(0, 2*PI);
    float speed = randomFloatRange(0.8f, 2.6f);
    data->xMovement = cos(direction) * speed;
    data->yMovement = sin(direction) * speed;

    data->z = 0;
    data->zMovement = randomFloatRange(1.5f, 3.5f);
    data->realY = this->y;
    data->isAirborne = true;
    data->existanceTimer = EXISTANCE_TIMER;

    GameObjectCreate(this, controller, data);
}


void CoinUpdate(WorldObject* this, CoinData* data){
    data->animationTimer++;
    data->animationTimer %= ANIMATION_FRAME_COUNT * ANIMATION_FRAME_LENGTH;

    if (data->animationTimer % ANIMATION_FRAME_LENGTH == 0){
        this->spriteIndex = getSpriteIndex(TextFormat("coin_%04d", (data->animationTimer / ANIMATION_FRAME_LENGTH) + 1));
    }

    if (data->animationTimer % 10 == 0){
        InitCoinSparkle(this->x + GetRandomValue(0, this->width), this->y + GetRandomValue(0, this->height));
    }

    if (data->isAirborne){
        this->x += data->xMovement;
        data->realY += data->yMovement;
        data->z += data->zMovement;

        data->zMovement -= 0.5f;

        if (data->z < 0){
            data->isAirborne = false;
            data->z = 0;
        }

        this->y = data->realY - data->z;
    }

    data->existanceTimer--;
    // fade animation
    if (data->existanceTimer == 0){
        this->state = OBJECT_STATE_DESTROY;
    }
    else if (data->existanceTimer < FADE_TIMER){
        float fadePercent = (float)(data->existanceTimer - FADE_TIMER) / FADE_TIMER;
        this->color.a = (unsigned char)(255 * fadePercent);
    } 
    
}


void CoinCollide(WorldObject* this, CoinData* data, WorldObject* other){
    if (other->objectTag == OBJECT_TAG_PLAYER){
        initHeapVariable(int, money, data->coinValue);
        GameObjectInteractIfPossible(other, INTERACTION_GIVE_MONEY, money);
        this->state = OBJECT_STATE_DESTROY;
    }
}


void CoinDestroy(WorldObject* this, CoinData* data){
    int rng = GetRandomValue(3, 6);
    for (int i = 0; i < rng; i++){
        InitCoinSparkle(this->x + GetRandomValue(0, this->width), this->y + GetRandomValue(0, this->height));
    }
}