#ifndef OBJECT_CONTROLLER
#define OBJECT_CONTROLLER


#include "worldObject.h"

struct ObjectController{
    void (*objectUpdate) (WorldObject* this);
    void (*objectCollide) (WorldObject* this, WorldObject* other);
    void (*objectDestroy) (WorldObject* this);
};
typedef struct ObjectController ObjectController ;

ObjectController* ObjectControllerInit(); //TODO : implementation

#endif