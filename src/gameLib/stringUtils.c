#include "stringUtils.h"
#include "memoryMacros.h"
#include <stdlib.h>
#include <stdbool.h>


char* StringSubstring(char* this, int startPosition, int length){
    char* output = malloc(length + 1);

    for (int i = 0; i < length; i++){
        output[i] = this[i + startPosition];
    }
    output[length] = 0;

    return output;
}


int StringIndexOf(char* this, char* needle){
    for (int i = 0; this[i] != 0; i++){
        bool found = true;
        for (int j = 0; needle[j] != 0; j++){
            if (this[i] != needle[j]){
                found = false;
                break;
            }
        }

        if (found){
            return i;
        }
    }
    return -1;
}


int StringLastIndexOf(char* this, char* needle){
    int lastIndex = -1;
    for (int i = 0; this[i] != 0; i++){
        bool found = true;
        for (int j = 0; needle[j] != 0; j++){
            if (this[i] != needle[j]){
                found = false;
                break;
            }
        }

        if (found){
            lastIndex = i;
        }
    }
    return lastIndex;
}



int StringLength(char* this){
    int i = 0;
    while (this[i] != 0){
        i++;
    }
    return i;
}


