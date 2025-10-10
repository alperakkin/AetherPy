#include <Python.h>
#include <structmember.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    PyObject_HEAD char *name;
} PyGameObject;

static PyObject *PyGameObject_repr(PyGameObject *self)
{
    return PyUnicode_FromFormat("GameObject(name='%s')", self->name);
}

static PyMemberDef PyGameObject_members[] = {
    {"name", T_STRING, offsetof(PyGameObject, name), 0, "object name"},
    {NULL}};

static PyTypeObject PyGameObjectType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "engine.GameObject",
    .tp_basicsize = sizeof(PyGameObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_members = PyGameObject_members,
    .tp_repr = (reprfunc)PyGameObject_repr,
};

static PyObject *py_CreateGameObject(PyObject *self, PyObject *args)
{
    const char *name;
    if (!PyArg_ParseTuple(args, "s", &name))
        return NULL;

    PyGameObject *obj = (PyGameObject *)PyType_GenericNew(&PyGameObjectType, NULL, NULL);
    if (!obj)
        return NULL;

    obj->name = strdup(name);
    return (PyObject *)obj;
}

static PyMethodDef EngineMethods[] = {
    {"CreateGameObject", py_CreateGameObject, METH_VARARGS, "Create a game object"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef engine_module = {
    PyModuleDef_HEAD_INIT,
    "engine",
    NULL,
    -1,
    EngineMethods};

PyMODINIT_FUNC PyInit_engine(void)
{
    if (PyType_Ready(&PyGameObjectType) < 0)
        return NULL;
    PyObject *m = PyModule_Create(&engine_module);
    Py_INCREF(&PyGameObjectType);
    PyModule_AddObject(m, "GameObject", (PyObject *)&PyGameObjectType);
    return m;
}
