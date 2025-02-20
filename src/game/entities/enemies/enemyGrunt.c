#include "enemyGrunt.h"
#include "enemy.h"
#include <stdlib.h>
#include "game/gameEnums/enumsInclude.h"
#include "math.h"
#include "game/systemsInclude.h"


#define GRUNT_SPEED 1.8f

void extraGruntUpdate(WorldObject* this, EnemyData* data, EnemyGruntData* extraData);
void extraGruntCollisionUpdate(WorldObject* this, EnemyData* data, EnemyGruntData* extraData, WorldObject* other);


const char* enemyAnimationLookup[] = {
    "enemy_0001",
    "enemy_0002",
    "enemy_0003",
    "enemy_0004",
    "enemy_0005",
    "enemy_0006",
    "enemy_0007",
    "enemy_0008",

};


void InitEnemyGrunt(float x, float y){
    EnemyGruntData* extraData = malloc(sizeof(EnemyGruntData));
    
    extraData->collisionPushForceX = 0;
    extraData->collisionPushForceY = 0;

    GenericEnemyInit(x, y, 32, 32, getSpriteIndex("enemy_0001"), 50.0f, ENEMY_TYPE_GRUNT, (EnemyExtraUpdate)&extraGruntUpdate, (EnemyExtraCollisionUpdate)&extraGruntCollisionUpdate, extraData);
}


void extraGruntUpdate(WorldObject* this, EnemyData* data, EnemyGruntData* extraData){
    // navigate to player
    WorldObject* player = WorldObjectManagerGetClosestObjectInRange(this, OBJECT_TAG_PLAYER, UNDEFINED);
    float xSpeed = 0.0f;
    float ySpeed = 0.0f;


    if (player != UNDEFINED && data->stunTimer == 0){

        float directionToPlayer = directionTowards(this->x, this->y, player->x, player->y);
        xSpeed = cosf(directionToPlayer) * GRUNT_SPEED;
        ySpeed = sinf(directionToPlayer) * GRUNT_SPEED;


        if (xSpeed < -0.5f){
            this->flip = FLIP_X;
        }else if (xSpeed > 0.5f){
            this->flip = FLIP_NONE;
        }

        // TODO : bring back pathfinding
    }else if (data->stunTimer != 0){
        data->stunTimer--;
        xSpeed = data->stunPushX;
        ySpeed = data->stunPushY;
        data->stunPushX /= 1.5f;
        data->stunPushY /= 1.5f;
    }


    xSpeed += extraData->collisionPushForceX;
    ySpeed += extraData->collisionPushForceY;
    extraData->collisionPushForceX = 0;
    extraData->collisionPushForceY = 0;

    if (
        TerrainCheckCollisions(this->x + xSpeed, this->y, this->width, this->height)
    ){
        xSpeed = 0;
        ySpeed = sign(ySpeed) * GRUNT_SPEED;
    }

    if (
        TerrainCheckCollisions(this->x, this->y + ySpeed, this->width, this->height)
    ){
        ySpeed = 0;
        xSpeed = sign(xSpeed) * GRUNT_SPEED;
    }


    this->x += xSpeed;
    this->y += ySpeed;
    data->xMovement = xSpeed;
    data->yMovement = ySpeed;

    
    // update animation
    if (data->stunTimer != 0){
        this->spriteIndex = getSpriteIndex(enemyAnimationLookup[7]);
    }
    else if (xSpeed == 0 && ySpeed == 0){
        this->spriteIndex = getSpriteIndex(enemyAnimationLookup[0]);
    }else {
        this->spriteIndex = getSpriteIndex(enemyAnimationLookup[(getGlobalTimer() / 2) % 7]);
    }

    

    // TODO : dealing damage
}


void extraGruntCollisionUpdate(WorldObject* this, EnemyData* data, EnemyGruntData* extraData, WorldObject* other){
    if (other->objectTag == OBJECT_TAG_ENEMY){
        float directionToOther = directionTowards(other->x, other->y, this->x, this->y);

        extraData->collisionPushForceX += cos(directionToOther) * 0.75f;
        extraData->collisionPushForceY += sin(directionToOther) * 0.75f;

    }
}

