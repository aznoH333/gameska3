#ifndef TERRAIN_SYSTEM
#define TERRAIN_SYSTEM

#include <stdbool.h>

void TerrainGenerateNewRoom();
bool TerrainCheckCollisions(float x, float y, float w, float h);
void TerrainUpdate();
void TerrainCheckForLineOfSight(float x, float y, float targetX, float targetY);

#endif