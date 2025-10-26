#pragma once
#include <Python.h>
#include "game/transform.h"
extern PyTypeObject apiVector3PropType;
typedef struct
{
    PyObject_HEAD Vector3Prop *c_obj;
} apiVector3Prop;

PyObject *apiVector3Prop_getx(apiVector3Prop *self, void *closure);

int apiVector3Prop_setx(apiVector3Prop *self, PyObject *value, void *closure);

PyObject *apiVector3Prop_gety(apiVector3Prop *self, void *closure);

int apiVector3Prop_sety(apiVector3Prop *self, PyObject *value, void *closure);

PyObject *apiVector3Prop_getz(apiVector3Prop *self, void *closure);

int apiVector3Prop_setz(apiVector3Prop *self, PyObject *value, void *closure);

PyObject *apiVector3Prop_repr(apiVector3Prop *self);

PyObject *apiVector3Prop_add(PyObject *a, PyObject *b);

PyObject *py_createV3(PyObject *self, PyObject *args, PyObject *kwds);
PyMODINIT_FUNC PyInit_transform(void);