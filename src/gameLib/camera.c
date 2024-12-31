#include "camera.h"
#include "screenUtils.h"

Camera2D camera;
#define DEFAULT_ZOOM 3.0f

void resetCamera(){
    camera.offset = (Vector2){(int)(getWindowWidth() / 2) - 32,(int)(getWindowHeight() / 2) - 32};
    camera.target = (Vector2){0.0f, 0.0f};
    camera.rotation = 0.0f;
    camera.zoom = DEFAULT_ZOOM;
}


void setCameraTarget(float x, float y){
    camera.target = (Vector2){x, y};
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

