#ifndef TERRAIN_SYSTEM
#define TERRAIN_SYSTEM

#include <stdbool.h>

struct PathFindingOutput{
    bool canReach;
    int nextX;
    int nextY;
}; typedef struct PathFindingOutput PathFindingOutput ;

void TerrainGenerateNewRoom();
bool TerrainCheckCollisions(float x, float y, float w, float h);
void TerrainUpdate();
bool TerrainCheckForLineOfSight(float x, float y, float w, float h, float targetX, float targetY);
PathFindingOutput* TerrainPathFindTowards(float x, float y, float targetX, float targetY);

#endif