#ifndef WORLD_OBJECT
#define WORLD_OBJECT

#include <stdbool.h>
#include "raylib.h"

enum ObjectState {
    OBJECT_STATE_NORMAL,
    OBJECT_STATE_DESTROY,
    OBJECT_STATE_HIDDEN_DESTROY,
}; typedef enum ObjectState ObjectState ;


struct WorldObject{
    int spriteIndex;
    int controllerId;
    int dataId;
    int objectTag;
    float x;
    float y;
    float width;
    float height;
    int id;
    float rotation;
    int layer;
    ObjectState state;
    int flip;
    bool checkCollisions;
    Color color;
}; typedef struct WorldObject WorldObject ;


WorldObject* InitWorldObject(float x, float y, float width, float height);
WorldObject* InitWorldObjectT(float x, float y, float width, float height, int objectTag);




#endif