#include "objectControllerManager.h"
#include "vector.h"
#include <stdlib.h>


Vector* objectControllers;


void ObjectControllerManagerInit(){
    objectControllers = VectorInit();
}


void ObjectControllerManagerDispose(){
    for (int i = 0; i < objectControllers->elementCount; i++){
        free(VectorGet(objectControllers, i));
    }
    VectorFree(objectControllers);
}


int ObjectControllerManageRegisterOrGet(ObjectController* controller){
    VectorAdd(objectControllers, controller); // TODO : rework to use map
    return objectControllers->elementCount;
}
