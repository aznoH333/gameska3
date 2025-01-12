#include "enemyGrunt.h"
#include "enemy.h"
#include <stdlib.h>
#include "game/gameEnums/enumsInclude.h"
#include "math.h"
#include "game/systemsInclude.h"


#define GRUNT_SPEED 1.8f

void extraGruntUpdate(WorldObject* this, EnemyData* data, EnemyGruntData* extraData);


void InitEnemyGrunt(float x, float y){
    EnemyGruntData* extraData = malloc(sizeof(EnemyGruntData));
    GenericEnemyInit(x, y, 32, 32, getSpriteIndex("debug_enemy"), 50.0f, ENEMY_TYPE_GRUNT, (EnemyExtraUpdate)&extraGruntUpdate, extraData);
}


void extraGruntUpdate(WorldObject* this, EnemyData* data, EnemyGruntData* extraData){
    // navigate to player
    WorldObject* player = WorldObjectManagerGetClosestObjectInRange(this, OBJECT_TAG_PLAYER, UNDEFINED);
    float xSpeed = 0.0f;
    float ySpeed = 0.0f;


    if (player != UNDEFINED){

        if (TerrainCheckForLineOfSight(this->x, this->y, this->width, this->height, player->x, player->y)){

            float directionToPlayer = directionTowards(this->x, this->y, player->x, player->y);
            xSpeed = cosf(directionToPlayer) * GRUNT_SPEED;
            ySpeed = sinf(directionToPlayer) * GRUNT_SPEED;


        }else {
            PathFindingOutput pathFindingResult = TerrainPathFindTowards(this->x, this->y, player->x, player->y);

            if (pathFindingResult.canReach){
                float dirToNext = directionTowards(this->x, this->y, pathFindingResult.nextX, pathFindingResult.nextY);
                
                xSpeed = cosf(dirToNext) * GRUNT_SPEED;
                ySpeed = sinf(dirToNext) * GRUNT_SPEED;

            }
            
        }

    }

    this->x += xSpeed;
    this->y += ySpeed;
    
    // TODO : dealing damage
}
