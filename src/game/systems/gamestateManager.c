#include "gamestateManager.h"
#include "terrainSystem.h"


GameState currentGamestate = GAME_STATE_GAME;
void GameStateUpdate(){
    switch (currentGamestate) {
        case GAME_STATE_GAME:
            TerrainUpdate();
            break;
    }
}


void GameStateSwitch(GameState newState){
    currentGamestate = newState;
}
