#ifndef GAME_H
#define GAME_H

#include <Python.h>
#include <structmember.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    float x;
    float y;
    float z;

} Vector3;

typedef struct
{
    PyObject_HEAD Vector3 *c_vec;
} PyVector3;

typedef struct
{
    char *name;
    Vector3 position;
    Vector3 rotation;

} GameObject;

typedef struct
{
    PyObject_HEAD char *name;
    GameObject *c_obj;
} PyGameObject;
typedef struct
{
    GameObject **list;
    int object_count;
} ObjectRegister;

extern ObjectRegister object_register;

GameObject *createGameObjectC(const char *name);
GameObject *getGameObjectC(const char *name);
void register_GameObject(GameObject *obj);
void destroyAllGameObjects(void);

PyObject *py_CreateGameObject(PyObject *self, PyObject *args, PyObject *kwds);
PyObject *py_GetGameObject(PyObject *self, PyObject *args);
PyObject *PyGameObject_repr(PyObject *self);

PyMODINIT_FUNC PyInit_game(void);
extern PyTypeObject PyGameObjectType;
extern PyModuleDef game_module;
extern PyMethodDef GameMethods[];
extern PyMemberDef PyGameObject_members[];

#endif
