#include "camera.h"
#include "screenUtils.h"
#include "math.h"
#include "numberUtils.h"
#include "gamelib.h"

Camera2D camera;
#define DEFAULT_ZOOM 3.0f
float screenShake;
float cameraX;
float cameraY;
#define MAX_SCREEN_SHAKE_OFFSET 6.0f

void resetCamera(){
    camera.offset = (Vector2){(int)(getWindowWidth() / 2) - 32,(int)(getWindowHeight() / 2) - 32};
    camera.target = (Vector2){0.0f, 0.0f};
    camera.rotation = 0.0f;
    camera.zoom = DEFAULT_ZOOM;
    screenShake = 0;
}


void updateCamera(){
    float finalX = cameraX + (cos(screenShake + getGlobalTimer()) * fmin(screenShake * 0.75f, MAX_SCREEN_SHAKE_OFFSET));
    float finalY = cameraY + (sin(screenShake + getGlobalTimer()) * fmin(screenShake * 0.75f, MAX_SCREEN_SHAKE_OFFSET));

    camera.target.x = finalX;
    camera.target.y = finalY;

    
    screenShake = limitedIncrement(screenShake, 0.0f, fmax(0.15f, (screenShake * 0.5f)));
}


void setCameraTarget(float x, float y){
    cameraX = x;
    cameraY = y;
}


Camera2D* getCamera(){
    return &camera;
}


float getInWorldMousePositionX(){
    return (GetMouseX() / camera.zoom) + camera.target.x - (camera.offset.x / camera.zoom);
}


float getInWorldMousePositionY(){
    return (GetMouseY() / camera.zoom) + camera.target.y - (camera.offset.y / camera.zoom);
}


void addScreenshake(float screenShakeAmmount){
    screenShake += screenShakeAmmount;
}

