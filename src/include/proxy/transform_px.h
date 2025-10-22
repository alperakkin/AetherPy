#pragma once
#include <Python.h>
#include "game/transform.h"
extern PyTypeObject ProxyVector3PropType;
typedef struct
{
    PyObject_HEAD Vector3Prop *c_obj;
} ProxyVector3Prop;

PyObject *ProxyVector3Prop_getx(ProxyVector3Prop *self, void *closure);

int ProxyVector3Prop_setx(ProxyVector3Prop *self, PyObject *value, void *closure);

PyObject *ProxyVector3Prop_gety(ProxyVector3Prop *self, void *closure);

int ProxyVector3Prop_sety(ProxyVector3Prop *self, PyObject *value, void *closure);

PyObject *ProxyVector3Prop_getz(ProxyVector3Prop *self, void *closure);

int ProxyVector3Prop_setz(ProxyVector3Prop *self, PyObject *value, void *closure);

PyObject *ProxyVector3Prop_repr(ProxyVector3Prop *self);

PyObject *ProxyVector3Prop_add(PyObject *a, PyObject *b);

PyObject *py_createV3(PyObject *self, PyObject *args, PyObject *kwds);
PyMODINIT_FUNC PyInit_transform(void);