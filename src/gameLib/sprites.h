#ifndef SPRITES
#define SPRITES

#include "raylib.h"


enum SpriteFlip {
    FLIP_NONE,
    FLIP_X,
    FLIP_Y,
    FLIP_BOTH,
};
typedef enum SpriteFlip SpriteFlip ;


void spritesLoadAll();
void spritesUnloadAll();

void spriteDraw(const char* spriteName, float x, float y, SpriteFlip flip, float rotation, float width, float height, Color color, int layer, bool isStatic);
void spriteDrawIndexed(int spriteIndex, float x, float y, SpriteFlip flip, float rotation, float width, float height, Color color, int layer, bool isStatic);
int getSpriteIndex(const char* spriteName);
void spriteDrawBasic(const char* spriteName, float x, float y, SpriteFlip flip, int layer);
void drawSpriteBatch(Camera2D* camera);

#endif