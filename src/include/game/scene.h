#ifndef ENTITY_H
#define ENTITY_H
#pragma once
#include <structmember.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "transform.h"
typedef struct
{
    char *name;
    Vector3 position;
    Vector3 rotation;

} GameObject;

typedef struct
{
    GameObject **list;
    int object_count;
} ObjectRegister;

void RegisterGameObject(GameObject *obj);
GameObject *CreateGameObject(const char *name);
GameObject *GetGameObject(const char *name);
#endif