#include "objectController.h"
#include <stdlib.h>
#include "numberUtils.h"
#include "memoryMacros.h"


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


