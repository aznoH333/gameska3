#include "gamelib.h"
#include "sprites.h"
#include <raylib.h>
#include "worldObjectManager.h"
#include "objectControllerManager.h"
#include "objectDataManager.h"
#include "vector.h"


Camera2D cam;
Vector* additionalSystems;


void gameLibInit(){
    spritesLoadAll();
    additionalSystems = VectorInit();
    cam.target = (Vector2){0, 0};
    cam.zoom = 1.0f;

    WorldObjectManagerInit();
    ObjectControllerManagerInit();
    ObjectDataManagerInit();
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
    drawSpriteBatch(&cam);

    // additional updates
    for (int i = 0; i < additionalSystems->elementCount; i++){
        ((void (*)())VectorGet(additionalSystems, i))();
    }
}
