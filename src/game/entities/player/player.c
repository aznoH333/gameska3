#include "player.h"
#include "gameLib/gamelibInclude.h"
#include "stdlib.h"
#include "game/systemsInclude.h"

void PlayerUpdate(WorldObject* this, PlayerData* data);

void PlayerInit(float x, float y){
    // init gameobject
    WorldObject* playerWorldObject = InitWorldObject(x, y, 32, 32);
    playerWorldObject->spriteIndex = getSpriteIndex("debug_man");

    // controller
    ObjectController* controller = ObjectControllerInit();
    controller->objectUpdate = (void (*)(WorldObject *, void *))&PlayerUpdate;

    PlayerData* data = malloc(sizeof(PlayerData));
    data->xVelocity = 0;
    data->yVelocity = 0;


    GameObjectCreate(playerWorldObject, controller, data);
}


#define PLAYER_SPEED_MULTIPLIER 2.0f
#define PLAYER_SPEED_BUILDUP 0.07f

void PlayerUpdate(WorldObject* this, PlayerData* data){
    


    // movement input
    if (IsKeyDown(KEY_D) == IsKeyDown(KEY_A)){
        data->xVelocity = limitedIncrement(data->xVelocity, 0.0f, PLAYER_SPEED_BUILDUP);
    }else if (IsKeyDown(KEY_D)){
        data->xVelocity = limitedIncrement(data->xVelocity, 1.0f, PLAYER_SPEED_BUILDUP);
    }else if (IsKeyDown(KEY_A)){
        data->xVelocity = limitedIncrement(data->xVelocity, -1.0f, PLAYER_SPEED_BUILDUP);
    }


    if (IsKeyDown(KEY_W) == IsKeyDown(KEY_S)){
        data->yVelocity = limitedIncrement(data->yVelocity, 0.0f, PLAYER_SPEED_BUILDUP);
    }else if (IsKeyDown(KEY_W)){
        data->yVelocity = limitedIncrement(data->yVelocity, -1.0f, PLAYER_SPEED_BUILDUP);
    }else if (IsKeyDown(KEY_S)) {
        data->yVelocity = limitedIncrement(data->yVelocity, 1.0f, PLAYER_SPEED_BUILDUP);
    }


    // terrain collisions
    float xCollisionCheck = this->x + (data->xVelocity * PLAYER_SPEED_MULTIPLIER);
    if (collidesWithTerrain(xCollisionCheck, this->y, this->width, this->height)){
        data->xVelocity = 0;
    }


    float yCollisionCheck = this->y + (data->yVelocity * PLAYER_SPEED_MULTIPLIER);
    if (collidesWithTerrain(this->x, yCollisionCheck, this->width, this->height)){
        data->yVelocity = 0;
    }



    // update position
    this->x += data->xVelocity * PLAYER_SPEED_MULTIPLIER;
    this->y += data->yVelocity * PLAYER_SPEED_MULTIPLIER;


    // camera follow
    setCameraTarget(this->x, this->y);



    // gun
    // temp
    float gunDirection = directionTowards(this->x, this->y, getInWorldMousePositionX(), getInWorldMousePositionY());
    spriteDrawBasic("debug_gun", getInWorldMousePositionX(), getInWorldMousePositionY(), FLIP_NONE, 1);
    spriteDraw("debug_gun", this->x, this->y, FLIP_NONE, gunDirection, 1.0f, 1.0f, WHITE, 1, false);

}