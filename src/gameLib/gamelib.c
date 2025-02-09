#include "gamelib.h"
#include "memoryMacros.h"
#include "sprites.h"
#include <raylib.h>
#include "worldObjectManager.h"
#include "objectControllerManager.h"
#include "objectDataManager.h"
#include "vector.h"
#include "camera.h"
#include "sounds.h"
#include "font.h"


unsigned int timer;
Vector* additionalSystems;
Vector* initEvents = UNDEFINED;
Vector* disposeEvents;


void gameLibRegisterInitEvent(void (*systemInitFunction)()){
    if (initEvents == UNDEFINED){
        initEvents = VectorInit();
    }

    VectorAdd(initEvents, systemInitFunction);
}


void gameLibRegisterDisposeEvent(void (*systemDisposeFunction)()){
    VectorAdd(disposeEvents, systemDisposeFunction);
}



void gameLibInit(){
    spritesLoadAll();
    FontLoad();
    soundsLoadAll();
    additionalSystems = VectorInit();
    disposeEvents = VectorInit();
    timer = 0;

    WorldObjectManagerInit();
    ObjectControllerManagerInit();
    ObjectDataManagerInit();
    resetCamera();

    // call init events
    if (initEvents == UNDEFINED){
        return;
    }
    for (int i = 0; i < initEvents->elementCount; i++){
        void (*systemInitFunction)() = VectorGet(initEvents, i);
        systemInitFunction();
    }
}


void gameLibEnd(){
    for (int i = 0; i < disposeEvents->elementCount; i++){
        void (*systemDisposeFunction)() = VectorGet(disposeEvents, i);
        systemDisposeFunction();
    }
    
    WorldObjectManagerDispose();
    spritesUnloadAll();
    FontUnload();
    soundsUnloadAll();
    ObjectDataManagerDispose();
    ObjectControllerManagerDispose();

    

    VectorFree(additionalSystems);
    VectorFree(disposeEvents);
    VectorFree(initEvents);
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

