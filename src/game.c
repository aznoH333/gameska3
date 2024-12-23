
#include "screenUtils.h"
#include "raylib.h"
#include "debug.h"
#include "gamelib.h"
#include "sprites.h"

#include "worldObjectManager.h"

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

    int x = 0;
    int y = 0;


    WorldObject* test = InitWorldObject(20, 20, 16, 16);
    test->spriteIndex = getSpriteIndex("debug_items_0001");
    WorldObjectManagerAddObject(test);

    while (!WindowShouldClose())
    {

        gameLibUpdate();

        if (IsKeyPressed(KEY_D)){
            fullscreen();
        }
        if (IsKeyDown(KEY_LEFT)){
            x--;
            test->x -= 1;
        }
        if (IsKeyDown(KEY_RIGHT)){
            test->x += 1;

            x++;
        }
        if (IsKeyDown(KEY_UP)){
            y--;
        }
        if (IsKeyDown(KEY_DOWN)){
            y++;
        }
        spriteDrawBasic("debug_man", x, y, FLIP_NONE, 0);
        spriteDrawBasic("debug_enemy", 100, 100, FLIP_NONE, 0);


    }

    gameLibEnd();    
    closeWindow();

    return 0;
}
