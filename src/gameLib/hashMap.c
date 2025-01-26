#include "hashMap.h"
#include "pair.h"
#include "vector.h"
#include <stdlib.h>
#include "memoryMacros.h"
#include "debug.h"

#define HASH_KOEFICIENT 91

HashMap* HashMapInit(GenericHashFunction){
    HashMap* this = malloc(sizeof(HashMap));
    
    this->valueBucket = VectorInit();
    this->hashFunction = hashFunction;

    for (int i = 0; i < HASH_KOEFICIENT; i++){
        VectorAdd(this->valueBucket, VectorInit());
    }

    return this;
}


Pair* mapFind(HashMap* this, unsigned int key){
    debugMessage("got here %d", key);

    Vector* target = VectorGet(this->valueBucket, key % HASH_KOEFICIENT);

    for (int i = 0; i < target->elementCount; i++){
        Pair* p = VectorGet(target, i);
        if ((*(int*)(p->first)) == key){
            return p;
        }
    }

    return UNDEFINED;
}


void HashMapPut(HashMap* this, Pair values){
    initHeapVariable(unsigned int, key, this->hashFunction(values.first));


    if (mapFind(this, *key) != UNDEFINED){
        crashMessage("Map error. Key already present [%p]", values.first);
    }


    Pair* keyValue = malloc(sizeof(Pair));
    keyValue->first = key;
    keyValue->second = values.second;

    Vector* target = VectorGet(this->valueBucket, (*key) % HASH_KOEFICIENT);

    VectorAdd(target, keyValue);
}


Pair* HashMapGet(HashMap* this, void* key){
    unsigned int hashedKey = this->hashFunction(key);

    Pair* output = mapFind(this, hashedKey);

    if (output == UNDEFINED){
        crashMessage("Map error. Not found [%p]", key);
    }

    return output;
}

bool HashMapContains(HashMap* this, void* key){
    unsigned int hashedKey = this->hashFunction(key);
    Pair* output = mapFind(this, hashedKey);
    return output != UNDEFINED;
}



void hashDispose(HashMap* this, bool freeValues){
    for (int i = 0; i < HASH_KOEFICIENT; i++){
        Vector* target = VectorGet(this->valueBucket, i);
        for (int j = 0; j < target->elementCount; j++){
            Pair* p = VectorGet(target, j);
            free(p->first);

            if (freeValues){
                free(p->second);
            }
            free(p);
        }
        VectorFree(target);
    }

    VectorFree(this->valueBucket);

    free(this);
}


void HashMapDispose(HashMap* this){
    hashDispose(this, false);    
}

void HashMapDisposeFreeValues(HashMap* this){
    hashDispose(this, true);    
}