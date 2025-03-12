#include "sprites.h"
#include "fileUtils.h"
#include <raylib.h>
#include <stdlib.h>
#include "debug.h"
#include "vector.h"
#include "screenUtils.h"
#include "stringUtils.h"
#include "numberUtils.h"
#include "font.h"
#include "worldSpaceUtils.h"
#include "GL/gl.h"

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
Vector* loadedShaders;
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

    // shaders
    loadedShaders = VectorInit();
}


void spritesUnloadAll(){
    for (int i = 0; i < loadedTextures; i++){
        UnloadTexture(textureAtlas[i].texture);
        free(textureAtlas[i].name);
    }

    // unload drawQueue
    for (int i = 0; i < MAX_SUPPORTED_LAYERS; i++){
        VectorFreeValues(drawQueue[i]);
        VectorFreeValues(staticDrawQueue[i]);
    }

    // unload render texture
    UnloadRenderTexture(renderTexture);


    // unload shaders
    for (int i = 0; i < loadedShaders->elementCount; i++){
        Shader* shader = VectorGet(loadedShaders, i);
        UnloadShader(*shader);
        free(shader);
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
    spriteDrawIndexed(findSpriteIndex(spriteName), x, y, flip, rotation, width, height, color, layer, isStatic);
}


void spriteDrawBasic(const char* spriteName, float x, float y, SpriteFlip flip, int layer){
    spriteDraw(spriteName, x, y, flip, 0.0f, 1.0f, 1.0f, WHITE, layer, false);
}


bool isSpriteOnScreen(float x, float y, int width, int height, Camera2D* camera){
    float camX = camera->target.x - (camera->offset.x * camera->zoom);
    float camY = camera->target.y - (camera->offset.y * camera->zoom);
    float camWidth = (camera->offset.x * 2 * camera->zoom);
    float camHeight = (camera->offset.y * 2 * camera->zoom);
    
    return squaresCollide(x, y, width, height, camX, camY, camWidth, camHeight);
}


void drawSprite(struct DrawData* data, Camera2D* camera){
    Texture2D* texture = &textureAtlas[data->spriteIndex].texture;
    float originOffsetX = (texture->width * data->width) / 2;
    float originOffsetY = (texture->height * data->height) / 2;

    bool flipX = data->flip == FLIP_X || data->flip == FLIP_BOTH;
    bool flipY = data->flip == FLIP_Y || data->flip == FLIP_BOTH;

    if (!isSpriteOnScreen(data->x, data->y, texture->width, texture->height, camera) && !data->isStatic){
        free(data);
        return;
    }

    
    DrawTexturePro(*texture, 
    (Rectangle){0, 0, texture->width * boolToSign(!flipX), texture->height * boolToSign(!flipY)}, 
    (Rectangle){data->x + originOffsetX, data->y + originOffsetY, textureAtlas[data->spriteIndex].texture.width * data->width, textureAtlas[data->spriteIndex].texture.height * data->height}, 
    (Vector2) {originOffsetX, originOffsetY}, data->rotation * RAD2DEG, data->color);
    free(data);
}


void drawSpriteBatch(Camera2D* camera){
    BeginTextureMode(renderTexture);
    ClearBackground(BLACK);
    
    BeginDrawing();
    // start shaders
    for (int i = 0; i < loadedShaders->elementCount; i++){
        BeginShaderMode(*((Shader*)VectorGet(loadedShaders, i)));
    }

    BeginMode2D(*camera);

    // normal sprites
    for (int i = 0; i < MAX_SUPPORTED_LAYERS; i++){
        for (int j = 0; j < drawQueue[i]->elementCount; j++){
            struct DrawData* data = VectorGet(drawQueue[i], j);
            drawSprite(data, camera);
        }
        VectorClear(drawQueue[i]);
    }
    DrawFontInWorldBatch();
    EndMode2D();


    // static sprites
    for (int i = 0; i < MAX_SUPPORTED_LAYERS; i++){
        for (int j = 0; j < staticDrawQueue[i]->elementCount; j++){
            struct DrawData* data = VectorGet(staticDrawQueue[i], j);
            drawSprite(data, camera);
        }
        VectorClear(staticDrawQueue[i]);
    }

    DrawFontBatch();
    
    // end shaders
    for (int i = 0; i < loadedShaders->elementCount; i++){
        EndShaderMode();
    }
    EndTextureMode();
    
    BeginDrawing();
    
    DrawTexturePro(renderTexture.texture,
    (Rectangle) {0,renderTexture.texture.height, renderTexture.texture.width, -renderTexture.texture.height} ,
    (Rectangle) {0,0, getWindowWidth(), getWindowHeight()}, 
    (Vector2) {0,0}, 0, WHITE);

    EndDrawing();
    glFlush(); // TODO : this sucks
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


void registerShader(const char* shaderPath, ShaderType shaderType){
    Shader shader;

    switch (shaderType) {
        case SHADER_FRAGMENT:
            shader = LoadShader(0, shaderPath);
            break;
        case SHADER_VERTEX:
            shader = LoadShader(shaderPath, 0);
            break;
    }

    if (!IsShaderReady(shader)){
        crashMessage("failed to load shader [%s]", shaderPath);
    }

    Shader* s = malloc(sizeof(shader));
    s->id = shader.id;
    s->locs = shader.locs;

    VectorAdd(loadedShaders, s);
}
