#ifndef OBJECT_LIFECYCLE_ORCHESTRATOR
#define OBJECT_LIFECYCLE_ORCHESTRATOR

#include "worldObject.h"
#include "objectController.h"

void GameObjectCreate(WorldObject* body, ObjectController* mind, void* soul);
void GameObjectRemove(int objectId);
void GameObjectInteractIfPossible(WorldObject* targetObject, int interactionType, void* interactionData);
void* GameObjectGetData(WorldObject* object);
void GameObjectClean(WorldObject* object);
ObjectController* GameObjectGetController(WorldObject* object);

#define ControllerUpdateFunction void (*)(WorldObject*, void*)
#define ControllerCollideFunction void (*)(WorldObject*, void*, WorldObject*) 
#define ControllerInteractFunction void (*)(WorldObject*, void*, ObjectInteraction*)

#endif