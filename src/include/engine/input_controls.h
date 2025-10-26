#include "game/controls.h"

int map_raylib_keys(KeyCode key);
void controls();
void apply_binding(PropertyType prop, GameObject *obj, Vector2 new_val);
void control_keyboard(ControlBinding *binding, GameObject *obj);
void control_mouse(ControlBinding *binding, GameObject *obj);
void control_action(ControlBinding *binding, GameObject *obj, ControlType type);