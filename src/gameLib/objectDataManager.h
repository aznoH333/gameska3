#ifndef OBJECT_DATA_MANAGER
#define OBJECT_DATA_MANAGER

void ObjectDataManagerInit();
int ObjectDataManagerAdd(void* data);
void* ObjectDataManagerGet(int index);
void ObjectDataManagerRemove(int index);
void ObjectDataManagerDispose();


#endif