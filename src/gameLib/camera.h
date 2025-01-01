#ifndef CAMERA
#define CAMERA

#include "raylib.h"

void resetCamera();
void updateCamera();
void setCameraTarget(float x, float y);
Camera2D* getCamera();
float getInWorldMousePositionX();
float getInWorldMousePositionY();
void addScreenshake(float screenShakeAmmount);



#endif