#ifndef EXIT
#define EXIT 

#include "stdbool.h"
#include "../../../gameLib/gamelibInclude.h"

struct ExitData{
    bool wantsToOpen;
    bool isOpen;
}; typedef struct ExitData ExitData;

void ExitInit(float x, float y, bool open);
void ExitOpen(WorldObject* exit);

#endif