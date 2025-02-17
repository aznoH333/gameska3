#include "screenUtils.h"
#include "raylib.h"
#include <math.h>
#include <unistd.h>
#include "debug.h"
#include "math.h"

int windowWidth;
int windowHeight;
bool isFullscreen;
int defaultWindowWidth;
int defaultWindowHeight;
int targetFps;
double lastUpdateTime = 0.0f;
double targetFrameTime;
double timeSinceLastFrame;


void initWindow(int width, int height, const char* title, int fps){
    windowWidth = width;
    windowHeight = height;

    defaultWindowWidth = width;
    defaultWindowHeight = height;

    isFullscreen = false;

    InitWindow(width, height, title);
    //SetTargetFPS(targetFps);
    targetFps = fps;
    targetFrameTime = 1.0 / fps;
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
        windowWidth = currentMonitorWidth;
        windowHeight = currentMonitorHeight;

    }else {
        ToggleFullscreen();
        SetWindowSize(defaultWindowWidth, defaultWindowHeight);
        windowWidth = defaultWindowWidth;
        windowHeight = defaultWindowHeight;
    }
}


int getWindowWidth(){
    return windowWidth;
}

int getWindowHeight(){
    return windowHeight;
}

void updateWindow(){
    PollInputEvents();
    SwapScreenBuffer();
    timeSinceLastFrame = (GetTime() - lastUpdateTime);
    if (timeSinceLastFrame < targetFrameTime){
        WaitTime(targetFrameTime - timeSinceLastFrame);
    }

    lastUpdateTime = GetTime();
}

