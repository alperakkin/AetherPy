#pragma once
#include <Python.h>
#include "game/graphics/color.h"
#include "game/graphics/shape.h"
#include "proxy/transform_px.h"

extern PyTypeObject ProxyShapeType;
typedef struct
{
    PyObject_HEAD ColorProp *c_obj;
} ProxyColor;

typedef struct
{
    PyObject_HEAD Shape *c_obj;
} ProxyShape;

PyObject *ProxyVector3Prop_getR(ProxyColor *self, void *closure);
int ProxyColor_setR(ProxyColor *self, PyObject *value, void *closure);

PyObject *ProxyVector3Prop_getG(ProxyColor *self, void *closure);
int ProxyColor_setG(ProxyColor *self, PyObject *value, void *closure);

PyObject *ProxyVector3Prop_getB(ProxyColor *self, void *closure);
int ProxyColor_setR(ProxyColor *self, PyObject *value, void *closure);

PyObject *ProxyVector3Prop_getB(ProxyColor *self, void *closure);
int ProxyColor_setR(ProxyColor *self, PyObject *value, void *closure);

PyObject *ProxyVector3Prop_getA(ProxyColor *self, void *closure);
int ProxyColor_setA(ProxyColor *self, PyObject *value, void *closure);

PyObject *ProxyColor_repr(ProxyColor *self);

PyObject *py_createColor(PyObject *self, PyObject *args, PyObject *kwds);

PyObject *ProxyShape_get_size(ProxyShape *self, void *closure);
int ProxyShape_set_size(ProxyShape *self, ProxyVector3Prop *value, void *closure);
PyObject *ProxyShape_get_color(ProxyShape *self, void *closure);
int ProxyShape_set_color(ProxyShape *self, ProxyColor *value, void *closure);
PyObject *ProxyShape_repr(ProxyShape *self);

PyObject *py_createRectangle(PyObject *self, PyObject *args, PyObject *kwds);
PyMODINIT_FUNC PyInit_graphics(void);