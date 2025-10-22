#pragma once
#include "game/graphics/color.h"
#include "game/transform.h"

typedef enum
{
    EMPTY,
    RECTANGLE,
} ShapeType;
typedef struct
{
    Vector3Prop size;
    ColorProp color;
    ShapeType type;
} Shape;

Shape *CreateShape(ShapeType type, Vector3Prop *size, ColorProp *color);
char *get_shape_name(ShapeType type);