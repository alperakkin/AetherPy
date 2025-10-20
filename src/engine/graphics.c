#include "engine/graphics.h"

bool draw_gameobject(Screen *screen, GameObject *obj)
{
    if (!obj)
    {
        printf("ERROR: obj is NULL\n");
        return true;
    }
    if (!obj->shape)
    {
        printf("WARNING: obj->shape is NULL for obj at %p (name: %s)\n", (void *)obj, obj->name ? obj->name : "(noname)");
        return true;
    }

    switch (obj->shape->type)
    {
    case RECTANGLE:
    {

        draw_rectangle(screen->renderer, obj);
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

        if (draw_gameobject(screen, object_register.list[i]) == false)
            return false;
    }
    return true;
}
