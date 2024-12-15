#include "gamelib.h"
#include "sprites.h"


void gameLibInit(){
    spritesLoadAll();
}


void gameLibEnd(){
    spritesUnloadAll();
}