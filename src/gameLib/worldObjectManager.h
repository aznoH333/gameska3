#ifndef WORLD_OBJECT_MANAGER
#define WORLD_OBJECT_MANAGER

#include "worldObject.h"
#include <stdbool.h>

void WorldObjectManagerInit();
int WorldObjectManagerAddObject(WorldObject* object);
void WorldObjectManagerRemove(int id);
void WorldObjectManagerUpdate();
void WorldObjectManagerDispose();
void WorldObjectManagerClear();
WorldObject* WorldObjectManagerGet(int id);
WorldObject* WorldObjectManagerGetClosestObjectInRange(WorldObject* searchingObject, int targetTag, float maxTargetDistance);

#endif