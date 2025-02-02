#include "terrainSystem.h"
#include "gameLib/gamelibInclude.h"
#include "math.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gameLib/hashMap.h"

#define WORLD_SIZE 32
#define TILE_SIZE 32
#define DEBUG_BORDER 3

unsigned char collisionMap[WORLD_SIZE][WORLD_SIZE];
HashMap* pathfindingResultCache = UNDEFINED;




struct PathFindingInfo{
    int startX;
    int startY;
    int endX;
    int endY;
}; typedef struct PathFindingInfo PathFindingInfo;


unsigned int hashPathFindingInfo(void* info){
    return universalHash(info, sizeof(PathFindingInfo));
}


void TerrainGenerateNewRoom(){
    for (int x = 0; x < WORLD_SIZE; x++){
        for (int y = 0; y < WORLD_SIZE; y++){
            collisionMap[x][y] = (x < DEBUG_BORDER || y < DEBUG_BORDER || x >= WORLD_SIZE - DEBUG_BORDER || y >= WORLD_SIZE - DEBUG_BORDER);
        }
    }

    for (int i = 10; i < 15; i++){
        collisionMap[i][8] = 1;
        collisionMap[7][i - 2] = 1;
        collisionMap[14][i - 1] = 1;
        collisionMap[i - 3][13] = 1;

    }

    
    if (pathfindingResultCache != UNDEFINED){
        HashMapDisposeFreeValues(pathfindingResultCache);
        HashMapDispose(pathfindingResultCache);
    }

    pathfindingResultCache = HashMapInit(&hashPathFindingInfo);

}


bool TerrainCheckCollisions(float x, float y, float w, float h){
    for (int i = floorf(x / TILE_SIZE); i < ceilf((x + w)/ TILE_SIZE); i++){
        for (int j = floorf(y / TILE_SIZE); j < ceilf((y + h)/ TILE_SIZE); j++){
            if ((i < 0 || i > WORLD_SIZE || j < 0 || j > WORLD_SIZE) || collisionMap[i][j]){
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
                tile = "wall";
            }else {
                tile = "floor_0001";
            }



            spriteDrawBasic(tile, x * TILE_SIZE, y * TILE_SIZE, FLIP_NONE, 0);

        }
    }
    
}

#define JANK_LOS_DISTANCE 0.25f
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


struct PathFindingNode{
    int x;
    int y;
    float pathFindingWeight;
    float g;
    float h;
    struct PathFindingNode* predecesor;
}; typedef struct PathFindingNode PathFindingNode ;


PathFindingNode* PathFindingNodeInit(int x, int y, float f, float g, float h){
    PathFindingNode* this = malloc(sizeof(PathFindingNode));
    this->x = x;
    this->y = y;
    this->g = g;
    this->h = h;
    this->pathFindingWeight = f;
    this->predecesor = UNDEFINED;
    return this;
}


void attemptPathFindingNodeGeneration(int x, int y, int targetX, int targetY, Vector* closedNodes, Vector* openNodes, PathFindingNode* parent, PathFindingNode** goalNode){
    if (collisionMap[x][y]){
        return;
    }

    float g = parent->g + distanceTo(x, y, parent->x, parent->y);
    float h = distanceTo(x, y, targetX, targetY);

    PathFindingNode* successor = PathFindingNodeInit(x, y, h + g, g, h);
    successor->predecesor = parent;
    if (x == targetX && y == targetY){
        *goalNode = successor;
    }
    // skip if a closer path exists
    for (int i = 0; i < openNodes->elementCount; i++){
        PathFindingNode* p = VectorGet(openNodes, i);
        if (p->x == x && p->y == y && p->pathFindingWeight < successor->pathFindingWeight){
            free(successor);
            return;
        }
    }

    // skip if already closed
    for (int i = 0; i < closedNodes->elementCount; i++){
        PathFindingNode* p = VectorGet(closedNodes, i);
        if (p->x == x && p->y == y && p->pathFindingWeight < successor->pathFindingWeight){
            free(successor);
            return;
        }
    }

    VectorAdd(openNodes, successor);
}

// TODO : pathfinding is super slow
PathFindingOutput* TerrainPathFindTowards(float x, float y, float targetX, float targetY){
    // find start location
    int startX = roundf(x / TILE_SIZE);
    int startY = roundf(y / TILE_SIZE);

    int goalX = roundf(targetX / TILE_SIZE);
    int goalY = roundf(targetY / TILE_SIZE);

    PathFindingInfo* info = malloc(sizeof(PathFindingInfo));
    info->startX = startX;
    info->startY = startY;
    info->endX = goalX;
    info->endY = goalY;

    if (HashMapContains(pathfindingResultCache, info)){
        Pair* result = HashMapGet(pathfindingResultCache, info);
        free(info);
        return result->second;
    }

    Vector* openNodes = VectorInit();
    Vector* closedNodes = VectorInit();

    VectorAdd(openNodes, PathFindingNodeInit(startX, startY, 0.0f, 0.0f, 0.0f));
    PathFindingNode* goalNode = UNDEFINED;

    while (openNodes->elementCount != 0){
        // find node with lowest f
        PathFindingNode* q = UNDEFINED;
        int qIndex = UNDEFINED;
        for (int i = 0; i < openNodes->elementCount; i++){
            PathFindingNode* node = VectorGet(openNodes, i);
            if (q == UNDEFINED || node->pathFindingWeight < q->pathFindingWeight){
                q = node;
                qIndex = i;
            }
        }
        VectorRemove(openNodes, qIndex);
        VectorAdd(closedNodes, q);


        attemptPathFindingNodeGeneration(q->x - 1, q->y, goalX, goalY, closedNodes, openNodes, q, &goalNode);
        attemptPathFindingNodeGeneration(q->x + 1, q->y, goalX, goalY, closedNodes, openNodes, q, &goalNode);

        attemptPathFindingNodeGeneration(q->x - 1, q->y + 1, goalX, goalY, closedNodes, openNodes, q, &goalNode);
        attemptPathFindingNodeGeneration(q->x + 1, q->y + 1, goalX, goalY, closedNodes, openNodes, q, &goalNode);

        attemptPathFindingNodeGeneration(q->x - 1, q->y - 1, goalX, goalY, closedNodes, openNodes, q, &goalNode);
        attemptPathFindingNodeGeneration(q->x + 1, q->y - 1, goalX, goalY, closedNodes, openNodes, q, &goalNode);

        attemptPathFindingNodeGeneration(q->x, q->y - 1, goalX, goalY, closedNodes, openNodes, q, &goalNode);
        attemptPathFindingNodeGeneration(q->x, q->y + 1, goalX, goalY, closedNodes, openNodes, q, &goalNode);

        if (goalNode != UNDEFINED){
            break;
        }
    }

    // find first
    PathFindingNode* first = goalNode;
    while (first->predecesor != UNDEFINED && !(first->predecesor->x == startX && first->predecesor->y == startY) ){
        first = first->predecesor;

        if (isDebugModeOn()){
            spriteDrawBasic("debug_man", first->x * TILE_SIZE, first->y * TILE_SIZE, FLIP_NONE, 2);
        }
    }

    PathFindingOutput* output = malloc(sizeof(PathFindingOutput));
    if (first == UNDEFINED){
        output->canReach = false;
    }else {
        output->canReach = true;
        output->nextX = first->x * TILE_SIZE;
        output->nextY = first->y * TILE_SIZE;
    }

    HashMapPut(pathfindingResultCache, (Pair){info, output});

    VectorFreeValues(openNodes);
    VectorFreeValues(closedNodes);

    return output;
}

