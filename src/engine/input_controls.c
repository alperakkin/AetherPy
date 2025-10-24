
#include "engine/graphics.h"
#include "engine/input_controls.h"
#include "ctype.h"

int map_raylib_char(char c)
{
    switch (tolower(c))
    {
    case 'w':
        return KEY_W;
    case 'a':
        return KEY_A;
    case 's':
        return KEY_S;
    case 'd':
        return KEY_D;
    default:
        return -1;
    }
}

void control_action(ControlBinding *binding, GameObject *obj)
{
    int key = map_raylib_char(binding->key);

    if (IsKeyDown(key))
    {
        switch (binding->property)
        {
        case POS_X:
            obj->position.x += binding->delta;
            break;
        case POS_Y:
            obj->position.y += binding->delta;
            break;
        case ROT_X:
            obj->rotation.x += binding->delta;
            break;
        case ROT_Y:
            obj->rotation.y += binding->delta;
            break;
        case SIZE_X:
            obj->shape->size.x += binding->delta;
            break;
        case SIZE_Y:
            obj->shape->size.y += binding->delta;
            break;

        default:
            break;
        }
    }
}

void controls()
{

    for (int ind = 0; ind < control_register.count; ind++)
    {
        ControlProp *control = control_register.list[ind];
        for (int b_ind = 0; b_ind < control->binding_count; b_ind++)
        {
            ControlBinding *binding = &control->bindings[b_ind];
            GameObject *obj = control->object;
            control_action(binding, obj);
        }
    }
}