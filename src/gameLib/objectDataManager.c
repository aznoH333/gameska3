#include "objectDataManager.h"
#include <stdlib.h>
#include "genericComparisons.h"
#include "map.h"

Map* objectDataStorage;
int elementIdCounter;

void ObjectDataManagerInit(){
    elementIdCounter = 0;
    objectDataStorage = MapInit(&intEquals);
}


int ObjectDataManagerAdd(void* data){
    MapPut(objectDataStorage, Pair{elementIdCounter, data});
    return objectDataStorage->elementCount;
}


void ObjectDataManagerRemove(int index){
    VectorGet(objectDataStorage, index);
}



void* ObjectDataManagerGet(int index){
    return VectorGet(objectDataStorage, index);
}


void ObjectDataManagerDispose(){
    for (int i = 0; i < objectDataStorage->elementCount;i++){
        free(VectorGet(objectDataStorage, i));
    }
    VectorFree(objectDataStorage);
}