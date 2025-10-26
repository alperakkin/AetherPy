#include "api/graphics_api.h"

PyTypeObject apiColorType;
PyTypeObject apiShapeType;

PyObject *apiColor_getR(apiColor *self, void *closure)
{
    return PyFloat_FromDouble(self->c_obj->R);
}

int apiColor_setR(apiColor *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_obj->R = (int)v;
    return 0;
}

PyObject *apiColor_getG(apiColor *self, void *closure)
{
    return PyFloat_FromDouble(self->c_obj->G);
}

int apiColor_setG(apiColor *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_obj->G = (int)v;
    return 0;
}

PyObject *apiColor_getB(apiColor *self, void *closure)
{
    return PyFloat_FromDouble(self->c_obj->B);
}

int apiColor_setB(apiColor *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_obj->B = (int)v;
    return 0;
}

PyObject *apiColor_getA(apiColor *self, void *closure)
{
    return PyFloat_FromDouble(self->c_obj->A);
}

int apiColor_setA(apiColor *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_obj->A = (int)v;
    return 0;
}
PyObject *apiColor_repr(apiColor *self)
{
    ColorProp *color = (ColorProp *)self->c_obj;
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

PyGetSetDef apiColor_getset[] = {
    {"R", (getter)apiColor_getR, (setter)apiColor_setR, "R", NULL},
    {"G", (getter)apiColor_getG, (setter)apiColor_setG, "G", NULL},
    {"B", (getter)apiColor_getB, (setter)apiColor_setB, "B", NULL},
    {"A", (getter)apiColor_getA, (setter)apiColor_setA, "A", NULL},
    {NULL}};

PyTypeObject apiColorType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "Aether.Color",
    .tp_basicsize = sizeof(apiColor),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_getset = apiColor_getset,
    .tp_repr = (reprfunc)apiColor_repr,

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

    ColorProp *c_color = CreateColor(R, G, B, A);

    apiColor *py_color = (apiColor *)PyType_GenericNew(&apiColorType, NULL, NULL);

    py_color->c_obj = c_color;

    return (PyObject *)py_color;
}

PyObject *apiShape_get_size(apiShape *self, void *closure)
{
    if (!self->c_obj)
    {
        PyErr_SetString(PyExc_AttributeError, "Rectangle Not Exists!");
        return NULL;
    }
    apiVector3Prop *vect = (apiVector3Prop *)PyType_GenericNew(&apiVector3PropType, NULL, NULL);

    vect->c_obj = &self->c_obj->size;

    return (PyObject *)vect;
}
int apiShape_set_size(apiShape *self, apiVector3Prop *value, void *closure)
{
    if (!PyObject_TypeCheck(value, &apiVector3PropType))
    {
        PyErr_SetString(PyExc_TypeError, "Expected Vector");
        return -1;
    }
    apiVector3Prop *vec = (apiVector3Prop *)value;

    self->c_obj->size.x = vec->c_obj->x;
    self->c_obj->size.y = vec->c_obj->y;
    self->c_obj->size.z = vec->c_obj->z;

    return 0;
}

PyObject *apiShape_get_color(apiShape *self, void *closure)
{
    if (!self->c_obj)
    {
        PyErr_SetString(PyExc_AttributeError, "Rectangle Not Exists!");
        return NULL;
    }
    apiColor *color = (apiColor *)PyType_GenericNew(&apiColorType, NULL, NULL);

    color->c_obj = &self->c_obj->color;

    return (PyObject *)color;
}
int apiShape_set_color(apiShape *self, apiColor *value, void *closure)
{
    if (!PyObject_TypeCheck(value, &apiColorType))
    {
        PyErr_SetString(PyExc_TypeError, "Expected Color");
        return -1;
    }
    apiColor *color = (apiColor *)value;

    self->c_obj->color.R = color->c_obj->R;
    self->c_obj->color.G = color->c_obj->G;
    self->c_obj->color.B = color->c_obj->B;
    self->c_obj->color.A = color->c_obj->A;

    return 0;
}

PyObject *apiShape_repr(apiShape *self)
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

    Vector3Prop *c_size = ((apiVector3Prop *)py_size)->c_obj;
    ColorProp *c_color = ((apiColor *)py_color)->c_obj;

    Shape *rect = CreateShape(RECTANGLE, c_size, c_color);

    apiShape *py_rect = (apiShape *)PyType_GenericNew(&apiShapeType, NULL, NULL);
    py_rect->c_obj = rect;

    return (PyObject *)py_rect;
}

PyObject *py_createCircle(PyObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *py_size = NULL;
    PyObject *py_color = NULL;

    static char *kwlist[] = {"size", "color", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_size, &py_color))
        return NULL;

    Vector3Prop *c_size = ((apiVector3Prop *)py_size)->c_obj;
    ColorProp *c_color = ((apiColor *)py_color)->c_obj;

    Shape *circle = CreateShape(CIRCLE, c_size, c_color);

    apiShape *py_circle = (apiShape *)PyType_GenericNew(&apiShapeType, NULL, NULL);
    py_circle->c_obj = circle;

    return (PyObject *)py_circle;
}

PyObject *py_createText(PyObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *py_size = NULL;
    PyObject *py_color = NULL;
    char *py_text = NULL;

    static char *kwlist[] = {"text", "size", "color", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "sOO", kwlist, &py_text, &py_size, &py_color))
        return NULL;

    Vector3Prop *c_size = ((apiVector3Prop *)py_size)->c_obj;
    ColorProp *c_color = ((apiColor *)py_color)->c_obj;
    char *value = (char *)py_text;

    Shape *c_text = CreateShape(TEXT, c_size, c_color);
    c_text->value = strdup(value);
    apiShape *py_text_obj = (apiShape *)PyType_GenericNew(&apiShapeType, NULL, NULL);
    py_text_obj->c_obj = c_text;

    return (PyObject *)py_text_obj;
}

PyGetSetDef apiShape_getset[] = {
    {"size", (getter)apiShape_get_size, (setter)apiShape_set_size, "size", NULL},
    {"color", (getter)apiShape_get_color, (setter)apiShape_set_color, "color", NULL},
    {NULL}};

PyTypeObject apiShapeType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "Aether.shape",
    .tp_basicsize = sizeof(apiShape),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_getset = apiShape_getset,
    .tp_repr = (reprfunc)apiShape_repr,

};

PyMethodDef GraphicsMethods[] = {
    {"Color", (PyCFunction)py_createColor, METH_VARARGS | METH_KEYWORDS, "Create Color Object"},
    {"Rectangle", (PyCFunction)py_createRectangle, METH_VARARGS | METH_KEYWORDS, "Create Rectangle Object"},
    {"Circle", (PyCFunction)py_createCircle, METH_VARARGS | METH_KEYWORDS, "Create Circle Object"},
    {"Text", (PyCFunction)py_createText, METH_VARARGS | METH_KEYWORDS, "Create Text Object"},
    {NULL, NULL, 0, NULL}};

PyModuleDef graphic_module = {
    PyModuleDef_HEAD_INIT,
    "graphics",
    NULL,
    -1,
    GraphicsMethods};

PyMODINIT_FUNC PyInit_graphics(void)
{
    if (PyType_Ready(&apiColorType) < 0)
        return NULL;
    if (PyType_Ready(&apiShapeType) < 0)
        return NULL;

    PyObject *m = PyModule_Create(&graphic_module);
    Py_INCREF(&apiColorType);
    PyModule_AddObject(m, "ColorRGBA", (PyObject *)&apiColorType);
    PyModule_AddObject(m, "Shape", (PyObject *)&apiShapeType);
    return m;
}
