#pragma once
#include <structmember.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game/scene.h"

typedef enum
{
    W,
    A,
    S,
    D,
    MOUSE_MOVE,
    MOUSE_CLICK
} KeyCode;

typedef enum
{
    POS_X,
    POS_Y,
    POS_ALL,
    ROT_X,
    ROT_Y,
    SIZE_X,
    SIZE_Y
} PropertyType;

typedef enum
{
    KEYBOARD,
    MOUSE

} ControlType;

typedef struct
{
    KeyCode key;
    int property;
    float delta;
} ControlBinding;

typedef struct
{
    GameObject *object;
    int binding_count;
    ControlBinding *bindings;
    ControlType type;
} ControlProp;

typedef struct
{
    ControlProp **list;
    int count;
} ControlRegister;

ControlProp *CreateControl(GameObject *obj, ControlBinding *bindings, int count, ControlType *control_type);
extern ControlRegister control_register;