#include "game.h"

PyMethodDef GameMethods[] = {
    {"CreateGameObject", py_CreateGameObject, METH_VARARGS, "Create a game object"},
    {NULL, NULL, 0, NULL}};

PyModuleDef game_module = {
    PyModuleDef_HEAD_INIT,
    "game",
    NULL,
    -1,
    GameMethods};

PyMemberDef PyGameObject_members[] = {
    {"name", T_STRING, offsetof(PyGameObject, name), 0, "object name"},
    {NULL}};

PyTypeObject PyGameObjectType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "game.GameObject",
    .tp_basicsize = sizeof(PyGameObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_members = PyGameObject_members,
    .tp_repr = PyGameObject_repr};

PyMODINIT_FUNC PyInit_game(void)
{
    if (PyType_Ready(&PyGameObjectType) < 0)
        return NULL;
    PyObject *m = PyModule_Create(&game_module);
    Py_INCREF(&PyGameObjectType);
    PyModule_AddObject(m, "GameObject", (PyObject *)&PyGameObjectType);
    return m;
}

PyObject *PyGameObject_repr(PyObject *self)
{
    PyGameObject *obj = (PyGameObject *)self;
    return PyUnicode_FromFormat("GameObject(name='%s')", obj->name);
}

PyObject *py_CreateGameObject(PyObject *self, PyObject *args)
{
    const char *name;
    if (!PyArg_ParseTuple(args, "s", &name))
        return NULL;

    PyGameObject *obj = (PyGameObject *)PyType_GenericNew(&PyGameObjectType, NULL, NULL);
    obj->name = strdup(name);
    return (PyObject *)obj;
}
