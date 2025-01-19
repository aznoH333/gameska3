#ifndef HASH_MAP
#define HASH_MAP


#include "vector.h"
#include "pair.h"

#define GenericHashFunction int (*hashFunction)(void*)

struct HashMap{
    Vector* valueBucket;
    GenericHashFunction;
}; typedef struct HashMap HashMap;




HashMap* HashMapInit(GenericHashFunction);
void HashMapPut(HashMap* this, Pair values);
Pair* HashMapGet(HashMap* this, void* key);
void HashMapDispose(HashMap* this);
void HashMapDisposeFreeValues(HashMap* this);

#endif