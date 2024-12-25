#include "objectController.h"
#include <stdlib.h>
#include "numberUtils.h"
#include "memoryMacros.h"


ObjectController* ObjectControllerInit(){
    ObjectController* this = malloc(sizeof(ObjectController));

    this->objectCollide = UNDEFINED;
    this->objectDestroy = UNDEFINED;
    this->objectUpdate = UNDEFINED;

    return this;
}


unsigned int ObjectControllerGetHash(ObjectController* this){
    unsigned int hash = hashInt((unsigned int)this->objectCollide);
    hash ^= hashInt((unsigned int)this->objectDestroy);
    hash ^= hashInt((unsigned int)this->objectUpdate);
    return hash;
}
