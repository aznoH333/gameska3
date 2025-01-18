#ifndef GAME_LIB
#define GAME_LIB

void gameLibInit();
void gameLibEnd();
void gameLibRegisterAdditionalSystem(void (*systemUpdateFunction)());
void gameLibRegisterInitEvent(void (*systemInitFunction)());
void gameLibRegisterDisposeEvent(void (*systemDisposeFunction)());
void gameLibUpdate();
unsigned int getGlobalTimer();

#endif