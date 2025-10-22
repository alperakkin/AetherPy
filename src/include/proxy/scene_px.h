#pragma once
#include <Python.h>
#include "game/scene.h"
#include "proxy/transform_px.h"
#include "proxy/graphics_px.h"

typedef struct
{
    PyObject_HEAD GameObject *c_obj;
} ProxyGameObject;

PyObject *ProxyGameObject_get_position(ProxyGameObject *self, void *closure);

int ProxyGameObject_set_position(ProxyGameObject *self, ProxyVector3Prop *value, void *closure);

PyObject *ProxyGameObject_get_rotation(ProxyGameObject *self, void *closure);
int ProxyGameObject_set_rotation(ProxyGameObject *self, ProxyVector3Prop *value, void *closure);
PyObject *ProxyGameObject_repr(PyObject *self);

PyObject *py_CreateGameObject(PyObject *self, PyObject *args, PyObject *kwds);
PyObject *py_GetGameObject(PyObject *self, PyObject *args);
PyMODINIT_FUNC PyInit_scene(void);