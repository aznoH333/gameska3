#include "sprites.h"


void spritesLoadAll();
void spritesUnloadAll();

void spriteDraw(const char* spriteName, float x, float y, SpriteFlip flip, float rotation, float width, float height, Color color, int layer, bool isStatic);
void spriteDrawBasic(const char* spriteName, float x, float y, SpriteFlip flip, int layer);