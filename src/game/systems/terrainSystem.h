#ifndef TERRAIN_SYSTEM
#define TERRAIN_SYSTEM

#include <stdbool.h>

void TerrainGenerateNewRoom();
bool TerrainCheckCollisions(float x, float y, float w, float h);
void TerrainUpdate();
bool TerrainCheckForLineOfSight(float x, float y, float w, float h, float targetX, float targetY);

#endif