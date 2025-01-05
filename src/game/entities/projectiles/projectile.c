#include "projectile.h"
#include "gameLib/gamelibInclude.h"
#include "math.h"
#include "game/systemsInclude.h"

void ProjectileUpdate(WorldObject* this, ProjectileData* data);

void ProjectileInit(float x, float y, float direction, float velocity, int objectTag){
    // init gameobject
    WorldObject* worldObject = InitWorldObjectT(x, y, 32, 32, objectTag);
    worldObject->spriteIndex = getSpriteIndex("debug_bullet");
    worldObject->layer = 0;
    worldObject->rotation = direction;
    

    // controller
    ObjectController* controller = ObjectControllerInit();
    controller->objectUpdate = (void (*)(WorldObject *, void *))&ProjectileUpdate;

    ProjectileData* data = malloc(sizeof(ProjectileData));
    data->direction = direction;
    data->velocity = velocity;


    GameObjectCreate(worldObject, controller, data);
}


void ProjectileUpdate(WorldObject* this, ProjectileData* data){
    // update
    this->x += cos(data->direction) * data->velocity;
    this->y += sin(data->direction) * data->velocity;
    this->rotation = data->direction;

    // collisions
    if (collidesWithTerrain(this->x, this->y, this->width, this->height)){
        this->state = OBJECT_STATE_DESTROY;
    }
    
}