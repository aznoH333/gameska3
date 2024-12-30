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

    PlayerData* peanis = malloc(sizeof(PlayerData));
    peanis->test = 26;


    GameObjectCreate(playerWorldObject, controller, peanis);
}

void PlayerUpdate(WorldObject* this, PlayerData* data){
    if (IsKeyDown(KEY_A)){
        data->test++;
    }
    this->x = data->test;
}