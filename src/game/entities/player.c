#include "game/entities/player.h"
#include "gameLib/gamelibInclude.h"
#include "stdlib.h"

void PlayerUpdate(WorldObject* this, PlayerData* data);

void PlayerInit(float x, float y){
    // init gameobject
    WorldObject* playerWorldObject = InitWorldObject(x, y, 16, 16);
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


    // update position
    this->x += data->xVelocity * PLAYER_SPEED_MULTIPLIER;
    this->y += data->yVelocity * PLAYER_SPEED_MULTIPLIER;

}