#ifndef TERRAIN_SYSTEM
#define TERRAIN_SYSTEM

#include <stdbool.h>
#include "../../gameLib/gamelibInclude.h"

struct PathFindingOutput{
    bool canReach;
    int nextX;
    int nextY;
}; typedef struct PathFindingOutput PathFindingOutput ;

enum RoomType{
    // TODO this
    ROOM_GENERIC_COMBAT = 0,
    ROOM_GENERIC_SHOP,
}; typedef enum RoomType RoomType;

struct RoomTypeProperty{
    bool spawnEnemies;
}; typedef struct RoomTypeProperty RoomTypeProperty;


void TerrainGenerateNewRoom(RoomType roomType);
RoomTypeProperty GetRoomTypeProperties(RoomType RoomType);
bool TerrainCheckCollisions(float x, float y, float w, float h);
void TerrainUpdate();
bool TerrainCheckForLineOfSight(float x, float y, float w, float h, float targetX, float targetY);
PathFindingOutput* TerrainPathFindTowards(float x, float y, float targetX, float targetY);
void RegisterExit(WorldObject* exit);
WorldObject* GetExit();

#endif