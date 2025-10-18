#pragma once
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "settings.h"
#define MAX_FILES 1024
#define MAX_PATH 512

typedef struct
{
    char **files;
    int count;
} FileList;

char *join_scripts_path(const char *path);
FileList scan_folder(char *folder);
char *get_name(char *path);
void get_settings(const char *path, Settings *settings);
double deg_to_rad(double deg);
double rad_to_deg(double rad);

double normalize_deg(double deg);
double normalize_rad(double rad);
