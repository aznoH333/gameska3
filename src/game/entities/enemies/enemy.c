#include "enemy.h"
#include <stdlib.h>
#include "game/gameEnums/enumsInclude.h"

void EnemyUpdate(WorldObject* this, EnemyData* data);
void EnemyClean(WorldObject* this, EnemyData* data);
void EnemyInteract(WorldObject* this, EnemyData* data, int interactionType, void* interactionValue);

WorldObject* GenericEnemyInit(float x, float y, float w, float h, int spriteIndex, float health, EnemyType enemyType, void (*extraUpdate)(WorldObject* this, struct EnemyData* data, void* extraData), void* extraData){
    WorldObject* body = InitWorldObjectT(x, y, w, h, OBJECT_TAG_ENEMY);
    body->spriteIndex = spriteIndex;
    body->layer = 0;
    

    ObjectController* controller = ObjectControllerInit();
    controller->objectUpdate = (ControllerUpdateFunction) &EnemyUpdate;
    controller->objectCleanUp = (ControllerUpdateFunction) &EnemyClean;
    controller->objectInteract = (ControllerInteractFunction) &EnemyInteract;

    EnemyData* data = malloc(sizeof(EnemyData));

    data->extraUpdate = extraUpdate;
    data->enemyExtraData = extraData;
    data->type = enemyType;
    data->health = health;
    data->maxHealth = health;

    GameObjectCreate(body, controller, data);
    debugMessage("spawned [%d]", body->dataId);
    return body;
}


void EnemyUpdate(WorldObject* this, EnemyData* data){
    data->extraUpdate(this, data, data->enemyExtraData);
}


void EnemyClean(WorldObject* this, EnemyData* data){
    free(data->enemyExtraData);
}


void takeDamage(WorldObject* this, EnemyData* data, float* damage){
    debugMessage("taking damage %f %f", *damage, data->health);
    data->health -= *damage;
    if (data->health <= 0){
        this->state = OBJECT_STATE_DESTROY;
    }
} 


void EnemyInteract(WorldObject* this, EnemyData* data, int interactionType, void* interactionValue){
    switch (interactionType) {
        case INTERACTION_DEAL_DAMAGE:
            takeDamage(this, data, interactionValue);
    };
}