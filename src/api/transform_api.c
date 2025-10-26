#include "api/transform_api.h"
PyTypeObject apiVector3PropType;

PyObject *apiVector3Prop_getx(apiVector3Prop *self, void *closure)
{
    return PyFloat_FromDouble(self->c_obj->x);
}

int apiVector3Prop_setx(apiVector3Prop *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_obj->x = (float)v;
    return 0;
}

PyObject *apiVector3Prop_gety(apiVector3Prop *self, void *closure)
{

    return PyFloat_FromDouble(self->c_obj->y);
}

int apiVector3Prop_sety(apiVector3Prop *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_obj->y = (float)v;
    return 0;
}

PyObject *apiVector3Prop_getz(apiVector3Prop *self, void *closure)
{

    return PyFloat_FromDouble(self->c_obj->z);
}

int apiVector3Prop_setz(apiVector3Prop *self, PyObject *value, void *closure)
{

    double v = PyFloat_AsDouble(value);
    self->c_obj->z = (float)v;
    return 0;
}

PyObject *apiVector3Prop_repr(apiVector3Prop *self)
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

PyObject *apiVector3Prop_add(PyObject *a, PyObject *b)
{
    if (!PyObject_TypeCheck(a, &apiVector3PropType) || !PyObject_TypeCheck(b, &apiVector3PropType))
    {
        PyErr_SetString(PyExc_TypeError, "Sum elements must be Vector3Prop");
        return NULL;
    }
    apiVector3Prop *vect_1 = (apiVector3Prop *)a;
    apiVector3Prop *vect_2 = (apiVector3Prop *)b;

    apiVector3Prop *result = (apiVector3Prop *)PyType_GenericNew(&apiVector3PropType, NULL, NULL);
    if (!result)
        return NULL;
    result->c_obj = CreateVector3Prop(
        vect_1->c_obj->x + vect_2->c_obj->x,
        vect_1->c_obj->y + vect_2->c_obj->y,
        vect_1->c_obj->z + vect_2->c_obj->z);
    return (PyObject *)result;
}

PyNumberMethods apiVector3Prop_as_number = {
    .nb_add = apiVector3Prop_add,
};

PyGetSetDef apiVector3Prop_getset[] = {
    {"x", (getter)apiVector3Prop_getx, (setter)apiVector3Prop_setx, "x", NULL},
    {"y", (getter)apiVector3Prop_gety, (setter)apiVector3Prop_sety, "y", NULL},
    {"z", (getter)apiVector3Prop_getz, (setter)apiVector3Prop_setz, "z", NULL},
    {NULL}};

PyTypeObject apiVector3PropType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "Aether.Vector3Prop",
    .tp_basicsize = sizeof(apiVector3Prop),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_getset = apiVector3Prop_getset,
    .tp_repr = (reprfunc)apiVector3Prop_repr,
    .tp_as_number = &apiVector3Prop_as_number,

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

    apiVector3Prop *py_vec = (apiVector3Prop *)PyType_GenericNew(&apiVector3PropType, NULL, NULL);

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
    if (PyType_Ready(&apiVector3PropType) < 0)
        return NULL;

    PyObject *m = PyModule_Create(&game_module);
    Py_INCREF(&apiVector3PropType);
    PyModule_AddObject(m, "Vector3Prop", (PyObject *)&apiVector3PropType);
    return m;
}