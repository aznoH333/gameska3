#include "objectControllerManager.h"
#include <stdlib.h>
#include "map.h"
#include "genericComparisons.h"
#include "memoryMacros.h"

Map* objectControllers;

void ObjectControllerManagerInit(){
    objectControllers = MapInit(&intEquals);
}


void ObjectControllerManagerDispose(){
    MapFreeKeys(objectControllers);
    MapFreeValues(objectControllers);
    MapFree(objectControllers);
}


int ObjectControllerManageRegisterOrGet(ObjectController* controller){
    initHeapVariable(int, hashedController, ObjectControllerGetHash(controller));
    
    if (MapContains(objectControllers, hashedController)){
        int output = *hashedController;
        free(hashedController);
        free(controller);
        return output;
    }
    MapPut(objectControllers, (Pair){hashedController, controller});
    return *hashedController;
}


ObjectController* ObjectControllerManagerGet(int id){
    initHeapVariable(int, key, id);

    ObjectController* output = MapGet(objectControllers, key)->second;
    free(key);
    return output;
}

