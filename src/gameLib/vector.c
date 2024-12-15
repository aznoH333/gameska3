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


void* VectorGet(Vector* this, int index){
    if (index > this->elementCount || index < 0){
        crashMessage("Invalid vector access -> Vector[] vector size []", index, this->size);
    }
    
    return this->elements[index];
}


void VectorFree(Vector* this){
    free(this);
}