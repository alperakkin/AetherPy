#include "proxy/graphics_px.h"

PyTypeObject ProxyColorType;
PyTypeObject ProxyShapeType;

PyObject *ProxyColor_getR(ProxyColor *self, void *closure)
{
    return PyFloat_FromDouble(self->c_obj->R);
}

int ProxyColor_setR(ProxyColor *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_obj->R = (int)v;
    return 0;
}

PyObject *ProxyColor_getG(ProxyColor *self, void *closure)
{
    return PyFloat_FromDouble(self->c_obj->G);
}

int ProxyColor_setG(ProxyColor *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_obj->G = (int)v;
    return 0;
}

PyObject *ProxyColor_getB(ProxyColor *self, void *closure)
{
    return PyFloat_FromDouble(self->c_obj->B);
}

int ProxyColor_setB(ProxyColor *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_obj->B = (int)v;
    return 0;
}

PyObject *ProxyColor_getA(ProxyColor *self, void *closure)
{
    return PyFloat_FromDouble(self->c_obj->A);
}

int ProxyColor_setA(ProxyColor *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_obj->A = (int)v;
    return 0;
}
PyObject *ProxyColor_repr(ProxyColor *self)
{
    Color *color = (Color *)self->c_obj;
    if (!color)
    {
        PyErr_SetString(PyExc_AttributeError, "Color not assigned");
        return NULL;
    }
    char buf[128];
    snprintf(buf, sizeof(buf), "Color(R=%d, G=%d, B=%d, A=%d)",
             (int)color->R,
             (int)color->G,
             (int)color->B,
             (int)color->A);

    return PyUnicode_FromFormat(buf);
}

PyGetSetDef ProxyColor_getset[] = {
    {"R", (getter)ProxyColor_getR, (setter)ProxyColor_setR, "R", NULL},
    {"G", (getter)ProxyColor_getG, (setter)ProxyColor_setG, "G", NULL},
    {"B", (getter)ProxyColor_getB, (setter)ProxyColor_setB, "B", NULL},
    {"A", (getter)ProxyColor_getA, (setter)ProxyColor_setA, "A", NULL},
    {NULL}};

PyTypeObject ProxyColorType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "Aether.Color",
    .tp_basicsize = sizeof(ProxyColor),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_getset = ProxyColor_getset,
    .tp_repr = (reprfunc)ProxyColor_repr,

};

PyObject *py_createColor(PyObject *self, PyObject *args, PyObject *kwds)
{
    int R = 0;
    int G = 0;
    int B = 0;
    int A = 0;
    static char *kwlist[] = {"R", "G", "B", "A", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "iiii", kwlist, &R, &G, &B, &A))
        return NULL;

    Color *c_color = CreateColor(R, G, B, A);

    ProxyColor *py_color = (ProxyColor *)PyType_GenericNew(&ProxyColorType, NULL, NULL);

    py_color->c_obj = c_color;

    return (PyObject *)py_color;
}

PyObject *ProxyShape_get_size(ProxyShape *self, void *closure)
{
    if (!self->c_obj)
    {
        PyErr_SetString(PyExc_AttributeError, "Rectangle Not Exists!");
        return NULL;
    }
    ProxyVector3 *vect = (ProxyVector3 *)PyType_GenericNew(&ProxyVector3Type, NULL, NULL);

    vect->c_obj = &self->c_obj->size;

    return (PyObject *)vect;
}
int ProxyShape_set_size(ProxyShape *self, ProxyVector3 *value, void *closure)
{
    if (!PyObject_TypeCheck(value, &ProxyVector3Type))
    {
        PyErr_SetString(PyExc_TypeError, "Expected Vector");
        return -1;
    }
    ProxyVector3 *vec = (ProxyVector3 *)value;

    self->c_obj->size.x = vec->c_obj->x;
    self->c_obj->size.y = vec->c_obj->y;
    self->c_obj->size.z = vec->c_obj->z;

    return 0;
}

