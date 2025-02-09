#include "effectEntity.h"
#include "gameLib/gamelibInclude.h"
#include "game/gameEnums/enumsInclude.h"
#include "math.h"
#include <stdlib.h>


void effectEntityUpdate(WorldObject* this, EffectEntityData* data);


void genericInit(float x, float y, EffectEntityData* data){

    WorldObject* body = InitWorldObjectT(x, y, 0, 0, OBJECT_TAG_NEUTRAL);
    body->checkCollisions = false;
    body->layer = LAYER_EFFECT;
    
    ObjectController* controller = ObjectControllerInit();
    controller->objectUpdate = (ControllerUpdateFunction)&effectEntityUpdate;

    data->animationTimer = 0;
    body->spriteIndex = getSpriteIndex(data->animationLookup[0]);

    GameObjectCreate(body, controller, data);
}

void InitGoreExplosion(float x, float y){

    EffectEntityData* data = malloc(sizeof(EffectEntityData));

    data->frameCount = 5;
    data->animationLookup[0] = "gore_explosion_0001";
    data->animationLookup[1] = "gore_explosion_0002";
    data->animationLookup[2] = "gore_explosion_0003";
    data->animationLookup[3] = "gore_explosion_0004";
    data->animationLookup[4] = "gore_explosion_0005";
    data->animationSpeed = 4;
    data->xMovement = 0.0f;
    data->yMovement = 0.0f;

    genericInit(x, y, data);
}


void InitCoinSparkle(float x, float y){
    EffectEntityData* data = malloc(sizeof(EffectEntityData));
    data->frameCount = 4;
    data->animationLookup[0] = "sparkle_0001";
    data->animationLookup[1] = "sparkle_0002";
    data->animationLookup[2] = "sparkle_0003";
    data->animationLookup[3] = "sparkle_0004";
    data->animationSpeed = 4;
    float direction = randomFloatRange(0, 2*PI);
    float speed = randomFloatRange(0.25f, 0.75f);
    data->xMovement = cos(direction) * speed;
    data->yMovement = sin(direction) * speed;
    debugMessage("??? [%f] [%f]", data->xMovement, data->yMovement);

    genericInit(x, y, data);
}


void effectEntityUpdate(WorldObject* this, EffectEntityData* data){
    if (data->animationTimer >= data->animationSpeed * data->frameCount){
        this->state = OBJECT_STATE_DESTROY;
    }else {
        this->spriteIndex = getSpriteIndex(data->animationLookup[data->animationTimer / data->animationSpeed]);
    }
    data->animationTimer++;
    this->x += data->xMovement;
    this->y += data->yMovement;
}