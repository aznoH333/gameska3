#include "worldObject.h"
#include <stdlib.h>

WorldObject* InitWorldObject(float x, float y, float width, float height){
    WorldObject* this = malloc(sizeof(WorldObject));

    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->controllerId = -1;
    this->spriteIndex = -1;

    return this;
}