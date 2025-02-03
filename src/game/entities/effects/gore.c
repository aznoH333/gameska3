#include "gore.h"
#include "gameLib/gamelibInclude.h"
#include "game/gameEnums/objectTags.h"
#include "gameLib/numberUtils.h"
#include "math.h"
#include "game/gameEnums/objectLayers.h"
#include "gameLib/sounds.h"


void pickRandomSprite(WorldObject* this){
    int number = GetRandomValue(0, 2);
    switch (number) {
        case 0:
            this->spriteIndex = getSpriteIndex("gore_0001");
            break;
        case 1:
            this->spriteIndex = getSpriteIndex("gore_0002");
            break;
        case 2:
            this->spriteIndex = getSpriteIndex("gore_0003");
            break;
    }
}


#define MAX_LIFETIME 140;

void GoreUpdate(WorldObject* this, GoreData* data);

void InitGore(float x, float y, int bounceCount){
    WorldObject* this = InitWorldObjectT(x, y, 5, 5, OBJECT_TAG_NEUTRAL);
    pickRandomSprite(this);
    this->layer = LAYER_FLOOR;
    this->checkCollisions = false;


    ObjectController* controller = ObjectControllerInit();
    controller->objectUpdate = (ControllerUpdateFunction) &GoreUpdate;

    GoreData* data = malloc(sizeof(GoreData));
    float direction = randomFloatRange(0, PI*2);
    float speed = randomFloatRange(2.25f, 3.75f);
    data->xVelocity = cos(direction) * speed;
    data->yVelocity = sin(direction) * speed;
    data->bounceCount = bounceCount;
    data->zVelocity = 2.25f;
    data->z = 0;
    data->isAirborne = true;
    data->realY = y;
    data->lifeTime = MAX_LIFETIME;

    GameObjectCreate(this, controller, data);
}


void GoreUpdate(WorldObject* this, GoreData* data){
    if (!data->isAirborne){
        data->lifeTime--;
        
        float transparency = (float)data->lifeTime / MAX_LIFETIME;

        this->color.a = (unsigned char)(255.0f * transparency);

        if (data->lifeTime <= 0){
            this->state = OBJECT_STATE_DESTROY;
        }

        return;
    }

    this->x += data->xVelocity;
    data->realY += data->yVelocity;
    this->y = data->realY - data->z;
    data->z += data->zVelocity;


    data->zVelocity -= 0.5f;

    if (data->z < 0){
        soundPlay("blood_splat");
        pickRandomSprite(this);
        data->isAirborne = false;
        if (data->bounceCount > 0){
            int rng = GetRandomValue(0, 2);

            for (int i = 0; i < rng; i++){
                InitGore(this->x, this->y, data->bounceCount - 1);
            }
        }
    }

}

#undef MAX_LIFETIME