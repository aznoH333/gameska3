#include "worldObjectManager.h"

#include <stdlib.h>
#include "numberUtils.h"
#include "objectController.h"
#include "sprites.h"
#include "map.h"
#include "memoryMacros.h"
#include "objectControllerManager.h"
#include "objectDataManager.h"
#include "genericComparisons.h"
#include "debug.h"
#include "objectLifecycleOrchestrator.h"
#include "vector.h"
#include "worldObject.h"
#include "worldSpaceUtils.h"

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

        spriteDrawIndexed(object->spriteIndex, object->x, object->y, FLIP_NONE, object->rotation, 1.0f, 1.0f, WHITE, object->layer, false);

        void* body = UNDEFINED;


        if (object->dataId != UNDEFINED){
            body = ObjectDataManagerGet(object->dataId);
        }



        ObjectController* controller = UNDEFINED;
        if (object->controllerId != UNDEFINED){
            // update
            controller = ObjectControllerManagerGet(object->controllerId);

            controller->objectUpdate(object, body);
        }


        if (object->state != OBJECT_STATE_NORMAL){
            
            if (object->controllerId != UNDEFINED){
                controller = ObjectControllerManagerGet(object->controllerId);
            }

            if (object->state != OBJECT_STATE_HIDDEN_DESTROY && object->controllerId != UNDEFINED && controller->objectDestroy != UNDEFINED){
                controller->objectDestroy(object, body);
            }

            debugMessage("%p %p", controller, controller->objectCleanUp);
            if (controller != UNDEFINED && controller->objectCleanUp != UNDEFINED){
                controller->objectCleanUp(object, body);
            }
            

            GameObjectRemove(object->id);
            i--;
            continue;
        }



        // collisions
        for (int j = 0; j < worldObjects->values->elementCount; j++){
            if (i == j){
                continue;
            }

            WorldObject* other = ((Pair*)VectorGet(worldObjects->values, j))->second;

            if (controller != UNDEFINED && controller->objectCollide != UNDEFINED &&
                squaresCollide(object->x, object->y, object->width, object->height, other->x, other->y, other->width, other->height)){
                controller->objectCollide(object, body, other);
            }
        }
    }
}


WorldObject* WorldObjectManagerGetClosestObjectInRange(WorldObject* searchingObject, int targetTag, float maxTargetDistance){
    WorldObject* closest = UNDEFINED;
    float closestDistance = UNDEFINED;
    
    for (int i = 0; i < worldObjects->values->elementCount; i++){
        WorldObject* obj = ((Pair*)VectorGet(worldObjects->values, i))->second;

        float distance = distanceTo(searchingObject->x, searchingObject->y, obj->x, obj->y);

        if (obj->objectTag == targetTag && (distance < maxTargetDistance || maxTargetDistance == UNDEFINED)){

            if (closest == UNDEFINED || distance < closestDistance){
                closest = obj;
                closestDistance = distance;
            }
        }
    }

    return closest;
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
    for (int i = 0; i < worldObjects->values->elementCount; i++){
        WorldObject* obj = VectorGet(worldObjects->values, i);

        GameObjectClean(obj);        
    }
    
    MapFreeKeys(worldObjects);
    MapFreeValues(worldObjects);
    MapFree(worldObjects);
}
