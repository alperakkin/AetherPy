#include "proxy/transform_px.h"
PyTypeObject ProxyVector3PropType;

PyObject *ProxyVector3Prop_getx(ProxyVector3Prop *self, void *closure)
{
    return PyFloat_FromDouble(self->c_obj->x);
}

int ProxyVector3Prop_setx(ProxyVector3Prop *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_obj->x = (float)v;
    return 0;
}

PyObject *ProxyVector3Prop_gety(ProxyVector3Prop *self, void *closure)
{

    return PyFloat_FromDouble(self->c_obj->y);
}

int ProxyVector3Prop_sety(ProxyVector3Prop *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_obj->y = (float)v;
    return 0;
}

PyObject *ProxyVector3Prop_getz(ProxyVector3Prop *self, void *closure)
{

    return PyFloat_FromDouble(self->c_obj->z);
}

int ProxyVector3Prop_setz(ProxyVector3Prop *self, PyObject *value, void *closure)
{

    double v = PyFloat_AsDouble(value);
    self->c_obj->z = (float)v;
    return 0;
}

PyObject *ProxyVector3Prop_repr(ProxyVector3Prop *self)
{
    Vector3Prop *vec = (Vector3Prop *)self->c_obj;
    if (!vec)
    {
        PyErr_SetString(PyExc_AttributeError, "Vector3Prop not assigned");
        return NULL;
    }
    char buf[128];
    snprintf(buf, sizeof(buf), "Vector3Prop(x=%f, y=%f, z=%f)",
             (double)vec->x,
             (double)vec->y,
             (double)vec->z);

    return PyUnicode_FromFormat(buf);
}

PyObject *ProxyVector3Prop_add(PyObject *a, PyObject *b)
{
    if (!PyObject_TypeCheck(a, &ProxyVector3PropType) || !PyObject_TypeCheck(b, &ProxyVector3PropType))
    {
        PyErr_SetString(PyExc_TypeError, "Sum elements must be Vector3Prop");
        return NULL;
    }
    ProxyVector3Prop *vect_1 = (ProxyVector3Prop *)a;
    ProxyVector3Prop *vect_2 = (ProxyVector3Prop *)b;

    ProxyVector3Prop *result = (ProxyVector3Prop *)PyType_GenericNew(&ProxyVector3PropType, NULL, NULL);
    if (!result)
        return NULL;
    result->c_obj = CreateVector3Prop(
        vect_1->c_obj->x + vect_2->c_obj->x,
        vect_1->c_obj->y + vect_2->c_obj->y,
        vect_1->c_obj->z + vect_2->c_obj->z);
    return (PyObject *)result;
}

PyNumberMethods ProxyVector3Prop_as_number = {
    .nb_add = ProxyVector3Prop_add,
};

PyGetSetDef ProxyVector3Prop_getset[] = {
    {"x", (getter)ProxyVector3Prop_getx, (setter)ProxyVector3Prop_setx, "x", NULL},
    {"y", (getter)ProxyVector3Prop_gety, (setter)ProxyVector3Prop_sety, "y", NULL},
    {"z", (getter)ProxyVector3Prop_getz, (setter)ProxyVector3Prop_setz, "z", NULL},
    {NULL}};

PyTypeObject ProxyVector3PropType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "Aether.Vector3Prop",
    .tp_basicsize = sizeof(ProxyVector3Prop),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_getset = ProxyVector3Prop_getset,
    .tp_repr = (reprfunc)ProxyVector3Prop_repr,
    .tp_as_number = &ProxyVector3Prop_as_number,

};

PyObject *py_createV3(PyObject *self, PyObject *args, PyObject *kwds)
{
    float x = 0;
    float y = 0;
    float z = 0;
    static char *kwlist[] = {"x", "y", "z", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "fff", kwlist, &x, &y, &z))
        return NULL;

    Vector3Prop *c_vec = CreateVector3Prop(x, y, z);

    ProxyVector3Prop *py_vec = (ProxyVector3Prop *)PyType_GenericNew(&ProxyVector3PropType, NULL, NULL);

    py_vec->c_obj = c_vec;

    return (PyObject *)py_vec;
}

PyMethodDef TransformMethods[] = {
    {"Vector", (PyCFunction)py_createV3, METH_VARARGS | METH_KEYWORDS, "Create V3 Instance"},
    {NULL, NULL, 0, NULL}};

PyModuleDef game_module = {
    PyModuleDef_HEAD_INIT,
    "transform",
    NULL,
    -1,
    TransformMethods};

PyMODINIT_FUNC PyInit_transform(void)
{
    if (PyType_Ready(&ProxyVector3PropType) < 0)
        return NULL;

    PyObject *m = PyModule_Create(&game_module);
    Py_INCREF(&ProxyVector3PropType);
    PyModule_AddObject(m, "Vector3Prop", (PyObject *)&ProxyVector3PropType);
    return m;
}