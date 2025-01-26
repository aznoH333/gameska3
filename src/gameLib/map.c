#include "map.h"
#include <stdlib.h>
#include "debug.h"


Map* MapInit(bool (*comparisonFunction)(void*, void*)){
    Map* this = malloc(sizeof(Map));
    this->values = VectorInit();
    this->comparisonFunction = comparisonFunction;
    return this;
}


void MapPut(Map* this, Pair pair){
    Pair* val = malloc(sizeof(pair));
    val->first = pair.first;
    val->second = pair.second;

    VectorAdd(this->values, val);
}


int findIndexOf(Map* this, void* key){

    for (int i = 0; i < this->values->elementCount; i++){
        Pair* p = VectorGet(this->values, i);

        if (this->comparisonFunction(key, p->first)){
            return i;
        }
    }

    return -1;
}


Pair* MapGet(Map* this, void* key){
    int indexOf = findIndexOf(this, key);

    return VectorGet(this->values, indexOf);
}


bool MapContains(Map* this, void* key){
    return findIndexOf(this, key) >= 0;
}



void MapRemove(Map* this, void* key){
    int indexOf = findIndexOf(this, key);
    if (indexOf == -1){
        crashMessage("cant remove value [%p] from map", key);
    }

    VectorRemove(this->values, indexOf);
}


void MapFree(Map* this){
    for (int i = 0; i < this->values->elementCount; i++){
        free(VectorGet(this->values, i));
    }
    VectorFree(this->values);
    free(this);
}


void MapFreeKeys(Map* this){
    for (int i = 0; i < this->values->elementCount; i++){
        free(((Pair*)VectorGet(this->values, i))->first);
    }
}


void MapFreeValues(Map* this){
    for (int i = 0; i < this->values->elementCount; i++){
        free(((Pair*)VectorGet(this->values, i))->second);
    }
}


Vector* MapGetAsVector(Map* this){
    return this->values;
}
