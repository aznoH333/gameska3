#include "gamestateManager.h"
#include "enemyCoordinator.h"
#include "terrainSystem.h"
#include "gameLib/worldObjectManager.h"


GameState currentGamestate = GAME_STATE_GAME;
void GameStateUpdate(){
    switch (currentGamestate) {
        case GAME_STATE_GAME:
            TerrainUpdate();
            EnemyCoordinatorUpdate();
            break;
    }
}


void GameStateSwitch(GameState newState){
    currentGamestate = newState;
}


void GameStateProgressLevel(){
    EnemyCoordinatorStartNewWave();
    WorldObjectManagerClear();
    TerrainGenerateNewRoom();
}