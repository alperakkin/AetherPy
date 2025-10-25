
#include "engine/graphics.h"
#include "engine/input_controls.h"
#include "ctype.h"

int map_raylib_keys(KeyCode key)
{
    switch (key)
    {
    case W:
        return KEY_W;
    case A:
        return KEY_A;
    case S:
        return KEY_S;
    case D:
        return KEY_D;
    default:
        return -1;
    }
}

void control_keyboard(ControlBinding *binding, GameObject *obj)
{
    int key = map_raylib_keys(binding->key);
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

void control_mouse(ControlBinding *binding, GameObject *obj)
{
    printf("Key is: %d\n", binding->key);
}

void control_action(ControlBinding *binding, GameObject *obj, ControlType type)
{

    switch (type)
    {
    case KEYBOARD:
        control_keyboard(binding, obj);
        break;
    case MOUSE:
        control_mouse(binding, obj);
        break;
    default:
        break;
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
            ControlType type = control->type;
            control_action(binding, obj, type);
        }
    }
}