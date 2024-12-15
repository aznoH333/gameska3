#include "sprites.h"
#include "sprites.h"
#include "fileUtils.h"
#include <stdlib.h>
#include "debug.h"
#include "vector.h"


struct DrawData{
    int spriteIndex;
    float x;
    float y; 
    SpriteFlip flip; 
    float rotation;
    float width; 
    float height; 
    Color color;
    bool isStatic;
};


struct TexturePair{
    char* name;
    Texture2D texture;
};


#define MAX_LOADED_TEXTURES 255
#define MAX_SUPPORTED_LAYERS 8

struct TexturePair textureAtlas[MAX_LOADED_TEXTURES];
Vector* drawQueue[MAX_SUPPORTED_LAYERS];
Vector* staticDrawQueue[MAX_SUPPORTED_LAYERS];

int loadedTextures;


void spritesLoadAll(){
    // load sprites
    Vector* spritePaths = getFilesInFolder("./resources/sprites");
    loadedTextures = 0;

    for (int i = 0; i < spritePaths->elementCount; i++){
        if (i > MAX_LOADED_TEXTURES){
            crashMessage("Loaded textures exceeded max textures [%d]", MAX_LOADED_TEXTURES);
        }
        debugMessage("Loaded texture [%s]", VectorGet(spritePaths, i));
        textureAtlas[i] = (struct TexturePair){VectorGet(spritePaths, i), LoadTexture(VectorGet(spritePaths, i))};
    }
    VectorFree(spritePaths);

    // init draw queue
    for (int i = 0; i < MAX_SUPPORTED_LAYERS; i++){
        drawQueue[i] = VectorInit();
        staticDrawQueue[i] = VectorInit();
    }
}


void spritesUnloadAll(){
    for (int i = 0; i < loadedTextures; i++){
        UnloadTexture(textureAtlas[i].texture);
        free(textureAtlas[i].name);
    }

    // unload drawQueue
    for (int i = 0; i < MAX_SUPPORTED_LAYERS; i++){
        VectorFree(drawQueue[i]);
        VectorFree(staticDrawQueue[i]);
    }
}


int findSpriteIndex(const char* spriteName){
    for (int i = 0; i < loadedTextures; i++){
        if (TextIsEqual(textureAtlas[i].name, spriteName)){
            return i;
        }
    }
    crashMessage("Texture [%s] not found", spriteName);
    return -1;
}


void spriteDraw(const char* spriteName, float x, float y, SpriteFlip flip, float rotation, float width, float height, Color color, int layer, bool isStatic){
    if (layer < 0 || layer > MAX_SUPPORTED_LAYERS){
        crashMessage("Draw call invalid [%s], layer[%d] outside of allowed range [0...%d]", spriteName, layer, MAX_SUPPORTED_LAYERS);
    }

    struct DrawData* data = malloc(sizeof(struct DrawData));
    data->spriteIndex = findSpriteIndex(spriteName);
    data->x = x;
    data->y = y;
    data->flip = flip;
    data->rotation = rotation;
    data->color = color;
    data->width = width;
    data->height = height;
    data->isStatic = isStatic;

    

    if (isStatic){
        VectorAdd(staticDrawQueue[layer], data);
    }else {
        VectorAdd(drawQueue[layer], data);
    }
}


void spriteDrawBasic(const char* spriteName, float x, float y, SpriteFlip flip, int layer){
    spriteDraw(spriteName, x, y, flip, 0.0f, 1.0f, 1.0f, WHITE, layer, false);
}


void drawSprite(struct DrawData* data){
    // TODO
}


void drawSpriteBatch(Camera2D* camera){
    // TODO
}