PyObject *ProxyShape_get_color(ProxyShape *self, void *closure)
{
    if (!self->c_obj)
    {
        PyErr_SetString(PyExc_AttributeError, "Rectangle Not Exists!");
        return NULL;
    }
    ProxyColor *color = (ProxyColor *)PyType_GenericNew(&ProxyColorType, NULL, NULL);

    color->c_obj = &self->c_obj->color;

    return (PyObject *)color;
}
int ProxyShape_set_color(ProxyShape *self, ProxyColor *value, void *closure)
{
    if (!PyObject_TypeCheck(value, &ProxyColorType))
    {
        PyErr_SetString(PyExc_TypeError, "Expected Color");
        return -1;
    }
    ProxyColor *color = (ProxyColor *)value;

    self->c_obj->color.R = color->c_obj->R;
    self->c_obj->color.G = color->c_obj->G;
    self->c_obj->color.B = color->c_obj->B;
    self->c_obj->color.A = color->c_obj->A;

    return 0;
}

PyObject *ProxyShape_repr(ProxyShape *self)
{
    Shape *shape = (Shape *)self->c_obj;
    if (!shape)
    {
        PyErr_SetString(PyExc_AttributeError, "Shape not assigned");
        return NULL;
    }
    char buf[128];
    snprintf(buf, sizeof(buf), "Shape(name=%s, size=(%f, %f), color=(%d, %d, %d, %d))",
             get_shape_name(shape->type),
             (float)shape->size.x,
             (float)shape->size.y,
             (int)shape->color.R,
             (int)shape->color.G,
             (int)shape->color.B,
             (int)shape->color.A);

    return PyUnicode_FromFormat(buf);
}

PyObject *py_createRectangle(PyObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *py_size = NULL;
    PyObject *py_color = NULL;

    static char *kwlist[] = {"size", "color", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_size, &py_color))
        return NULL;

    Vector3 *c_size = ((ProxyVector3 *)py_size)->c_obj;
    Color *c_color = ((ProxyColor *)py_color)->c_obj;

    Shape *rect = CreateShape(RECTANGLE, c_size, c_color);

    ProxyShape *py_rect = (ProxyShape *)PyType_GenericNew(&ProxyShapeType, NULL, NULL);
    py_rect->c_obj = rect;

    return (PyObject *)py_rect;
}

PyGetSetDef ProxyShape_getset[] = {
    {"size", (getter)ProxyShape_get_size, (setter)ProxyShape_set_size, "size", NULL},
    {"color", (getter)ProxyShape_get_color, (setter)ProxyShape_set_color, "R", NULL},
    {NULL}};

PyTypeObject ProxyShapeType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "Aether.shape",
    .tp_basicsize = sizeof(ProxyShape),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_getset = ProxyShape_getset,
    .tp_repr = (reprfunc)ProxyShape_repr,

};

PyMethodDef GraphicsMethods[] = {
    {"Color", (PyCFunction)py_createColor, METH_VARARGS | METH_KEYWORDS, "Create Color Object"},
    {"Rectangle", (PyCFunction)py_createRectangle, METH_VARARGS | METH_KEYWORDS, "Create Rectangle Object"},
    {NULL, NULL, 0, NULL}};

PyModuleDef graphic_module = {
    PyModuleDef_HEAD_INIT,
    "graphics",
    NULL,
    -1,
    GraphicsMethods};

PyMODINIT_FUNC PyInit_graphics(void)
{
    if (PyType_Ready(&ProxyColorType) < 0)
        return NULL;
    if (PyType_Ready(&ProxyShapeType) < 0)
        return NULL;

    PyObject *m = PyModule_Create(&graphic_module);
    Py_INCREF(&ProxyColorType);
    PyModule_AddObject(m, "ColorRGBA", (PyObject *)&ProxyColorType);
    PyModule_AddObject(m, "Shape", (PyObject *)&ProxyShapeType);
    return m;
}
