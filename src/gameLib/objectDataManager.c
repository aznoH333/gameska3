#include "objectDataManager.h"
#include <stdlib.h>
#include "genericComparisons.h"
#include "map.h"
#include "debug.h"
#include "memoryMacros.h"

Map* objectDataStorage;
int elementIdCounter;

void ObjectDataManagerInit(){
    elementIdCounter = 1;
    objectDataStorage = MapInit(&intEquals);
}


int ObjectDataManagerAdd(void* data){
    int* key = malloc(sizeof(int));
    *key = elementIdCounter;

    MapPut(objectDataStorage, (Pair){key, data});
    return elementIdCounter++;
}


void ObjectDataManagerRemove(int index){
    int* key = malloc(sizeof(int));
    *key = elementIdCounter;
    Pair* value = MapGet(objectDataStorage, key);
    MapRemove(objectDataStorage, key);
    free(value->first);
    free(value);
    free(key);
}



void* ObjectDataManagerGet(int index){
    initHeapVariable(int, key, index);
    debugMessage("val %d", key);
    Pair* value = MapGet(objectDataStorage, key);

    free(key);
    return value->second;
}


void ObjectDataManagerDispose(){
    Vector* values = MapGetAsVector(objectDataStorage);

    for (int i = 0; i < values->elementCount;i++){
        Pair* p = VectorGet(values, i);

        free(p->first);
        free(p->second);
    }

    MapFree(objectDataStorage);
}