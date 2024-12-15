#ifndef DEBUG
#define DEBUG

#include <stdbool.h>

enum DebugLevel{
    DEBUG_LEVEL_NORMAL,
    DEBUG_LEVEL_DEBUG
}; typedef enum DebugLevel DebugLevel;

void setDebugLevel(DebugLevel debugLevel);
void debugMessage(const char* format, ...);
void crashMessage(const char* format, ...);
bool isDebugModeOn();


#endif