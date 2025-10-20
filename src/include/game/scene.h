#pragma once
#include <structmember.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game/transform.h"
#include "game/graphics/shape.h"

typedef struct
{
    char *name;
    Vector3 position;
    Vector3 rotation;
    Shape *shape;

} GameObject;

typedef struct
{
    GameObject **list;
    int count;
} ObjectRegister;

void RegisterGameObject(GameObject *obj);
GameObject *CreateGameObject(const char *name);
GameObject *GetGameObject(const char *name);
extern ObjectRegister object_register;