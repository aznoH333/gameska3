#include "sprites.h"
#include "sprites.h"
#include "fileUtils.h"
#include <raylib.h>
#include <stdlib.h>
#include "debug.h"
#include "vector.h"
#include "screenUtils.h"
#include "stringUtils.h"

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
RenderTexture2D renderTexture;

int loadedTextures;


void spritesLoadAll(){
    // load sprites
    Vector* spritePaths = getFilesInFolder("./resources/sprites");
    loadedTextures = 0;

    for (int i = 0; i < spritePaths->elementCount; i++){
        if (i > MAX_LOADED_TEXTURES){
            crashMessage("Loaded textures exceeded max textures [%d]", MAX_LOADED_TEXTURES);
        }

        char* path = VectorGet(spritePaths, i);
        int indexOf = StringLastIndexOf(path, "/");

        char* textureFileName = StringSubstring(path, indexOf + 1, StringLength(path) - indexOf);
        char* textureName = StringSubstring(textureFileName, 0, StringIndexOf(textureFileName, "."));
        
        debugMessage("Loaded texture [%s] with name [%s]", VectorGet(spritePaths, i), textureName);
        
        textureAtlas[i] = (struct TexturePair){textureName, LoadTexture(VectorGet(spritePaths, i))};

        free(path);
        free(textureFileName);

        loadedTextures++;

    }
    VectorFree(spritePaths);

    // init draw queue
    for (int i = 0; i < MAX_SUPPORTED_LAYERS; i++){
        drawQueue[i] = VectorInit();
        staticDrawQueue[i] = VectorInit();
    }

    // render texture
    renderTexture = LoadRenderTexture(getWindowWidth(), getWindowHeight());
}


void spritesUnloadAll(){
    for (int i = 0; i < loadedTextures; i++){
        debugMessage("unloading texture [%s]", textureAtlas[i].name);
        UnloadTexture(textureAtlas[i].texture);
        free(textureAtlas[i].name);
    }

    // unload drawQueue
    for (int i = 0; i < MAX_SUPPORTED_LAYERS; i++){
        VectorFree(drawQueue[i]);
        VectorFree(staticDrawQueue[i]);
    }

    // unload render texture
    UnloadRenderTexture(renderTexture);
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
    spriteDrawIndexed(findSpriteIndex(spriteName), x, y, flip, rotation, width, height, color, layer, isStatic);
}


void spriteDrawBasic(const char* spriteName, float x, float y, SpriteFlip flip, int layer){
    spriteDraw(spriteName, x, y, flip, 0.0f, 1.0f, 1.0f, WHITE, layer, false);
}


void drawSprite(struct DrawData* data){
    DrawTexturePro(textureAtlas[data->spriteIndex].texture, 
    (Rectangle){0, 0, textureAtlas[data->spriteIndex].texture.width, textureAtlas[data->spriteIndex].texture.height}, 
    (Rectangle){data->x, data->y, textureAtlas[data->spriteIndex].texture.width * data->width, textureAtlas[data->spriteIndex].texture.height * data->height}, 
    (Vector2) {data->width / 2}, data->height / 2, data->color);
}


void drawSpriteBatch(Camera2D* camera){
    BeginTextureMode(renderTexture);
    ClearBackground(WHITE);
    
    BeginDrawing();
    BeginMode2D(*camera);

    // normal sprites
    for (int i = 0; i < MAX_SUPPORTED_LAYERS; i++){
        for (int j = 0; j < drawQueue[i]->elementCount; j++){
            struct DrawData* data = VectorGet(drawQueue[i], j);
            drawSprite(data);
            free(data);
        }
        VectorClear(drawQueue[i]);
    }

    EndMode2D();

    // static sprites
    for (int i = 0; i < MAX_SUPPORTED_LAYERS; i++){
        for (int j = 0; j < staticDrawQueue[i]->elementCount; j++){
            struct DrawData* data = VectorGet(staticDrawQueue[i], j);
            drawSprite(data);
            free(data);
        }
        VectorClear(staticDrawQueue[i]);
    }

    EndTextureMode();
    
    BeginDrawing();
    
    DrawTexturePro(renderTexture.texture,
    (Rectangle) {0,renderTexture.texture.height, renderTexture.texture.width, -renderTexture.texture.height} ,
    (Rectangle) {0,0, GetScreenWidth(), GetScreenHeight()}, 
    (Vector2) {0,0}, 0, WHITE);

    EndDrawing();
}


void spriteDrawIndexed(int spriteIndex, float x, float y, SpriteFlip flip, float rotation, float width, float height, Color color, int layer, bool isStatic){
    if (layer < 0 || layer > MAX_SUPPORTED_LAYERS){
        crashMessage("Draw call invalid [%d], layer[%d] outside of allowed range [0...%d]", spriteIndex, layer, MAX_SUPPORTED_LAYERS);
    }

    struct DrawData* data = malloc(sizeof(struct DrawData));
    data->spriteIndex = spriteIndex;
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


int getSpriteIndex(const char* spriteName){
    return findSpriteIndex(spriteName);
}