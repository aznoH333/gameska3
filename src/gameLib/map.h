#ifndef MAP 
#define MAP 

#include "vector.h"
#include "pair.h"
#include <stdbool.h>

struct Map{
    Vector* values;
    bool (*comparisonFunction)(void*, void*);
}; typedef struct Map Map;

Map* MapInit(bool (*comparisonFunction)(void*, void*));
void MapPut(Map* this, Pair pair);
Pair* MapGet(Map* this, void* key);
Vector* MapGetAsVector(Map* this);
void MapRemove(Map* this, void* key);
void MapFree(Map* this);


#endif