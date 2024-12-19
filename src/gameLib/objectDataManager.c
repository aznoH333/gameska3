#include "objectDataManager.h"
#include "vector.h"
#include <stdlib.h>

Vector* objectDataStorage;

void ObjectDataManagerInit(){
    objectDataStorage = VectorInit();
}


int ObjectDataManagerAdd(void* data){
    VectorAdd(objectDataStorage, data);
    return objectDataStorage->elementCount;
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