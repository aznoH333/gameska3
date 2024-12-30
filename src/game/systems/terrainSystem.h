#ifndef TERRAIN_SYSTEM
#define TERRAIN_SYSTEM

#include <stdbool.h>

void generateNewRoom();
bool collidesWithTerrain(float x, float y, float w, float h);
void terrainUpdate();

#endif