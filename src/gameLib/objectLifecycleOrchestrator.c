#include "objectLifecycleOrchestrator.h"
#include "worldObjectManager.h"


void GameObjectCreate(WorldObject* body, ObjectController* mind, void* soul){
    
    if (mind != 0){
        
    }
    
    WorldObjectManagerAddObject(body);
}


void GameObjectRemove(int objectIndex);