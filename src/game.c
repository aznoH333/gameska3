
#include "screenUtils.h"
#include "raylib.h"
#include "debug.h"
#include "gamelib.h"

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
    initWindow(800, 420, "Test window", 60);
    fullscreen();


    // init lib
    gameLibInit();

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

            if (IsKeyPressed(KEY_D)){
                fullscreen();
            }

        EndDrawing();
    }

    closeWindow();
    gameLibEnd();    

    return 0;
}
