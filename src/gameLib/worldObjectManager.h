#ifndef WORLD_OBJECT_MANAGER
#define WORLD_OBJECT_MANAGER

#include "worldObject.h"


void WorldObjectManagerInit();
int WorldObjectManagerAddObject(WorldObject* object);
void WorldObjectManagerUpdate();
void WorldObjectManagerDispose();

#endif