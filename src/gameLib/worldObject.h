#ifndef WORLD_OBJECT
#define WORLD_OBJECT

enum ObjectState {
    OBJECT_STATE_NORMAL,
    OBJECT_STATE_DESTROY,
    OBJECT_STATE_HIDDEN_DESTROY,
}; typedef enum ObjectState ObjectState ;


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
    ObjectState state;
}; typedef struct WorldObject WorldObject ;


WorldObject* InitWorldObject(float x, float y, float width, float height);



#endif