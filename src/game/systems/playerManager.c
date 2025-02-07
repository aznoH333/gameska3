#include "playerManager.h"

WorldObject* playerReference = UNDEFINED;

void PlayerManagerSetPlayer(WorldObject* player){
    playerReference = player;
}

WorldObject* PlayerManagerGetPlayer(){
    return playerReference;
}


void PlayerManagerUpdate(){
    
}
