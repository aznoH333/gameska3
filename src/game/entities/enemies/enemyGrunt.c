#include "enemyGrunt.h"
#include "enemy.h"
#include <stdlib.h>
#include "game/gameEnums/enumsInclude.h"
#include "math.h"


#define GRUNT_SPEED 1.8f

void extraGruntUpdate(WorldObject* this, EnemyData* data, EnemyGruntData* extraData);


void InitEnemyGrunt(float x, float y){
    EnemyGruntData* extraData = malloc(sizeof(EnemyGruntData));
    GenericEnemyInit(x, y, 32, 32, getSpriteIndex("debug_enemy"), ENEMY_TYPE_GRUNT, (EnemyExtraUpdate)&extraGruntUpdate, extraData);
}


void extraGruntUpdate(WorldObject* this, EnemyData* data, EnemyGruntData* extraData){
    // navigate to player
    WorldObject* player = WorldObjectManagerGetClosestObjectInRange(this, OBJECT_TAG_PLAYER, UNDEFINED);

    if (player != UNDEFINED){
        float directionToPlayer = directionTowards(this->x, this->y, player->x, player->y);

        this->x += cosf(directionToPlayer) * GRUNT_SPEED;
        this->y += sinf(directionToPlayer) * GRUNT_SPEED;
    }
    
    
    
    // TODO : pathfinding
    // TODO : taking damage
    // TODO : dealing damage
}