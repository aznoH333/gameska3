#include "fileUtils.h"
#include <dirent.h>
#include "debug.h"
#include <stddef.h>
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

Vector* getFilesInFolder(const char* folderPath){
    DIR *dir;
    struct dirent *ent;

    Vector* output = VectorInit();

    if ((dir = opendir (folderPath)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (TextFindIndex(ent->d_name, ".") == 0){
                continue;
            }

            if (ent->d_type == DT_DIR){
                char* path = malloc(255);
                sprintf(path, "%s/%s", folderPath, ent->d_name);
                
                Vector* recursiveOutput = getFilesInFolder(path);

                free(path);

                for (int i = 0; i < recursiveOutput->elementCount; i++){
                    VectorAdd(output, VectorGet(recursiveOutput, i));
                }
                VectorFree(recursiveOutput);
            }else {
                char* path = malloc(255);

                sprintf(path, "%s/%s", folderPath, ent->d_name);

                
                VectorAdd(output, path);
            }
        }
        closedir (dir);
    } else {
        crashMessage("Could not open directory %s", folderPath);
    }

    return output;
}