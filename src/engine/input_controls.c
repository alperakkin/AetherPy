
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

void apply_binding(PropertyType prop, GameObject *obj, Vector2 new_val)
{
    switch (prop)
    {
    case POS_X:
        obj->position.x = new_val.x;
        break;
    case POS_Y:
        obj->position.y = new_val.y;
        break;
    case ROT_X:
        obj->rotation.x = new_val.x;
        break;
    case ROT_Y:
        obj->rotation.y = new_val.y;
        break;
    case SIZE_X:
        obj->shape->size.x = new_val.x;
        break;
    case SIZE_Y:
        obj->shape->size.y = new_val.y;
        break;
    case POS_ALL:
        obj->position.x = new_val.x;
        obj->position.y = new_val.y;
        // TODO: add z axis for 3D rendering
    default:
        break;
    }
}

void control_keyboard(ControlBinding *binding, GameObject *obj)
{
    int key = map_raylib_keys(binding->key);
    Vector2 new_val = {obj->position.x + binding->delta,
                       obj->position.y + binding->delta};
    if (IsKeyDown(key))
    {
        apply_binding(binding->property,
                      obj, new_val);
    }
}

void control_mouse(ControlBinding *binding, GameObject *obj)
{
    Vector2 pos = GetMousePosition();

    switch (binding->key)
    {
    case MOUSE_MOVE:
    {
        Vector2 new_val = {pos.x + binding->delta,
                           pos.y + binding->delta};
        apply_binding(binding->property,
                      obj,
                      new_val);
        break;
    }

    case MOUSE_CLICK:
    {
        Vector2 new_val = {pos.x + binding->delta,
                           pos.y + binding->delta};
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            apply_binding(binding->property,
                          obj,
                          new_val);
        break;
    }

    default:
        break;
    }
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