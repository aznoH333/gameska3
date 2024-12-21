#ifndef VECTOR
#define VECTOR

struct Vector{
    unsigned int elementCount;
    unsigned int size;
    void** elements;
};
typedef struct Vector Vector;

Vector* VectorInit();
void VectorAdd(Vector* this, void* element);
void* VectorGet(Vector* this, int index);
void VectorFree(Vector* this);
void VectorClear(Vector* this);
void VectorRemove(Vector* this, int index);


#endif