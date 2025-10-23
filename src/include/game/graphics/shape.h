#pragma once
#include "game/graphics/color.h"
#include "game/transform.h"

typedef enum
{
    EMPTY,
    RECTANGLE,
    CIRCLE,
    TEXT
} ShapeType;
typedef struct
{
    Vector3Prop size;
    ColorProp color;
    ShapeType type;
    void *value;

} Shape;

Shape *CreateShape(ShapeType type, Vector3Prop *size, ColorProp *color);
char *get_shape_name(ShapeType type);