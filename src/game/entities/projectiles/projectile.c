#include "projectile.h"
#include "game/gameEnums/interactionTypes.h"
#include "gameLib/gamelibInclude.h"
#include "math.h"
#include "game/systemsInclude.h"
#include "game/gameEnums/enumsInclude.h"

void ProjectileUpdate(WorldObject* this, ProjectileData* data);
void ProjectileCollide(WorldObject* this, ProjectileData* data, WorldObject* other);


void ProjectileInit(float x, float y, float direction, float velocity, float damage, int objectTag){
    // init gameobject
    WorldObject* worldObject = InitWorldObjectT(x, y, 32, 32, objectTag);
    worldObject->spriteIndex = getSpriteIndex("bullet");
    worldObject->layer = 0;
    worldObject->rotation = direction;
    

    // controller
    ObjectController* controller = ObjectControllerInit();
    controller->objectUpdate = (void (*)(WorldObject *, void *))&ProjectileUpdate;
    controller->objectCollide = (ControllerCollideFunction)&ProjectileCollide;

    ProjectileData* data = malloc(sizeof(ProjectileData));
    data->direction = direction;
    data->velocity = velocity;
    data->damage = damage;


    GameObjectCreate(worldObject, controller, data);
}


void ProjectileUpdate(WorldObject* this, ProjectileData* data){
    // update
    this->x += cos(data->direction) * data->velocity;
    this->y += sin(data->direction) * data->velocity;
    this->rotation = data->direction;

    // collisions
    if (TerrainCheckCollisions(this->x, this->y, this->width, this->height)){
        this->state = OBJECT_STATE_DESTROY;
    }
    
}


void ProjectileCollide(WorldObject* this, ProjectileData* data, WorldObject* other){
    if (other->objectTag == OBJECT_TAG_ENEMY){
        this->state = OBJECT_STATE_DESTROY;
        
        // deal damage
        initHeapVariable(float, damage, data->damage);
        GameObjectInteractIfPossible(other, INTERACTION_DEAL_DAMAGE, damage);

        // push
        ObjectInteractionPushData* pushData = malloc(sizeof(ObjectInteractionPushData));
        pushData->pushX = cos(data->direction) * data->velocity;
        pushData->pushY = sin(data->direction) * data->velocity;
        pushData->pushValue = 10;
        GameObjectInteractIfPossible(other, INTERACTION_PUSH, pushData);
    }
}
