#include "objectController.h"
#include <stdlib.h>

ObjectController* ObjectControllerInit(){
    ObjectController* this = malloc(sizeof(ObjectController));

    this->objectCollide = 0;
    this->objectDestroy = 0;
    this->objectUpdate = 0;

    return this;
}