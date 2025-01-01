#include "gamelib.h"
#include "sprites.h"
#include <raylib.h>
#include "worldObjectManager.h"
#include "objectControllerManager.h"
#include "objectDataManager.h"
#include "vector.h"
#include "camera.h"


unsigned int timer;
Vector* additionalSystems;


void gameLibInit(){
    spritesLoadAll();
    additionalSystems = VectorInit();
    timer = 0;

    WorldObjectManagerInit();
    ObjectControllerManagerInit();
    ObjectDataManagerInit();
    resetCamera();
}


void gameLibEnd(){
    WorldObjectManagerDispose();
    spritesUnloadAll();
    ObjectControllerManagerDispose();
    ObjectDataManagerDispose();
    VectorFree(additionalSystems);
}


void gameLibRegisterAdditionalSystem(void (*systemUpdateFunction)()){
    VectorAdd(additionalSystems, systemUpdateFunction);
}



void gameLibUpdate(){
    WorldObjectManagerUpdate();
    updateCamera();
    drawSpriteBatch(getCamera());

    // additional updates
    for (int i = 0; i < additionalSystems->elementCount; i++){
        ((void (*)())VectorGet(additionalSystems, i))();
    }

    timer++;
}

unsigned int getGlobalTimer(){
    return timer;
}

