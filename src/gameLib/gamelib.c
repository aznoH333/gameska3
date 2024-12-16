#include "gamelib.h"
#include "sprites.h"
#include <raylib.h>


Camera2D cam;

void gameLibInit(){
    spritesLoadAll();
    cam.target = (Vector2){0, 0};
    cam.zoom = 1.0f;
}


void gameLibEnd(){
    spritesUnloadAll();
}

void gameLibUpdate(){
    drawSpriteBatch(&cam);
}
