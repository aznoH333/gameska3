#include "gamelib.h"
#include "sprites.h"
#include <raylib.h>
#include "worldObjectManager.h"
#include "objectControllerManager.h"
#include "objectDataManager.h"


Camera2D cam;


void gameLibInit(){
    spritesLoadAll();
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

}


void gameLibUpdate(){
    WorldObjectManagerUpdate();

    drawSpriteBatch(&cam);
}
