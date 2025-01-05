#include "worldObject.h"
#include <stdlib.h>
#include "memoryMacros.h"

WorldObject* InitWorldObject(float x, float y, float width, float height){
    return InitWorldObjectT(x, y, width, height, UNDEFINED);
}


WorldObject* InitWorldObjectT(float x, float y, float width, float height, int objectTag){
    WorldObject* this = malloc(sizeof(WorldObject));

    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->controllerId = UNDEFINED;
    this->spriteIndex = UNDEFINED;
    this->dataId = UNDEFINED;
    this->rotation = 0;
    this->layer = 0;
    this->state = OBJECT_STATE_NORMAL;
    this->objectTag = objectTag;

    return this;
}
