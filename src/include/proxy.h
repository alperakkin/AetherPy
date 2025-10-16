#pragma once
#include <Python.h>
#include "vectors.h"
#include "entity.h"
typedef PyModuleDef PyModuleDef;

typedef struct
{
    PyObject_HEAD GameObject *c_obj;
} ProxyGameObject;
typedef struct
{
    PyObject_HEAD Vector3 *c_obj;
} ProxyVector3;

#include "proxy.h"

PyTypeObject ProxyGameObjectType;
PyTypeObject ProxyVector3Type;

PyObject *ProxyVector3_getx(ProxyVector3 *self, void *closure);

int ProxyVector3_setx(ProxyVector3 *self, PyObject *value, void *closure);

PyObject *ProxyVector3_gety(ProxyVector3 *self, void *closure);

int ProxyVector3_sety(ProxyVector3 *self, PyObject *value, void *closure);

PyObject *ProxyVector3_getz(ProxyVector3 *self, void *closure);

int ProxyVector3_setz(ProxyVector3 *self, PyObject *value, void *closure);

PyObject *ProxyVector3_repr(ProxyVector3 *self);

PyObject *ProxyVector3_add(PyObject *a, PyObject *b);

PyObject *ProxyGameObject_get_position(ProxyGameObject *self, void *closure);

int ProxyGameObject_set_position(ProxyGameObject *self, ProxyVector3 *value, void *closure);

PyObject *ProxyGameObject_get_rotation(ProxyGameObject *self, void *closure);

PyObject *ProxyGameObject_repr(PyObject *self);

PyObject *py_CreateGameObject(PyObject *self, PyObject *args, PyObject *kwds);

PyObject *py_createV3(PyObject *self, PyObject *args, PyObject *kwds);

PyObject *py_GetGameObject(PyObject *self, PyObject *args);

PyMODINIT_FUNC PyInit_Aether(void);
