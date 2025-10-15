#pragma once
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_FILES 1024
#define MAX_PATH 512

typedef struct
{
    char **files;
    int count;
} FileList;

FileList scan_folder(char *folder);
char *get_name(char *path);