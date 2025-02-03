#include "enemy.h"
#include <stdlib.h>
#include "game/gameEnums/enumsInclude.h"
#include "game/entities/effects/effectEntity.h"
#include "game/entities/effects/gore.h"

void EnemyUpdate(WorldObject* this, EnemyData* data);
void EnemyClean(WorldObject* this, EnemyData* data);
void EnemyCollide(WorldObject* this, EnemyData* data, WorldObject* other);
void EnemyInteract(WorldObject* this, EnemyData* data, ObjectInteraction* interactionData);
void EnemyDestroy(WorldObject* this, EnemyData* data);

WorldObject* GenericEnemyInit(
    float x, 
    float y, 
    float w, 
    float h, 
    int spriteIndex, 
    float health, 
    EnemyType enemyType, 
    void (*extraUpdate)(WorldObject* this, struct EnemyData* data, void* extraData),
    void (*extraCollisionUpdate)(WorldObject* this, struct EnemyData* data, void* enemyExtraData, WorldObject* other), 
    void* extraData
){
    WorldObject* body = InitWorldObjectT(x, y, w, h, OBJECT_TAG_ENEMY);
    body->spriteIndex = spriteIndex;
    body->layer = LAYER_ENEMY;
    

    ObjectController* controller = ObjectControllerInit();
    controller->objectUpdate = (ControllerUpdateFunction) &EnemyUpdate;
    controller->objectCleanUp = (ControllerUpdateFunction) &EnemyClean;
    controller->objectInteract = (ControllerInteractFunction) &EnemyInteract;
    controller->objectCollide = (ControllerCollideFunction) &EnemyCollide;
    controller->objectDestroy = (ControllerUpdateFunction) &EnemyDestroy;

    EnemyData* data = malloc(sizeof(EnemyData));

    data->extraUpdate = extraUpdate;
    data->extraCollisionUpdate = extraCollisionUpdate;
    data->enemyExtraData = extraData;
    data->type = enemyType;
    data->health = health;
    data->maxHealth = health;
    data->stunTimer = 0;

    GameObjectCreate(body, controller, data);
    return body;
}


void EnemyCollide(WorldObject* this, EnemyData* data, WorldObject* other){
    if (data->extraCollisionUpdate != UNDEFINED){
        data->extraCollisionUpdate(this, data, data->enemyExtraData, other);
    }
}



void EnemyUpdate(WorldObject* this, EnemyData* data){
    
    data->extraUpdate(this, data, data->enemyExtraData);
    
}


void EnemyClean(WorldObject* this, EnemyData* data){
    free(data->enemyExtraData);
}


void takeDamage(WorldObject* this, EnemyData* data, float* damage){
    data->health -= *damage;
    if (data->health <= 0){
        this->state = OBJECT_STATE_DESTROY;
    }

    int rng = GetRandomValue(1, 3);
    for (int i = 0; i < rng; i++){
        InitGore(this->x, this->y, 1);
    }
}

void push(WorldObject* this, EnemyData* data, ObjectInteractionPushData* pushData){
    data->stunPushX = pushData->pushX;
    data->stunPushY = pushData->pushY;
    data->stunTimer = pushData->pushValue;
}


void EnemyInteract(WorldObject* this, EnemyData* data, ObjectInteraction* interactionData){
    switch (interactionData->interactionType) {
        case INTERACTION_DEAL_DAMAGE:
            takeDamage(this, data, interactionData->interactionValue);
        case INTERACTION_PUSH:
            push(this, data, interactionData->interactionValue);
    };
}


void EnemyDestroy(WorldObject* this, EnemyData* data){
    InitGoreExplosion(this->x, this->y);
}