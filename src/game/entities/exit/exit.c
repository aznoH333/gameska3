#include "exit.h"


#include "gameLib/gamelibInclude.h"
#include "game/gameEnums/enumsInclude.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include "game/entitiesInclude.h"
#include "game/systems/playerManager.h"
#include "game/systems/gamestateManager.h"
#include "game/systems/terrainSystem.h"

void ExitUpdate(WorldObject* this, ExitData* data);
void ExitCollide(WorldObject* this, ExitData* data, WorldObject* other);

void ExitInit(float x, float y, bool open){
    WorldObject* this = InitWorldObjectT(x, y, 32, 20, OBJECT_TAG_NEUTRAL);
    this->checkCollisions = false;
    this->spriteIndex = getSpriteIndex("exit_0001");


    ExitData* data = malloc(sizeof(ExitData));
    data->isOpen = false;
    data->wantsToOpen = open;


    ObjectController* controller = ObjectControllerInit();
    controller->objectUpdate = (ControllerUpdateFunction)&ExitUpdate;
    controller->objectCollide = (ControllerCollideFunction)&ExitCollide;

    GameObjectCreate(this, controller, data);
    RegisterExit(this);
}


void ExitUpdate(WorldObject* this, ExitData* data){
    if (data->isOpen){
        FontDrawInWorld("exit", this->x - 32, this->y, 1.0f, YELLOW);
    }
    
    
    
    if (!data->wantsToOpen){
        return;
    }

    WorldObject* player = PlayerManagerGetPlayer();


    if (distanceTo(this->x, this->y, player->x, player->y) > 60){
        this->spriteIndex = getSpriteIndex("exit_0002");
        this->checkCollisions = true;
        data->isOpen = true;
    }
}

void ExitOpen(WorldObject* exit){
    ExitData* data = GameObjectGetData(exit);
    data->wantsToOpen = true;
    
}


void ExitCollide(WorldObject* this, ExitData* data, WorldObject* other){
    if (data->isOpen && other->objectTag == OBJECT_TAG_PLAYER){
        GameStateProgressLevel();
    }
}