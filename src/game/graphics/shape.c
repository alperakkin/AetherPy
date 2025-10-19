#include <stdlib.h>
#include "game/graphics/shape.h"

ShapeRectangle *CreateRectangle(Vector3 *size, Color *color)
{

    ShapeRectangle *obj = malloc(sizeof(ShapeRectangle));
    obj->color = *color;
    obj->size = *size;

    return obj;
}
