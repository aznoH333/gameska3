#include "player.h"
#include "gameLib/gamelibInclude.h"
#include "gun.h"
#include "stdlib.h"
#include "game/systemsInclude.h"
#include "math.h"
#include "game/entities/projectiles/projectile.h"
#include "game/gameEnums/enumsInclude.h"
#include "gameLib/sounds.h"

void PlayerUpdate(WorldObject* this, PlayerData* data);
void PlayerInteract(WorldObject* this, PlayerData* data, ObjectInteraction* interaction);
void PlayerSwapGun(WorldObject* this, PlayerData* data, Gun newGun);

void PlayerInit(float x, float y){
    // init gameobject
    WorldObject* playerWorldObject = InitWorldObjectT(x, y, 32, 32, OBJECT_TAG_PLAYER);
    playerWorldObject->spriteIndex = getSpriteIndex("player_0001");
    playerWorldObject->layer = LAYER_PLAYER;

    // controller
    ObjectController* controller = ObjectControllerInit();
    controller->objectUpdate = (void (*)(WorldObject *, void *))&PlayerUpdate;
    controller->objectInteract = (ControllerInteractFunction) &PlayerInteract;

    PlayerData* data = malloc(sizeof(PlayerData));
    data->xVelocity = 0;
    data->yVelocity = 0;
    data->dashCooldown = 0;
    data->stunTimer = 0;
    data->invincibilityTimer = 0;
    PlayerSwapGun(playerWorldObject, data, 
        GunInit(
            "guns_0002", 
            20, 
            7, 
            10.0f, 
            0.1f, 
            1, 
            30
        )
    );

    GameObjectCreate(playerWorldObject, controller, data);

    PlayerManagerSetPlayer(playerWorldObject);
}


const char* animationLookup[] = {
    "player_0001",
    "player_0002",
    "player_0003",
    "player_0004",
    "player_0005",
    "player_0006",
    "player_0007",
};

#define PLAYER_SPEED_MULTIPLIER 3.5f
#define PLAYER_SPEED_BUILDUP 0.07f
#define GUN_OFFSET 23.0f

