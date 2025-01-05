#include "enemy.h"
#include <stdlib.h>


void EnemyUpdate(WorldObject* this, EnemyData* data);
void EnemyClean(WorldObject* this, EnemyData* data);

WorldObject* GenericEnemyInit(float x, float y, float w, float h, int spriteIndex, EnemyType enemyType, void (*extraUpdate)(WorldObject* this, struct EnemyData* data, void* extraData), void* extraData){
    WorldObject* body = InitWorldObject(x, y, w, h);
    body->spriteIndex = spriteIndex;
    body->layer = 0;
    

    ObjectController* controller = ObjectControllerInit();
    controller->objectUpdate = (ControllerUpdateFunction) &EnemyUpdate;
    controller->objectCleanUp = (ControllerUpdateFunction) &EnemyClean;

    EnemyData* data = malloc(sizeof(EnemyData));

    data->extraUpdate = extraUpdate;
    data->enemyExtraData = extraData;
    data->type = enemyType;

    GameObjectCreate(body, controller, data);

    return body;
}


void EnemyUpdate(WorldObject* this, EnemyData* data){
    data->extraUpdate(this, data, data->enemyExtraData);
}


void EnemyClean(WorldObject* this, EnemyData* data){
    free(data->enemyExtraData);
}

