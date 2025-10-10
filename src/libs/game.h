#ifndef GAME_H
#define GAME_H

#include <Python.h>
#include <structmember.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;

} GameObject;

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

typedef struct
{
    PyObject_HEAD char *name;

} PyGameObject;

PyObject *py_CreateGameObject(PyObject *self, PyObject *args, PyObject *kwds);
PyObject *py_GetGameObject(PyObject *self, PyObject *args);
PyObject *PyGameObject_repr(PyObject *self);

PyMODINIT_FUNC PyInit_game(void);
extern PyTypeObject PyGameObjectType;
extern PyModuleDef game_module;
extern PyMethodDef GameMethods[];
extern PyMemberDef PyGameObject_members[];

#endif
