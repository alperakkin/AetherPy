#include "engine/graphics.h"

void draw_rectangle(GameObject *obj)
{

    if (!obj)
    {
        printf("GameObject Drawing Error");
        return;
    }

    if (!obj->shape)
        return;

    DrawRectangle(
        (int)obj->position.x,
        (int)obj->position.y,
        (int)obj->shape->size.x,
        (int)obj->shape->size.y,
        (Color){
            obj->shape->color.R,
            obj->shape->color.G,
            obj->shape->color.B,
            obj->shape->color.A,

        });
}