#ifndef OBJECT_CONTROLLER
#define OBJECT_CONTROLLER


#include "worldObject.h"

struct ObjectController{
    void (*objectUpdate) (WorldObject* this, void* data);
    void (*objectCollide) (WorldObject* this, void* data, WorldObject* other);
    void (*objectDestroy) (WorldObject* this, void* data);
    void (*objectCleanUp) (WorldObject* this, void* data);
    void (*objectInteract) (WorldObject* this, void* data, int interactionType, void* interactionValue);
};
typedef struct ObjectController ObjectController ;

ObjectController* ObjectControllerInit();
unsigned int ObjectControllerGetHash(ObjectController* this);

#endif