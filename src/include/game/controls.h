#pragma once
#include <structmember.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game/scene.h"

typedef enum
{
    POS_X,
    POS_Y,
    ROT_X,
    ROT_Y,
    SIZE_X,
    SIZE_Y
} PropertyType;

typedef struct
{
    char key;
    int property;
    float delta;
} ControlBinding;

typedef struct
{
    GameObject *object;
    int binding_count;
    ControlBinding *bindings;
} ControlProp;

typedef struct
{
    ControlProp **list;
    int count;
} ControlRegister;

ControlProp *CreateControl(GameObject *obj, ControlBinding *bindings, int count);
extern ControlRegister control_register;