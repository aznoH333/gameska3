#ifndef FONT 
#define FONT 

#include "raylib.h"

void FontLoad();
void FontUnload();
void FontDraw(const char* text, float x, float y, float scale, Color color, ...);
void DrawFontBatch();

#endif