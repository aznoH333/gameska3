#include "playerManager.h"
#include "game/gameEnums/enumsInclude.h"
#include "gameLib/font.h"
#include "game/entities/player/player.h"
#include <raylib.h>
#include <stdbool.h>


WorldObject* playerReference = UNDEFINED;
int playerHealth = 5;
int playerMaxHealth = 5;

int playerMoney = 0;
int playerPickupTimer = 0;
int playerPickupAmmount = 0;



#define HEALTH_BAR_X 20.0f
#define HEALTH_BAR_Y 20.0f
#define UI_SCALE 3.0f
#define HEALTH_BAR_SEGMENT_WIDTH UI_SCALE * 8.0f
#define HEALTH_BAR_LAST_SEGMENT_OFFSET UI_SCALE * 6.0f
#define HEALTH_BAR_START_OFFSET UI_SCALE * 4.0f



#define AMMO_BAR_X HEALTH_BAR_X
#define AMMO_BAR_Y HEALTH_BAR_Y + 52.0f
#define AMMO_BAR_SEGMENT_WIDTH HEALTH_BAR_SEGMENT_WIDTH


#define MONEY_DISPLAY_X 20.0f
#define MONEY_DISPLAY_Y 996.0f
#define MONEY_DISPLAY_WIDTH 10
#define MONEY_DISPLAY_ICON_OFFSET 12.0f
#define MONEY_DISPLAY_TEXT_OFFSET 64.0f
#define MONEY_FADING_TIMER 45
#define MONEY_FADING_OFFSET 60
const Color MONEY_COLOR = (Color){255, 255, 0, 255};

void PlayerManagerSetPlayer(WorldObject* player){
    playerReference = player;
}

WorldObject* PlayerManagerGetPlayer(){
    return playerReference;
}


