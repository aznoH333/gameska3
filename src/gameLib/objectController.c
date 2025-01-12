#include "objectController.h"
#include <stdlib.h>
#include "numberUtils.h"
#include "memoryMacros.h"



ObjectInteraction* ObjectInteractionInit(int type, void* value){
    ObjectInteraction* this = malloc(sizeof(ObjectInteraction));
    this->interactionType = type;
    this->interactionValue = value;
    return this;
}

void ObjectInteractionFree(ObjectInteraction* this){
    free(this->interactionValue);
    free(this);
}


ObjectController* ObjectControllerInit(){
    ObjectController* this = malloc(sizeof(ObjectController));

    this->objectCollide = UNDEFINED;
    this->objectDestroy = UNDEFINED;
    this->objectUpdate = UNDEFINED;
    this->objectCleanUp = UNDEFINED;
    this->objectInteract = UNDEFINED;

    return this;
}


unsigned int ObjectControllerGetHash(ObjectController* this){
    unsigned int hash = hashLong((unsigned long)this->objectCollide);
    hash ^= hashLong((unsigned long)this->objectDestroy);
    hash ^= hashLong((unsigned long)this->objectUpdate);
    hash ^= hashLong((unsigned long)this->objectCleanUp);
    hash ^= hashLong((unsigned long)this->objectInteract);
    return hash;
}


