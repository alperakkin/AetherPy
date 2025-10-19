#pragma once
#include "game/graphics/color.h"
#include "game/transform.h"

typedef struct
{
    Vector3 size;
    Color color;

} ShapeRectangle;

ShapeRectangle *CreateRectangle(Vector3 *size, Color *color);