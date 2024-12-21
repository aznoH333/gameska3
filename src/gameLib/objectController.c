#include "objectController.h"
#include <stdlib.h>
#include "numberUtils.h"


ObjectController* ObjectControllerInit(){
    ObjectController* this = malloc(sizeof(ObjectController));

    this->objectCollide = 0;
    this->objectDestroy = 0;
    this->objectUpdate = 0;

    return this;
}


unsigned int ObjectControllerGetHash(ObjectController* this){
    unsigned int hash = hashInt((unsigned int)this->objectCollide);
    hash ^= hashInt((unsigned int)this->objectDestroy);
    hash ^= hashInt((unsigned int)this->objectUpdate);
    return hash;
}
