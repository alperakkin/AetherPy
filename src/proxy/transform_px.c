#include "transform_px.h"
PyTypeObject ProxyVector3Type;
PyObject *ProxyVector3_getx(ProxyVector3 *self, void *closure)
{
    return PyFloat_FromDouble(self->c_obj->x);
}

int ProxyVector3_setx(ProxyVector3 *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_obj->x = (float)v;
    return 0;
}

PyObject *ProxyVector3_gety(ProxyVector3 *self, void *closure)
{

    return PyFloat_FromDouble(self->c_obj->y);
}

int ProxyVector3_sety(ProxyVector3 *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_obj->y = (float)v;
    return 0;
}

PyObject *ProxyVector3_getz(ProxyVector3 *self, void *closure)
{

    return PyFloat_FromDouble(self->c_obj->z);
}

int ProxyVector3_setz(ProxyVector3 *self, PyObject *value, void *closure)
{

    double v = PyFloat_AsDouble(value);
    self->c_obj->z = (float)v;
    return 0;
}

PyObject *ProxyVector3_repr(ProxyVector3 *self)
{
    Vector3 *vec = (Vector3 *)self->c_obj;
    if (!vec)
    {
        PyErr_SetString(PyExc_AttributeError, "Vector3 not assigned");
        return NULL;
    }
    char buf[128];
    snprintf(buf, sizeof(buf), "Vector3(x=%f, y=%f, z=%f)",
             (double)vec->x,
             (double)vec->y,
             (double)vec->z);

    return PyUnicode_FromFormat(buf);
}

PyObject *ProxyVector3_add(PyObject *a, PyObject *b)
{
    if (!PyObject_TypeCheck(a, &ProxyVector3Type) || !PyObject_TypeCheck(b, &ProxyVector3Type))
    {
        PyErr_SetString(PyExc_TypeError, "Sum elements must be Vector3");
        return NULL;
    }
    ProxyVector3 *vect_1 = (ProxyVector3 *)a;
    ProxyVector3 *vect_2 = (ProxyVector3 *)b;

    ProxyVector3 *result = (ProxyVector3 *)PyType_GenericNew(&ProxyVector3Type, NULL, NULL);
    if (!result)
        return NULL;
    result->c_obj = CreateVector3(
        vect_1->c_obj->x + vect_2->c_obj->x,
        vect_1->c_obj->y + vect_2->c_obj->y,
        vect_1->c_obj->z + vect_2->c_obj->z);
    return (PyObject *)result;
}

PyNumberMethods ProxyVector3_as_number = {
    .nb_add = ProxyVector3_add,
};

PyGetSetDef ProxyVector3_getset[] = {
    {"x", (getter)ProxyVector3_getx, (setter)ProxyVector3_setx, "x", NULL},
    {"y", (getter)ProxyVector3_gety, (setter)ProxyVector3_sety, "y", NULL},
    {"z", (getter)ProxyVector3_getz, (setter)ProxyVector3_setz, "z", NULL},
    {NULL}};

PyTypeObject ProxyVector3Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "Aether.Vector3",
    .tp_basicsize = sizeof(ProxyVector3),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_getset = ProxyVector3_getset,
    .tp_repr = (reprfunc)ProxyVector3_repr,
    .tp_as_number = &ProxyVector3_as_number,

};

PyObject *py_createV3(PyObject *self, PyObject *args, PyObject *kwds)
{
    float x = 0;
    float y = 0;
    float z = 0;
    static char *kwlist[] = {"x", "y", "z", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "fff", kwlist, &x, &y, &z))
        return NULL;

    Vector3 *c_vec = CreateVector3(x, y, z);

    ProxyVector3 *py_vec = (ProxyVector3 *)PyType_GenericNew(&ProxyVector3Type, NULL, NULL);

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
    if (PyType_Ready(&ProxyVector3Type) < 0)
        return NULL;

    PyObject *m = PyModule_Create(&game_module);
    Py_INCREF(&ProxyVector3Type);
    PyModule_AddObject(m, "Vector3", (PyObject *)&ProxyVector3Type);
    return m;
}