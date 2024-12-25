#ifndef WORLD_OBJECT_MANAGER
#define WORLD_OBJECT_MANAGER

#include "worldObject.h"


void WorldObjectManagerInit();
int WorldObjectManagerAddObject(WorldObject* object);
void WorldObjectManagerRemove(int id);
void WorldObjectManagerUpdate();
void WorldObjectManagerDispose();
WorldObject* WorldObjectManagerGet(int id);

#endif