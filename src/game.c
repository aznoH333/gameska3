
#include "screenUtils.h"
#include "raylib.h"

int main(void)
{

    initWindow(800, 420, "Test window", 60);
    fullscreen();

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

    return 0;
}
