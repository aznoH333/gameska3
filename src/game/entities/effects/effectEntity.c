#include "effectEntity.h"
#include "gameLib/gamelibInclude.h"
#include "game/gameEnums/enumsInclude.h"


void effectEntityUpdate(WorldObject* this, EffectEntityData* data);

void InitGoreExplosion(float x, float y){
    WorldObject* body = InitWorldObjectT(x, y, 0, 0, OBJECT_TAG_NEUTRAL);
    body->checkCollisions = false;
    body->layer = LAYER_EFFECT;
    
    ObjectController* controller = ObjectControllerInit();
    controller->objectUpdate = (ControllerUpdateFunction)&effectEntityUpdate;

    EffectEntityData* data = malloc(sizeof(EffectEntityData));

    data->frameCount = 5;
    data->animationLookup[0] = "gore_explosion_0001";
    data->animationLookup[1] = "gore_explosion_0002";
    data->animationLookup[2] = "gore_explosion_0003";
    data->animationLookup[3] = "gore_explosion_0004";
    data->animationLookup[4] = "gore_explosion_0005";
    data->animationTimer = 0;
    data->animationSpeed = 4;
    body->spriteIndex = getSpriteIndex(data->animationLookup[0]);

    GameObjectCreate(body, controller, data);
}


void effectEntityUpdate(WorldObject* this, EffectEntityData* data){
    data->animationTimer++;
    if (data->animationTimer >= data->animationSpeed * data->frameCount){
        this->state = OBJECT_STATE_DESTROY;
    }else {
        this->spriteIndex = getSpriteIndex(data->animationLookup[data->animationTimer / data->animationSpeed]);

    }
}