#include "objectLifecycleOrchestrator.h"
#include "objectController.h"
#include "worldObjectManager.h"
#include "objectDataManager.h"
#include "objectControllerManager.h"
#include "memoryMacros.h"
#include "debug.h"


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


void GameObjectInteractIfPossible(WorldObject* targetObject, int interactionType, void* interactionData){
    if (targetObject->controllerId == UNDEFINED){
        return;
    }
    ObjectController* controller = ObjectControllerManagerGet(targetObject->controllerId);

    if (controller == UNDEFINED || controller->objectInteract == UNDEFINED){
        return;
    }

    ObjectInteraction* intData = ObjectInteractionInit(interactionType, interactionData);

    void* targetData = GameObjectGetData(targetObject);
    controller->objectInteract(targetObject, targetData, intData);

    ObjectInteractionFree(intData);
}


void* GameObjectGetData(WorldObject* object){
    if (object->dataId == UNDEFINED){
        return UNDEFINED;
    }
    debugMessage("got here 3 [%d]", object->dataId);

    return ObjectDataManagerGet(object->dataId);
}


ObjectController* GameObjectGetController(WorldObject* object){
    if (object->controllerId == UNDEFINED){
        return UNDEFINED;
    }
    return ObjectControllerManagerGet(object->controllerId);
}


void GameObjectClean(WorldObject* object){
    ObjectController* controller = GameObjectGetController(object);

    if (controller != UNDEFINED && controller->objectCleanUp != UNDEFINED){
        controller->objectCleanUp(object, object);
    }
}

