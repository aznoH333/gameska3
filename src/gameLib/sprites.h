#ifndef SPRITES
#define SPRITES

#include "raylib.h"


enum SpriteFlip {
    NONE,
    X,
    Y,
    BOTH,
};
typedef enum SpriteFlip SpriteFlip ;


void spritesLoadAll();
void spritesUnloadAll();

void spriteDraw(const char* spriteName, float x, float y, SpriteFlip flip, float rotation, float width, float height, Color color, int layer, bool isStatic);
void spriteDrawBasic(const char* spriteName, float x, float y, SpriteFlip flip, int layer);

#endif