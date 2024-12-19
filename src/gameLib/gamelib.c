#include "gamelib.h"
#include "sprites.h"
#include <raylib.h>
#include "worldObjectManager.h"


Camera2D cam;

void gameLibInit(){
    spritesLoadAll();
    cam.target = (Vector2){0, 0};
    cam.zoom = 1.0f;

    WorldObjectManagerInit();
}


void gameLibEnd(){
    WorldObjectManagerDispose();
    spritesUnloadAll();

}

void gameLibUpdate(){
    WorldObjectManagerUpdate();

    drawSpriteBatch(&cam);
}
