#include "player.h"
#include "gameLib/gamelibInclude.h"
#include "stdlib.h"
#include "game/systemsInclude.h"
#include "math.h"
#include "game/entities/projectiles/projectile.h"

void PlayerUpdate(WorldObject* this, PlayerData* data);

void PlayerInit(float x, float y){
    // init gameobject
    WorldObject* playerWorldObject = InitWorldObject(x, y, 32, 32);
    playerWorldObject->spriteIndex = getSpriteIndex("debug_man");

    // controller
    ObjectController* controller = ObjectControllerInit();
    controller->objectUpdate = (void (*)(WorldObject *, void *))&PlayerUpdate;

    PlayerData* data = malloc(sizeof(PlayerData));
    data->xVelocity = 0;
    data->yVelocity = 0;
    data->fireCooldown = 0;
    data->dashCooldown = 0;
    data->ammoCount = 10;
    data->reloadTimer = 0;

    GameObjectCreate(playerWorldObject, controller, data);
}


#define PLAYER_SPEED_MULTIPLIER 3.5f
#define PLAYER_SPEED_BUILDUP 0.07f
#define GUN_OFFSET 23.0f

void PlayerUpdate(WorldObject* this, PlayerData* data){
    
    // dashing
    if (IsKeyPressed(KEY_SPACE) && data->dashCooldown == 0 && (fabs(data->xVelocity) > 0.1f || fabs(data->yVelocity) > 0.1f)){
        data->dashCooldown = 65;
        float dashDirection = directionTowards(0, 0, data->xVelocity, data->yVelocity);
        data->xVelocity = cos(dashDirection) * 2.5f;
        data->yVelocity = sin(dashDirection) * 2.5f;
    }
    data->dashCooldown -= data->dashCooldown > 0;


    // movement input
    if (IsKeyDown(KEY_D) == IsKeyDown(KEY_A)){
        data->xVelocity = limitedIncrement(data->xVelocity, 0.0f, PLAYER_SPEED_BUILDUP);
    }else if (IsKeyDown(KEY_D)){
        data->xVelocity = limitedIncrement(data->xVelocity, 1.0f, PLAYER_SPEED_BUILDUP);
    }else if (IsKeyDown(KEY_A)){
        data->xVelocity = limitedIncrement(data->xVelocity, -1.0f, PLAYER_SPEED_BUILDUP);
    }


    if (IsKeyDown(KEY_W) == IsKeyDown(KEY_S)){
        data->yVelocity = limitedIncrement(data->yVelocity, 0.0f, PLAYER_SPEED_BUILDUP);
    }else if (IsKeyDown(KEY_W)){
        data->yVelocity = limitedIncrement(data->yVelocity, -1.0f, PLAYER_SPEED_BUILDUP);
    }else if (IsKeyDown(KEY_S)) {
        data->yVelocity = limitedIncrement(data->yVelocity, 1.0f, PLAYER_SPEED_BUILDUP);
    }


    // terrain collisions
    float xCollisionCheck = this->x + (data->xVelocity * PLAYER_SPEED_MULTIPLIER);
    if (collidesWithTerrain(xCollisionCheck, this->y, this->width, this->height)){
        data->xVelocity = 0;
    }


    float yCollisionCheck = this->y + (data->yVelocity * PLAYER_SPEED_MULTIPLIER);
    if (collidesWithTerrain(this->x, yCollisionCheck, this->width, this->height)){
        data->yVelocity = 0;
    }



    // update position
    this->x += data->xVelocity * PLAYER_SPEED_MULTIPLIER;
    this->y += data->yVelocity * PLAYER_SPEED_MULTIPLIER;


    // camera follow
    setCameraTarget(this->x, this->y);

    // TODO : tweak dashing
    
    // gun
    bool isReloading = data->reloadTimer > 0;
    float gunDirection = directionTowards(this->x + (this->width / 2), this->y + (this->height / 2), getInWorldMousePositionX(), getInWorldMousePositionY());
    float gunX = this->x + (cos(gunDirection) * GUN_OFFSET * 1.25f);
    float gunY = this->y + (sin(gunDirection) * GUN_OFFSET);
    float bulletOriginX = gunX + (cos(gunDirection) * 24);
    float bulletOriginY = gunY + (sin(gunDirection) * 24);
    
    data->fireCooldown -= data->fireCooldown > 0;
    int flipGun = FLIP_Y;
    if (gunDirection < PI/2 && gunDirection > -PI/2){
        flipGun = FLIP_NONE;
    }    

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && data->fireCooldown == 0 && !isReloading){
        if (data->ammoCount > 0){
            ProjectileInit(bulletOriginX, bulletOriginY, gunDirection, 8);
            data->fireCooldown = 10;
            addScreenshake(5.0f);
            data->ammoCount--;
            // TODO : shoot sound effect
        }else {
            // TODO : click sound effect
        }
    }

    if (IsKeyPressed(KEY_R) && !isReloading && data->ammoCount < 10){
        data->reloadTimer = 30;
        // TODO : reload sound effect
    }

    data->reloadTimer -= data->reloadTimer > 0;
    // gun spin animation
    if (isReloading){
        gunDirection -= (data->reloadTimer / 30.0f) * (PI * 2);
        if (data->reloadTimer == 1){
            // TODO : click sound effect
            data->ammoCount = 10;
        }
    }

    spriteDraw("debug_gun", gunX, gunY, flipGun, gunDirection, 1.0f, 1.0f, WHITE, 1, false);



}