void PlayerUpdate(WorldObject* this, PlayerData* data){
    // dashing
    float dashXVel = (IsKeyDown(KEY_A) * -1) + (IsKeyDown(KEY_D));
    float dashYVel = (IsKeyDown(KEY_W) * -1) + (IsKeyDown(KEY_S));

    if (dashXVel == 0){
        dashXVel = data->xVelocity;
    }

    if (dashYVel == 0){
        dashYVel = data->yVelocity;
    }

    if (IsKeyPressed(KEY_SPACE) && data->dashCooldown == 0 && (fabs(dashXVel) > 0.1f || fabs(dashYVel) > 0.1f)){
        data->dashCooldown = 65;
        float dashDirection = directionTowards(0, 0, dashXVel, dashYVel);
        data->xVelocity = cos(dashDirection) * 2.5f;
        data->yVelocity = sin(dashDirection) * 2.5f;
    }
    data->dashCooldown -= data->dashCooldown > 0;

    
    // movement input
    if (IsKeyDown(KEY_D) == IsKeyDown(KEY_A)){
        data->xVelocity = limitedIncrement(data->xVelocity, 0.0f, PLAYER_SPEED_BUILDUP);
    }else if (IsKeyDown(KEY_D)){
        data->xVelocity = limitedIncrement(data->xVelocity, 1.0f, PLAYER_SPEED_BUILDUP);
        this->flip = FLIP_NONE;
    }else if (IsKeyDown(KEY_A)){
        data->xVelocity = limitedIncrement(data->xVelocity, -1.0f, PLAYER_SPEED_BUILDUP);
        this->flip = FLIP_X;
    }


    if (IsKeyDown(KEY_W) == IsKeyDown(KEY_S)){
        data->yVelocity = limitedIncrement(data->yVelocity, 0.0f, PLAYER_SPEED_BUILDUP);
    }else if (IsKeyDown(KEY_W)){
        data->yVelocity = limitedIncrement(data->yVelocity, -1.0f, PLAYER_SPEED_BUILDUP);
    }else if (IsKeyDown(KEY_S)) {
        data->yVelocity = limitedIncrement(data->yVelocity, 1.0f, PLAYER_SPEED_BUILDUP);
    }

    // update position
    // terrain collisions
    float xCollisionCheck = this->x + (data->xVelocity * PLAYER_SPEED_MULTIPLIER);
    if (TerrainCheckCollisions(xCollisionCheck, this->y, this->width, this->height)){
        data->xVelocity = 0;
    }
    this->x += data->xVelocity * PLAYER_SPEED_MULTIPLIER;


    float yCollisionCheck = this->y + (data->yVelocity * PLAYER_SPEED_MULTIPLIER);
    if (TerrainCheckCollisions(this->x, yCollisionCheck, this->width, this->height)){
        data->yVelocity = 0;
    }
    this->y += data->yVelocity * PLAYER_SPEED_MULTIPLIER;


    // invincibility flicker
    if (data->invincibilityTimer > 0){
        data->invincibilityTimer--;
        this->color.a = 255 * (data->invincibilityTimer % 4 < 2);
    }

    // update animation
    if (data->stunTimer != 0){
        this->spriteIndex = getSpriteIndex("player_0008");
        data->stunTimer--;
    }
    else if (data->yVelocity == 0 && data->xVelocity == 0){
        this->spriteIndex = getSpriteIndex(animationLookup[0]);
    }else {
        this->spriteIndex = getSpriteIndex(animationLookup[(getGlobalTimer() / 2) % 7]);
    }


    // camera follow
    setCameraTarget(this->x, this->y);

    // gun
    bool isReloading = data->gun.reloadTimer > 0;
    float gunDirection = directionTowards(this->x + (this->width / 2), this->y + (this->height / 2), getInWorldMousePositionX(), getInWorldMousePositionY());
    float gunX = this->x + (cos(gunDirection) * GUN_OFFSET * 1.25f);
    float gunY = this->y + (sin(gunDirection) * GUN_OFFSET);
    float bulletOriginX = gunX + (cos(gunDirection) * 24);
    float bulletOriginY = gunY + (sin(gunDirection) * 24);
    
    data->gun.fireCooldown -= data->gun.fireCooldown > 0;
    int flipGun = FLIP_Y;
    if (gunDirection < PI/2 && gunDirection > -PI/2){
        flipGun = FLIP_NONE;
    }    

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && data->gun.fireCooldown == 0 && !isReloading){
        if (data->gun.ammoCount > 0){ // TODO : bullet speed
            for (int i = 0; i < data->gun.bulletsPerShot; i++){
                float bulletDirection = gunDirection + randomFloatRange(-data->gun.accuracy, data->gun.accuracy);
                ProjectileInit(bulletOriginX, bulletOriginY, bulletDirection, 8, data->gun.damage, OBJECT_TAG_PLAYER_PROJECTILE);
            }
            
            addScreenshake(5.0f); // TODO : screen shake ammount
            data->gun.ammoCount--;
            soundPlay("gun"); // TODO : gun sounds
        }else {
            soundPlay("click"); // TODO : click sounds
        }
        data->gun.fireCooldown = data->gun.fireRate;

    }

    if (IsKeyPressed(KEY_R) && !isReloading && data->gun.ammoCount < data->gun.maxAmmo){
        data->gun.reloadTimer = data->gun.reloadSpeed;
        soundPlay("pickup"); // TODO : reload sounds
    }

    data->gun.reloadTimer -= data->gun.reloadTimer > 0;
    // gun spin animation
    if (isReloading){
        gunDirection -= (data->gun.reloadTimer / (float)data->gun.reloadSpeed) * (PI * 2);
        if (data->gun.reloadTimer == 1){
            soundPlay("click");
            data->gun.ammoCount = data->gun.maxAmmo;
        }
    }

    spriteDraw(data->gun.sprite, gunX, gunY, flipGun, gunDirection, 1.0f, 1.0f, WHITE, LAYER_PLAYER, false);
}


void playerDamage(WorldObject* this, PlayerData* data, int damage){
    if (data->invincibilityTimer == 0){
        PlayerManagerHurtPlayer(damage);
        data->invincibilityTimer = 120;
    }
}

void playerPush(WorldObject* this, PlayerData* data, ObjectInteractionPushData* pushData){
    if (data->stunTimer == 0 && data->invincibilityTimer == 0){
        data->xVelocity = pushData->pushX * 1.25f;
        data->yVelocity = pushData->pushY * 1.25f;
        data->stunTimer = (int)pushData->pushValue;
    }
}

void pickupMoney(WorldObject* this, PlayerData* data, int money){
    PlayerManagerAddMoney(money);
}


void PlayerInteract(WorldObject* this, PlayerData* data, ObjectInteraction* interaction){
    switch (interaction->interactionType) {
        case INTERACTION_DEAL_DAMAGE:
            playerDamage(this, data, *(int*)interaction->interactionValue);
            break;
        case INTERACTION_PUSH:
            playerPush(this, data, interaction->interactionValue);
            break;
        case INTERACTION_GIVE_MONEY:
            pickupMoney(this, data, *(int*)interaction->interactionValue);
            break;
    }
}


void PlayerSwapGun(WorldObject* this, PlayerData* data, Gun newGun){
    data->gun = newGun;
}

Gun* PlayerGetGun(WorldObject* player){
    PlayerData* p = GameObjectGetData(player);
    return &p->gun;
}
