#ifndef PLAYER_MANAGER
#define PLAYER_MANAGER

#include "../../gameLib/gamelibInclude.h"


void PlayerManagerSetPlayer(WorldObject* player);
WorldObject* PlayerManagerGetPlayer();
void PlayerManagerUpdate();
void PlayerManagerHurtPlayer(int damage);
void PlayerManagerAddMoney(int ammount);


#endif