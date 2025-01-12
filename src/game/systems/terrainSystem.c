#include "terrainSystem.h"
#include "gameLib/gamelibInclude.h"
#include "math.h"
#include <stdbool.h>

#define WORLD_SIZE 32
#define TILE_SIZE 32
#define DEBUG_BORDER 3

unsigned char collisionMap[WORLD_SIZE][WORLD_SIZE];


void TerrainGenerateNewRoom(){
    for (int x = 0; x < WORLD_SIZE; x++){
        for (int y = 0; y < WORLD_SIZE; y++){
            collisionMap[x][y] = (x < DEBUG_BORDER || y < DEBUG_BORDER || x >= WORLD_SIZE - DEBUG_BORDER || y >= WORLD_SIZE - DEBUG_BORDER);
        }
    }
    collisionMap[10][8] = 1;
}


bool TerrainCheckCollisions(float x, float y, float w, float h){
    for (int i = floorf(x / TILE_SIZE); i < ceilf((x + w)/ TILE_SIZE); i++){
        for (int j = floorf(y / TILE_SIZE); j < ceilf((y + h)/ TILE_SIZE); j++){
            if (collisionMap[i][j]){
                return true;
            }
        } 
    } 
    return false;
}


void TerrainUpdate(){
    for (int x = 0; x < WORLD_SIZE; x++){
        for (int y = 0; y < WORLD_SIZE; y++){
            char* tile;

            if (collisionMap[x][y] == 1){
                tile = "debug_tiles_0001";
            }else {
                tile = "debug_tiles_0002";
            }



            spriteDrawBasic(tile, x * TILE_SIZE, y * TILE_SIZE, FLIP_NONE, 0);

        }
    }
    
}

#define JANK_LOS_DISTANCE 0.45f
bool TerrainCheckForLineOfSight(float x, float y, float w, float h, float targetX, float targetY){
    float direction = directionTowards(x, y, targetX, targetY);
    float distance = distanceTo(x, y, targetX, targetY);

    float iterator = 0.0f;

    while (iterator < distance - JANK_LOS_DISTANCE){
        iterator += JANK_LOS_DISTANCE;
        float tryX = cos(direction) * iterator + x;
        float tryY = sin(direction) * iterator + y;

        if (TerrainCheckCollisions(tryX, tryY, w, h)){
            return false;
        }
    }
    return true;
}
