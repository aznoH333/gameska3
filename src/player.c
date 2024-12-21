#include "player.h"
#include "objectLifecycleOrchestrator.h"
#include "sprites.h"


void PlayerInit(float x, float y){
    // init gameobject
    WorldObject* playerWorldObject = InitWorldObject(x, y, 16, 16);
    playerWorldObject->spriteIndex = getSpriteIndex("debug_man");
}