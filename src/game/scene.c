#include "scene.h"
ObjectRegister object_register = {NULL, 0};

void RegisterGameObject(GameObject *obj)
{
    GameObject **new_list = realloc(object_register.list,
                                    sizeof(GameObject *) * (object_register.object_count + 1));
    if (!new_list)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    object_register.list = new_list;
    object_register.list[object_register.object_count++] = obj;
}

GameObject *CreateGameObject(const char *name)
{
    GameObject *obj = malloc(sizeof(GameObject));
    obj->name = strdup(name);
    obj->position.x = 0.0f;
    obj->position.y = 0.0f;
    obj->position.z = 0.0f;

    obj->rotation.x = 0.0f;
    obj->rotation.y = 0.0f;
    obj->rotation.z = 0.0f;
    RegisterGameObject(obj);
    return obj;
}

GameObject *GetGameObject(const char *name)
{
    for (int i = 0; i < object_register.object_count; i++)
    {
        GameObject *obj = object_register.list[i];
        if (strcmp(obj->name, name) == 0)
            return obj;
    }
    return NULL;
}
