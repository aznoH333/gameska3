#include "debug.h"
#include "raylib.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

DebugLevel debugLevel;
void setDebugLevel(DebugLevel level){
    debugLevel = level;

    switch (debugLevel) {
        case DEBUG_LEVEL_NORMAL:
            SetTraceLogLevel(LOG_FATAL);
            break;
        case DEBUG_LEVEL_DEBUG:
            SetTraceLogLevel(LOG_ALL);
            break;
    }
}


enum MessageType{
    MSG_INFO,
    MSG_ERROR
};


void printMessage(enum MessageType type, const char* format, va_list args){
    switch (type) {
        case MSG_INFO:
            if (debugLevel == DEBUG_LEVEL_NORMAL){
                return;
            }


            printf("\033[1;33m [INFO] : ");
            break;
        case MSG_ERROR:
            printf("\033[1;31m [ERROR] : ");
            break;
    }
    
    
    vprintf(format, args);
    printf("\033[1;0m \n");
}


void debugMessage(const char* format, ...){
    va_list ptr;
    va_start(ptr, format);

    printMessage(MSG_INFO, format, ptr);

    va_end(ptr);
}


void crashMessage(const char* format, ...){
    va_list ptr;
    va_start(ptr, format);

    printMessage(MSG_ERROR, format, ptr);

    va_end(ptr);

    exit(-1);
}


bool isDebugModeOn(){
    return debugLevel == DEBUG_LEVEL_DEBUG;
}
