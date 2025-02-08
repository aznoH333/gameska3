#include "enemy.h"
#include <stdlib.h>
#include "game/gameEnums/enumsInclude.h"
#include "game/entities/effects/effectEntity.h"
#include "game/entities/effects/gore.h"
#include "gameLib/sounds.h"
#include "game/systems/enemyCoordinator.h"

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
    data->xMovement = 0.0f;
    data->yMovement = 0.0f;

    GameObjectCreate(body, controller, data);
    return body;
}


void EnemyCollide(WorldObject* this, EnemyData* data, WorldObject* other){
    if (data->extraCollisionUpdate != UNDEFINED){
        data->extraCollisionUpdate(this, data, data->enemyExtraData, other);
    }

    if (other->objectTag == OBJECT_TAG_PLAYER){
        initHeapVariable(int, damage, 1);
        GameObjectInteractIfPossible(other, INTERACTION_DEAL_DAMAGE, damage);

        ObjectInteractionPushData* pushData = malloc(sizeof(ObjectInteractionPushData));
        pushData->pushX = data->xMovement;
        pushData->pushY = data->yMovement;
        pushData->pushValue = 20;
        GameObjectInteractIfPossible(other, INTERACTION_PUSH, pushData);

    }
}



void EnemyUpdate(WorldObject* this, EnemyData* data){
    data->extraUpdate(this, data, data->enemyExtraData);
}


void EnemyClean(WorldObject* this, EnemyData* data){
    free(data->enemyExtraData);
}


void takeDamage(WorldObject* this, EnemyData* data, float* damage){
    
    int goreCount = 0;
    
    data->health -= *damage;
    if (data->health <= 0){
        this->state = OBJECT_STATE_DESTROY;
        soundPlay("enemy_death");
        goreCount = GetRandomValue(3, 6);
    }else {
        soundPlay("enemy_hit");
        goreCount = GetRandomValue(1, 2);
    }

    for (int i = 0; i < goreCount; i++){
        InitGore(this->x, this->y, GetRandomValue(0, 1));
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
    EnemyCoordinatorKilledEnemy();
    InitGoreExplosion(this->x, this->y);
}