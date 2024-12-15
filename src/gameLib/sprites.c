#include "sprites.h"
#include "sprites.h"
#include "fileUtils.h"
#include <stdlib.h>
#include "debug.h"


#define MAX_LOADED_TEXTURES 255

Texture2D textureAtlas[MAX_LOADED_TEXTURES];
int loadedTextures;


void spritesLoadAll(){
    Vector* spritePaths = getFilesInFolder("./resources/sprites");
    loadedTextures = 0;

    for (int i = 0; i < spritePaths->elementCount; i++){
        if (i > MAX_LOADED_TEXTURES){
            crashMessage("Loaded textures exceeded max textures [%d]", MAX_LOADED_TEXTURES);
        }
        debugMessage("Loaded texture [%s]", VectorGet(spritePaths, i));
        textureAtlas[i] = LoadTexture(VectorGet(spritePaths, i));
        free(VectorGet(spritePaths, i));
    }
    VectorFree(spritePaths);
}


void spritesUnloadAll(){
    for (int i = 0; i < loadedTextures; i++){
        UnloadTexture(textureAtlas[i]);
    }
}

void spriteDraw(const char* spriteName, float x, float y, SpriteFlip flip, float rotation, float width, float height, Color color, int layer, bool isStatic);
void spriteDrawBasic(const char* spriteName, float x, float y, SpriteFlip flip, int layer);