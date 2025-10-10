#ifndef GAME_H
#define GAME_H

#include <Python.h>
#include <structmember.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    PyObject_HEAD char *name;
} PyGameObject;

PyObject *py_CreateGameObject(PyObject *self, PyObject *args);
PyObject *PyGameObject_repr(PyObject *self);
PyMODINIT_FUNC PyInit_game(void);

/* Tip ve modül objelerini C tarafında tanımla */
extern PyTypeObject PyGameObjectType;
extern PyModuleDef game_module;
extern PyMethodDef GameMethods[];
extern PyMemberDef PyGameObject_members[];

#endif
