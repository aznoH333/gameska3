#include "screenUtils.h"
#include "raylib.h"


int windowWidth;
int windowHeight;
bool isFullscreen;
int defaultWindowWidth;
int defaultWindowHeight;

void initWindow(int width, int height, const char* title, int targetFps){
    windowWidth = width;
    windowHeight = height;

    defaultWindowWidth = width;
    defaultWindowHeight = height;

    isFullscreen = false;

    InitWindow(width, height, title);
    SetTargetFPS(targetFps);


}

void closeWindow(){
    CloseWindow();
}

void fullscreen(){
    isFullscreen = !isFullscreen;
    
    
    // set width / height
    if (isFullscreen){
        int currentMonitorWidth = GetMonitorWidth(GetCurrentMonitor());
        int currentMonitorHeight = GetMonitorHeight(GetCurrentMonitor());    
        SetWindowSize(currentMonitorWidth, currentMonitorHeight);
        SetWindowPosition(0, 0);
        ToggleFullscreen();

    }else {
        SetWindowSize(defaultWindowWidth, defaultWindowHeight);
        ToggleFullscreen();
    }

}


int getWindowWidth(){
    return windowWidth;
}

int getWindowHeight(){
    return windowHeight;
}