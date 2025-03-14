
#include "game/entities/enemies/enemyGrunt.h"
#include "game/systems/enemyCoordinator.h"
#include "game/systems/gamestateManager.h"
#include "game/systems/terrainSystem.h"
#include "gameLib/debug.h"
#include "gameLib/font.h"
#include "gameLib/gamelib.h"
#include "gameLib/gamelibInclude.h"
#include "game/entitiesInclude.h"
#include "game/systemsInclude.h"
#include "gameLib/memoryMacros.h"
#include "gameLib/numberUtils.h"
#include "gameLib/screenUtils.h"
#include "gameLib/sprites.h"
#include <raylib.h>
#include "gameLib/hashMap.h"


int hashish(void* key){
    return hashInt(*((int*)key));
}

int main(int argc, char **argv)
{
    
    
    setDebugLevel(DEBUG_LEVEL_NORMAL);
    // handle args
    for (int i = 0; i < argc; i++){
        if (TextIsEqual(argv[i], "debug")){
            setDebugLevel(DEBUG_LEVEL_DEBUG);
        }
    }

    // init window
    initWindow(1280, 720, "Test window", 60);
    fullscreen();


    // init lib
    gameLibRegisterInitEvent(&EnemyCoordinatorInit);
    gameLibInit();


    // system init
    gameLibRegisterAdditionalSystem(&GameStateUpdate);
    gameLibRegisterDisposeEvent(&EnemyCoordinatorDispose);
    registerShader("resources/shaders/testShader.fs", SHADER_FRAGMENT);


    // temporary initialization
    //TerrainGenerateNewRoom(ROOM_GENERIC_COMBAT); // TODO : move this to gamestate manager
    GameStateProgressLevel();

    // TODO : sometimes enemies spawn outside the level

    
    while (!WindowShouldClose())
    {
        gameLibUpdate();

    }

    gameLibEnd();    
    closeWindow();

    return 0;
}


