#ifndef SOUNDS
#define SOUNDS


void soundsLoadAll();
void soundsUnloadAll();
void soundPlay(const char* soundName);
void soundPlayV(const char *soundName, float volume);


#endif