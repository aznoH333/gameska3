#ifndef OBJECT_CONTROLLER_MANAGER
#define OBJECT_CONTROLLER_MANAGER

#include "objectController.h"


void ObjectControllerManagerInit();
void ObjectControllerManagerDispose();
int ObjectControllerManageRegisterOrGet(ObjectController* controller);
ObjectController* ObjectControllerManagerGet(int id);



#endif