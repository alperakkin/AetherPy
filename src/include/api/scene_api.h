#pragma once
#include <Python.h>
#include "settings.h"
#include "game/scene.h"
#include "api/transform_api.h"
#include "api/graphics_api.h"

typedef struct
{
    PyObject_HEAD GameObject *c_obj;
} apiGameObject;
extern PyTypeObject apiGameObjectType;
PyObject *apiGameObject_get_position(apiGameObject *self, void *closure);

int apiGameObject_set_position(apiGameObject *self, apiVector3Prop *value, void *closure);

PyObject *apiGameObject_get_rotation(apiGameObject *self, void *closure);
int apiGameObject_set_rotation(apiGameObject *self, apiVector3Prop *value, void *closure);
PyObject *apiGameObject_repr(PyObject *self);

PyObject *py_CreateGameObject(PyObject *self, PyObject *args, PyObject *kwds);
PyObject *py_GetGameObject(PyObject *self, PyObject *args);
PyMODINIT_FUNC PyInit_scene(void);