#pragma once
#include <Python.h>
#include "game/transform.h"

typedef struct
{
    PyObject_HEAD Vector3 *c_obj;
} ProxyVector3;

PyObject *ProxyVector3_getx(ProxyVector3 *self, void *closure);

int ProxyVector3_setx(ProxyVector3 *self, PyObject *value, void *closure);

PyObject *ProxyVector3_gety(ProxyVector3 *self, void *closure);

int ProxyVector3_sety(ProxyVector3 *self, PyObject *value, void *closure);

PyObject *ProxyVector3_getz(ProxyVector3 *self, void *closure);

int ProxyVector3_setz(ProxyVector3 *self, PyObject *value, void *closure);

PyObject *ProxyVector3_repr(ProxyVector3 *self);

PyObject *ProxyVector3_add(PyObject *a, PyObject *b);

PyObject *py_createV3(PyObject *self, PyObject *args, PyObject *kwds);
PyMODINIT_FUNC PyInit_transform(void);