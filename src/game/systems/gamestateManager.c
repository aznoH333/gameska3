#include "gamestateManager.h"
#include "enemyCoordinator.h"
#include "terrainSystem.h"
#include "gameLib/worldObjectManager.h"
#include "playerManager.h"



int currentLevel = 0;
RoomType currentRoomType;

GameState currentGamestate = GAME_STATE_GAME;
void GameStateUpdate(){
    switch (currentGamestate) {
        case GAME_STATE_GAME:
            TerrainUpdate();
            EnemyCoordinatorUpdate();
            PlayerManagerUpdate();
            break;
    }
}


void GameStateSwitch(GameState newState){
    currentGamestate = newState;
}


void GameStateProgressLevel(){
    // set current room type
    if ((currentLevel)%2==0){
        currentRoomType = ROOM_GENERIC_COMBAT;
    }else {
        currentRoomType = ROOM_GENERIC_SHOP;
    }

    debugMessage("wth man %d %d", currentLevel, currentRoomType);

    // spawn enemies
    EnemyCoordinatorStartNewWave(GetRoomTypeProperties(currentRoomType).spawnEnemies);


    WorldObjectManagerClear();
    TerrainGenerateNewRoom(currentRoomType);
    currentLevel++;
}