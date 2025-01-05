#include "enemyGrunt.h"
#include "enemy.h"
#include <stdlib.h>


void extraGruntUpdate(WorldObject* this, EnemyData* data, EnemyGruntData* extraData);


void InitEnemyGrunt(float x, float y){
    EnemyGruntData* extraData = malloc(sizeof(EnemyGruntData));
    GenericEnemyInit(x, y, 32, 32, getSpriteIndex("debug_enemy"), ENEMY_TYPE_GRUNT, (EnemyExtraUpdate)&extraGruntUpdate, extraData);
}


void extraGruntUpdate(WorldObject* this, EnemyData* data, EnemyGruntData* extraData){
    // temporary
    this->x += 0.1f;
}
