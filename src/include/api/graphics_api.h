#pragma once
#include <Python.h>
#include "game/graphics/color.h"
#include "game/graphics/shape.h"
#include "api/transform_api.h"

extern PyTypeObject apiShapeType;
typedef struct
{
    PyObject_HEAD ColorProp *c_obj;
} apiColor;

typedef struct
{
    PyObject_HEAD Shape *c_obj;
} apiShape;

PyObject *apiVector3Prop_getR(apiColor *self, void *closure);
int apiColor_setR(apiColor *self, PyObject *value, void *closure);

PyObject *apiVector3Prop_getG(apiColor *self, void *closure);
int apiColor_setG(apiColor *self, PyObject *value, void *closure);

PyObject *apiVector3Prop_getB(apiColor *self, void *closure);
int apiColor_setR(apiColor *self, PyObject *value, void *closure);

PyObject *apiVector3Prop_getB(apiColor *self, void *closure);
int apiColor_setR(apiColor *self, PyObject *value, void *closure);

PyObject *apiVector3Prop_getA(apiColor *self, void *closure);
int apiColor_setA(apiColor *self, PyObject *value, void *closure);

PyObject *apiColor_repr(apiColor *self);

PyObject *py_createColor(PyObject *self, PyObject *args, PyObject *kwds);

PyObject *apiShape_get_size(apiShape *self, void *closure);
int apiShape_set_size(apiShape *self, apiVector3Prop *value, void *closure);
PyObject *apiShape_get_color(apiShape *self, void *closure);
int apiShape_set_color(apiShape *self, apiColor *value, void *closure);
PyObject *apiShape_repr(apiShape *self);

PyObject *py_createRectangle(PyObject *self, PyObject *args, PyObject *kwds);
PyObject *py_createCircle(PyObject *self, PyObject *args, PyObject *kwds);
PyObject *py_createText(PyObject *self, PyObject *args, PyObject *kwds);
PyMODINIT_FUNC PyInit_graphics(void);