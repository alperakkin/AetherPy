#pragma once
#include "game/graphics/color.h"
#include "game/transform.h"

typedef enum
{
    RECTANGLE,
} ShapeType;
typedef struct
{
    Vector3 size;
    Color color;
    ShapeType type;
} Shape;

Shape *CreateShape(ShapeType type, Vector3 *size, Color *color);
char *get_shape_name(ShapeType type);