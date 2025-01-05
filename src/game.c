
#include "game/entities/enemies/enemyGrunt.h"
#include "gameLib/gamelibInclude.h"
#include "game/entitiesInclude.h"
#include "game/systemsInclude.h"
#include "gameLib/sprites.h"


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
    gameLibInit();

    // system init
    gameLibRegisterAdditionalSystem(&terrainUpdate);
    registerShader("resources/shaders/testShader.fs", SHADER_FRAGMENT);

    // temporary initialization
    PlayerInit(128, 128);
    InitEnemyGrunt(150, 128);
    generateNewRoom();

    // TODO : object collisions
    
    while (!WindowShouldClose())
    {
        gameLibUpdate();
    }

    gameLibEnd();    
    closeWindow();

    return 0;
}


