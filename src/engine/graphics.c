#include "engine/graphics.h"

bool draw_gameobject(Screen *screen, GameObject *obj)
{
    if (!obj)
        return true;

    if (!obj->shape)
        return true;

    switch (obj->shape->type)
    {
    case RECTANGLE:
    {

        draw_rectangle(screen->renderer, obj);
        break;
    }

    default:
        break;
    }
    return true;
}

bool draw_objects(Screen *screen)
{
    for (int i = 0; i < object_register.count; i++)
    {
        GameObject *obj = object_register.list[i];

        if (!obj)
        {
            printf("WARNING: object_register.list[%d] is NULL\n", i);
            continue;
        }

        if (!draw_gameobject(screen, obj))
            return false;
    }
    return true;
}
