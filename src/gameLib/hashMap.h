#ifndef HASH_MAP
#define HASH_MAP


#include "vector.h"
#include "pair.h"
#include <stdbool.h>

#define GenericHashFunction unsigned int (*hashFunction)(void*)

struct HashMap{
    Vector* valueBucket;
    GenericHashFunction;
}; typedef struct HashMap HashMap;




HashMap* HashMapInit(GenericHashFunction);
void HashMapPut(HashMap* this, Pair values);
bool HashMapContains(HashMap* this, void* key);
Pair* HashMapGet(HashMap* this, void* key);

void HashMapDispose(HashMap* this);
void HashMapDisposeFreeValues(HashMap* this);

#endif