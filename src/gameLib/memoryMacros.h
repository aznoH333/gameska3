#ifndef MEMORY_MACROS
#define MEMORY_MACROS

#include <stdlib.h>

#define UNDEFINED 0
#define initHeapVariable(type, name, value) type* name = malloc(sizeof(type)); *name = value


#endif