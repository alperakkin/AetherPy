#include <stdlib.h>
#include "game/graphics/shape.h"

Shape *CreateShape(ShapeType type, Vector3 *size, Color *color)
{

    Shape *obj = malloc(sizeof(Shape));
    obj->color = *color;
    obj->size = *size;
    obj->type = type;

    return obj;
}

char *get_shape_name(ShapeType type)
{

    switch (type)
    {
    case RECTANGLE:
        return "Rectangle";
    default:
        return "N/A";
    }
}