#include "font.h"
#include "debug.h"
#include "vector.h"
#include <raylib.h>
#include <stdio.h>
#include "stdlib.h"

#define MAX_STRING_LENGTH 255


Vector* fontQueue;

struct FontDrawData{
    char text[MAX_STRING_LENGTH];
    float x;
    float y;
    float scale;
    Color color;
};typedef struct FontDrawData FontDrawData;

Font font;

void FontLoad(){
    font = LoadFont("./resources/font/font.png");
    fontQueue = VectorInit();
}


void FontUnload(){
    UnloadFont(font);

    VectorFreeValues(fontQueue);
}


void FontDraw(const char* text, float x, float y, float scale, Color color, ...){
    FontDrawData* data = malloc(sizeof(FontDrawData));

    va_list args;
    va_start(args, color);
    vsprintf(data->text, text, args);
    va_end(args);

    data->x = x;
    data->y = y;
    data->scale = scale * 15 * 3;
    data->color = color;

    VectorAdd(fontQueue, data);
}


void DrawFontBatch(){
    for (int i = 0; i < fontQueue->elementCount; i++){
        FontDrawData* data = VectorGet(fontQueue, i);
        DrawTextPro(font, data->text, (Vector2){data->x, data->y}, (Vector2){0,0}, 0.0f, data->scale, 1.0f, data->color);
        free(data);
    }

    VectorClear(fontQueue);
}