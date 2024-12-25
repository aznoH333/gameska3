#include "objectLifecycleOrchestrator.h"
#include "worldObjectManager.h"
#include "objectDataManager.h"
#include "objectControllerManager.h"
#include "memoryMacros.h"


void GameObjectCreate(WorldObject* body, ObjectController* mind, void* soul){
    if (mind != UNDEFINED){
        body->controllerId = ObjectControllerManageRegisterOrGet(mind);
    }
    
    if (soul != UNDEFINED){
        body->dataId = ObjectDataManagerAdd(soul);
    }

    body->id = WorldObjectManagerAddObject(body);
}


void GameObjectRemove(int objectId){
    WorldObject* object = WorldObjectManagerGet(objectId);
    if (object->dataId != UNDEFINED){
        ObjectDataManagerRemove(object->dataId);
    }
    WorldObjectManagerRemove(objectId);

}