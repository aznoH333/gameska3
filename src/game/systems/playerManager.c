#include "playerManager.h"
#include "game/gameEnums/enumsInclude.h"
#include "gameLib/font.h"


WorldObject* playerReference = UNDEFINED;
int playerHealth = 5;
int playerMaxHealth = 5;


#define HEALTH_BAR_X 20.0f
#define HEALTH_BAR_Y 20.0f
#define UI_SCALE 3.0f
#define HEALTH_BAR_SEGMENT_WIDTH UI_SCALE * 8.0f
#define HEALTH_BAR_LAST_SEGMENT_OFFSET UI_SCALE * 6.0f
#define HEALTH_BAR_START_OFFSET UI_SCALE * 4.0f

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
}


void PlayerManagerHurtPlayer(int damage){
    playerHealth -= damage;
}
