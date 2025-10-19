#include <stdlib.h>
#include "game/graphics/shape.h"

RenderComponent *create_rectangle(Vector3 size, Color color)
{
    ShapeRectangle *rect = malloc(sizeof(ShapeRectangle));
    rect->color = color;
    rect->size = size;

    RenderComponent *component = malloc(sizeof(RenderComponent));
    component->type = RECTANGLE;
    component->draw = component;
    return component;
}