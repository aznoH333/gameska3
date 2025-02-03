#include "sounds.h"
#include "fileUtils.h"
#include <raylib.h>
#include "stringUtils.h"
#include <stdlib.h>
#include "debug.h"


#define MAX_LOADED_SOUNDS 256

struct SoundPair{
    char* name;
    Sound sound;
};

struct SoundPair loadedSounds[MAX_LOADED_SOUNDS];
int loadedSoundCount = 0;




void soundsLoadAll(){

    InitAudioDevice();
    Vector* files = getFilesInFolder("./resources/sounds/");

    for (int i = 0; i < files->elementCount; i++){
        if (i > MAX_LOADED_SOUNDS){
            crashMessage("error max sound limit exceeded");
        }
        
        char* path = VectorGet(files, i);

        int indexOf = StringLastIndexOf(path, "/");

        char* soundFileName = StringSubstring(path, indexOf + 1, StringLength(path) - indexOf);
        char* soundName = StringSubstring(soundFileName, 0, StringIndexOf(soundFileName, "."));

        loadedSounds[loadedSoundCount] = (struct SoundPair){soundName, LoadSound(path)};

        free(path);
        free(soundFileName);

        loadedSoundCount++;
    }
}


void soundsUnloadAll(){
    for (int i = 0; i < loadedSoundCount; i++){
        UnloadSound(loadedSounds[i].sound);
        free(loadedSounds[i].name);
    }

    CloseAudioDevice();
}


void soundPlay(const char* soundName){
    soundPlayV(soundName, 1.0f);
}


Sound getSound(const char* soundName){
    for (int i = 0; i < loadedSoundCount; i++){
        struct SoundPair* p = &loadedSounds[i];

        if (TextIsEqual(p->name, soundName)){
            return p->sound;
        }
    }
    crashMessage("sound not found [%s]", soundName);
    return (Sound){};
}

void soundPlayV(const char *soundName, float volume){
    Sound sound = getSound(soundName);

    SetSoundVolume(sound, volume);
    PlaySound(sound);
}