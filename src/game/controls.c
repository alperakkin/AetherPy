#include "game/controls.h"
ControlRegister control_register = {NULL, 0};

void RegisterControl(ControlProp *obj)
{
    ControlProp **new_list = realloc(control_register.list,
                                     sizeof(ControlProp *) * (control_register.count + 1));
    if (!new_list)
    {
        fprintf(stderr, "[ControlProp] Memory allocation failed\n");
        return;
    }
    control_register.list = new_list;
    control_register.list[control_register.count++] = obj;
}

ControlProp *CreateControl(GameObject *obj, ControlBinding *bindings, int count)
{
    ControlProp *ctrl = malloc(sizeof(ControlProp));
    ctrl->object = obj;
    ctrl->binding_count = count;
    ctrl->bindings = malloc(sizeof(ControlBinding) * count);
    memcpy(ctrl->bindings, bindings, sizeof(ControlBinding) * count);

    RegisterControl(ctrl);
    return ctrl;
}
