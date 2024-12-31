#include "projectile.h"
#include "gameLib/gamelibInclude.h"
#include "math.h"
#include "game/systemsInclude.h"

void ProjectileUpdate(WorldObject* this, ProjectileData* data);

void ProjectileInit(float x, float y, float direction, float velocity){
    // init gameobject
    WorldObject* playerWorldObject = InitWorldObject(x, y, 32, 32);
    playerWorldObject->spriteIndex = getSpriteIndex("debug_bullet");

    // controller
    ObjectController* controller = ObjectControllerInit();
    controller->objectUpdate = (void (*)(WorldObject *, void *))&ProjectileUpdate;

    ProjectileData* data = malloc(sizeof(ProjectileData));
    data->direction = direction;
    data->velocity = velocity;


    GameObjectCreate(playerWorldObject, controller, data);
}


void ProjectileUpdate(WorldObject* this, ProjectileData* data){
    // update
    this->x += cos(data->direction) * data->velocity;
    this->y += sin(data->direction) * data->velocity;

    // collisions
    if (collidesWithTerrain(this->x, this->y, this->width, this->height)){
        // TODO : delete
    }
    
}