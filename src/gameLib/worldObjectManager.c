#include "worldObjectManager.h"

#include "vector.h"
#include <stdlib.h>
#include "sprites.h"

Vector* worldObjects;


void WorldObjectManagerInit(){
    worldObjects = VectorInit();
}


int WorldObjectManagerAddObject(WorldObject* object){
    VectorAdd(worldObjects, object);
    return worldObjects->elementCount;
}


void WorldObjectManagerUpdate(){
    for (int i = 0; i < worldObjects->elementCount; i++){
        WorldObject* object = VectorGet(worldObjects, i);

        // TODO: rotation
        // TODO: flipping
        // TODO: width
        // TODO: height
        // TODO: color
        // TODO: layers

        if (object->spriteIndex != -1){
            spriteDrawIndexed(object->spriteIndex, object->x, object->y, FLIP_NONE, 0.0f, 1.0f, 1.0f, WHITE, 0, false);
        }

        if (object->controllerId != -1){
            // TODO: controllers
        }
    }
}


void WorldObjectManagerDispose(){
    for (int i = 0; i < worldObjects->elementCount; i++){
        free(VectorGet(worldObjects, i));
    }
    VectorFree(worldObjects);
}
