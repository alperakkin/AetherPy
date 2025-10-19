#include "proxy/graphics_px.h"

PyTypeObject ProxyColorType;

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

PyMethodDef GraphicsMethods[] = {
    {"Color", (PyCFunction)py_createColor, METH_VARARGS | METH_KEYWORDS, "Create Color Object"},
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

    PyObject *m = PyModule_Create(&graphic_module);
    Py_INCREF(&ProxyColorType);
    PyModule_AddObject(m, "ColorRGBA", (PyObject *)&ProxyColorType);
    return m;
}
