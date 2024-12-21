#ifndef OBJECT_LIFECYCLE_ORCHESTRATOR
#define OBJECT_LIFECYCLE_ORCHESTRATOR

#include "worldObject.h"
#include "objectController.h"

void GameObjectCreate(WorldObject* body, ObjectController* mind, void* soul);
void GameObjectRemove(int objectIndex);


#endif