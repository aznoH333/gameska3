
#include "screenUtils.h"
#include "raylib.h"
#include "debug.h"
#include "gamelib.h"
#include "player.h"

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
    initWindow(800, 400, "Test window", 60);
    fullscreen();


    // init lib
    gameLibInit();

    PlayerInit(20, 20);


    while (!WindowShouldClose())
    {

        gameLibUpdate();
    }

    gameLibEnd();    
    closeWindow();

    return 0;
}
