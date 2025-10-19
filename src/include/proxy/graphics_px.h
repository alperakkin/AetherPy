#pragma once
#include <Python.h>
#include "game/graphics/color.h"
#include "game/graphics/shape.h"
#include "proxy/transform_px.h"

typedef struct
{
    PyObject_HEAD Color *c_obj;
} ProxyColor;

typedef struct
{
    PyObject_HEAD ShapeRectangle *c_rect;
} ProxyRectangle;

PyObject *ProxyVector3_getR(ProxyColor *self, void *closure);
int ProxyColor_setR(ProxyColor *self, PyObject *value, void *closure);

PyObject *ProxyVector3_getG(ProxyColor *self, void *closure);
int ProxyColor_setG(ProxyColor *self, PyObject *value, void *closure);

PyObject *ProxyVector3_getB(ProxyColor *self, void *closure);
int ProxyColor_setR(ProxyColor *self, PyObject *value, void *closure);

PyObject *ProxyVector3_getB(ProxyColor *self, void *closure);
int ProxyColor_setR(ProxyColor *self, PyObject *value, void *closure);

PyObject *ProxyVector3_getA(ProxyColor *self, void *closure);
int ProxyColor_setA(ProxyColor *self, PyObject *value, void *closure);

PyObject *ProxyColor_repr(ProxyColor *self);

PyObject *py_createColor(PyObject *self, PyObject *args, PyObject *kwds);

PyObject *ProxyRectangle_get_size(ProxyRectangle *self, void *closure);
int ProxyRectangle_set_size(ProxyRectangle *self, ProxyVector3 *value, void *closure);
PyObject *ProxyRectangle_get_color(ProxyRectangle *self, void *closure);
int ProxyRectangle_set_color(ProxyRectangle *self, ProxyColor *value, void *closure);
PyObject *ProxyRectangle_repr(ProxyRectangle *self);

PyObject *py_createRectangle(PyObject *self, PyObject *args, PyObject *kwds);
PyMODINIT_FUNC PyInit_graphics(void);