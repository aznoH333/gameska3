#ifndef WORLD_OBJECT
#define WORLD_OBJECT

struct WorldObject{
    int spriteIndex;
    int controllerId;
    int dataId;
    float x;
    float y;
    float width;
    float height;
}; typedef struct WorldObject WorldObject ;


WorldObject* InitWorldObject(float x, float y, float width, float height);



#endif