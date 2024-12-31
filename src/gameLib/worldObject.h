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
    int id;
    float rotation;
    float layer;
}; typedef struct WorldObject WorldObject ;


WorldObject* InitWorldObject(float x, float y, float width, float height);



#endif