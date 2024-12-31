#include "worldObjectManager.h"

#include <stdlib.h>
#include "sprites.h"
#include "map.h"
#include "memoryMacros.h"
#include "objectControllerManager.h"
#include "objectDataManager.h"
#include "genericComparisons.h"
#include "debug.h"

Map* worldObjects;
int keyIterator;

void WorldObjectManagerInit(){
    keyIterator = 0;
    worldObjects = MapInit(&intEquals);
}


int WorldObjectManagerAddObject(WorldObject* object){
    initHeapVariable(int, id, keyIterator++);
    MapPut(worldObjects, (Pair){id, object});
    return *id;
}


void WorldObjectManagerUpdate(){
    for (int i = 0; i < worldObjects->values->elementCount; i++){
        WorldObject* object = ((Pair*)VectorGet(worldObjects->values, i))->second;

        // TODO: flipping
        // TODO: width
        // TODO: height
        // TODO: color

        if (object->spriteIndex != UNDEFINED){
            spriteDrawIndexed(object->spriteIndex, object->x, object->y, FLIP_NONE, object->rotation, 1.0f, 1.0f, WHITE, object->layer, false);
        }

        void* body = UNDEFINED;


        if (object->dataId != UNDEFINED){
            body = ObjectDataManagerGet(object->dataId);
        }

        debugMessage("body id [%d] body prt [%p]", object->dataId, body);



        if (object->controllerId != UNDEFINED){
            // update
            ObjectController* controller = ObjectControllerManagerGet(object->controllerId);

            controller->objectUpdate(object, body);
        }
    }
}


void WorldObjectManagerRemove(int id){
    initHeapVariable(int, key, id);
    MapRemove(worldObjects, key);
    free(key);
}


WorldObject* WorldObjectManagerGet(int id){
    initHeapVariable(int, key, id);
    WorldObject* output = MapGet(worldObjects, key)->second;
    free(key);
    return output;
}




void WorldObjectManagerDispose(){
    MapFreeKeys(worldObjects);
    MapFreeValues(worldObjects);
    MapFree(worldObjects);
}