void PlayerManagerUpdate(){
    // draw ui
    // health bar frame
    spriteDraw("healthbar_0001", HEALTH_BAR_X, HEALTH_BAR_Y, FLIP_NONE, 0.0f, UI_SCALE, UI_SCALE, WHITE, LAYER_UI, true);
    for (int i = 1; i < playerMaxHealth; i++){
        spriteDraw("healthbar_0002", HEALTH_BAR_X + (i*HEALTH_BAR_SEGMENT_WIDTH), HEALTH_BAR_Y, FLIP_NONE, 0.0f, UI_SCALE, UI_SCALE, WHITE, LAYER_UI, true);
    }
    spriteDraw("healthbar_0003", HEALTH_BAR_X + ((playerMaxHealth - 1) * HEALTH_BAR_SEGMENT_WIDTH) + HEALTH_BAR_LAST_SEGMENT_OFFSET, HEALTH_BAR_Y, FLIP_NONE, 0.0f, UI_SCALE, UI_SCALE, WHITE, LAYER_UI, true);

    // health bar
    for (int i = 0; i < playerHealth; i++){
        spriteDraw("healthbar_0004", HEALTH_BAR_X + (i * HEALTH_BAR_SEGMENT_WIDTH) + HEALTH_BAR_START_OFFSET, HEALTH_BAR_Y, FLIP_NONE, 0.0f, UI_SCALE, UI_SCALE, WHITE, LAYER_UI, true);
    }

    // health text
    FontDraw("%d/%d", HEALTH_BAR_X + (playerMaxHealth * HEALTH_BAR_SEGMENT_WIDTH) + HEALTH_BAR_START_OFFSET + 10, HEALTH_BAR_Y, 1.0f, WHITE, playerHealth, playerMaxHealth);


    // ammo
    // ammo bar frame
    Gun* gun = PlayerGetGun(playerReference);
    spriteDraw("healthbar_0001", AMMO_BAR_X, AMMO_BAR_Y, FLIP_NONE, 0.0f, UI_SCALE, UI_SCALE, WHITE, LAYER_UI, true);
    for (int i = 1; i < gun->maxAmmo; i++){
        spriteDraw("healthbar_0002", AMMO_BAR_X + (i*AMMO_BAR_SEGMENT_WIDTH), AMMO_BAR_Y, FLIP_NONE, 0.0f, UI_SCALE, UI_SCALE, WHITE, LAYER_UI, true);
    }
    spriteDraw("healthbar_0003", AMMO_BAR_X + ((gun->maxAmmo - 1) * HEALTH_BAR_SEGMENT_WIDTH) + HEALTH_BAR_LAST_SEGMENT_OFFSET, AMMO_BAR_Y, FLIP_NONE, 0.0f, UI_SCALE, UI_SCALE, WHITE, LAYER_UI, true);

    // ammo bar
    for (int i = 0; i < gun->ammoCount; i++){
        spriteDraw("healthbar_0005", AMMO_BAR_X + (i * AMMO_BAR_SEGMENT_WIDTH) + HEALTH_BAR_START_OFFSET, AMMO_BAR_Y, FLIP_NONE, 0.0f, UI_SCALE, UI_SCALE, WHITE, LAYER_UI, true);
    }

    // ammo text
    FontDraw("%d/%d", AMMO_BAR_X + (gun->maxAmmo * AMMO_BAR_SEGMENT_WIDTH) + HEALTH_BAR_START_OFFSET + 10, AMMO_BAR_Y, 1.0f, WHITE, gun->ammoCount, gun->maxAmmo);



    // money display
    spriteDraw("healthbar_0001", MONEY_DISPLAY_X, MONEY_DISPLAY_Y, FLIP_NONE, 0.0f, UI_SCALE, UI_SCALE, WHITE, LAYER_UI, true);
    for (int i = 1; i < MONEY_DISPLAY_WIDTH; i++){
        spriteDraw("healthbar_0002", MONEY_DISPLAY_X + (i*AMMO_BAR_SEGMENT_WIDTH), MONEY_DISPLAY_Y, FLIP_NONE, 0.0f, UI_SCALE, UI_SCALE, WHITE, LAYER_UI, true);
    }
    spriteDraw("healthbar_0003", MONEY_DISPLAY_X + ((MONEY_DISPLAY_WIDTH - 1) * HEALTH_BAR_SEGMENT_WIDTH) + HEALTH_BAR_LAST_SEGMENT_OFFSET, MONEY_DISPLAY_Y, FLIP_NONE, 0.0f, UI_SCALE, UI_SCALE, WHITE, LAYER_UI, true);

    // draw icon
    spriteDraw("coin_0001", MONEY_DISPLAY_X + MONEY_DISPLAY_ICON_OFFSET, MONEY_DISPLAY_Y, FLIP_NONE, 0.0f, UI_SCALE, UI_SCALE, WHITE, LAYER_UI, true);
    FontDraw("%8d", MONEY_DISPLAY_X + MONEY_DISPLAY_TEXT_OFFSET, MONEY_DISPLAY_Y, 1.0f, MONEY_COLOR, playerMoney);

    // draw fading text
    float moneyFadingPercentage = (float)playerPickupTimer / MONEY_FADING_TIMER;
    Color moneyColor = (Color){255, 255, 0, (unsigned char) (moneyFadingPercentage * 255)};
    FontDraw("%+8d", MONEY_DISPLAY_X + MONEY_DISPLAY_TEXT_OFFSET, MONEY_DISPLAY_Y - MONEY_FADING_OFFSET + (moneyFadingPercentage * MONEY_FADING_OFFSET), 1.0f, moneyColor, playerPickupAmmount);
    playerPickupTimer -= playerPickupTimer > 0;
    playerPickupAmmount *= playerPickupTimer > 0;
    
}


void PlayerManagerHurtPlayer(int damage){
    playerHealth -= damage;
}

void PlayerManagerAddMoney(int ammount){
    playerMoney += ammount;
    playerPickupTimer = MONEY_FADING_TIMER;
    playerPickupAmmount += ammount;
}
