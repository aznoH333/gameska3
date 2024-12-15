#ifndef SCREEN_UTILS
#define SCREEN_UTILS


void initWindow(int width, int height, const char* title, int targetFps);
void closeWindow();
void fullscreen();
int getWindowWidth();
int getWindowHeight();


#endif