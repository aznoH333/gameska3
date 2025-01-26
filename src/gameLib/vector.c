#include "vector.h"
#include <stdlib.h>
#include "debug.h"

#define DEFAULT_VECTOR_SIZE 25

Vector* VectorInit(){
    Vector* this = malloc(sizeof(Vector));

    this->size = DEFAULT_VECTOR_SIZE;
    this->elements = malloc(sizeof(void*) * this->size);
    this->elementCount = 0;

    return this;
}


void VectorAdd(Vector* this, void* element){
    if (this->elementCount >= this->size){
        // resize
        this->size *= 4;
        void** newArray = malloc(sizeof(void*) * this->size);

        // copy contents
        for (int i = 0; i < this->elementCount; i++){
            newArray[i] = this->elements[i];
        }

        free(this->elements);
        this->elements = newArray;
    }

    this->elements[this->elementCount] = element; 
    this->elementCount++;
}


void VectorRemove(Vector* this, int index){
    if (index < 0 || index > this->elementCount){
        crashMessage("Unable to remove element. Index [%d] is outside vector", index);
    }

    this->elementCount--;

    for (int i = index; i < this->elementCount; i++){
        this->elements[i] = this->elements[i+1];
    }
}



void* VectorGet(Vector* this, int index){
    
    return this->elements[index];
}


void VectorClear(Vector* this){
    this->elementCount = 0;
}



void VectorFree(Vector* this){
    free(this->elements);
    free(this);
}


void VectorFreeValues(Vector* this){
    for (int i = 0; i < this->elementCount; i++){
        free(this->elements[i]);
    }
    VectorFree(this);
}
