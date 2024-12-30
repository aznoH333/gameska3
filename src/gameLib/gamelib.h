#ifndef GAME_LIB
#define GAME_LIB

void gameLibInit();
void gameLibEnd();
void gameLibRegisterAdditionalSystem(void (*systemUpdateFunction)());
void gameLibUpdate();

#endif