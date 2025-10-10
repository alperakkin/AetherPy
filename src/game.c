#include "game.h"

ObjectRegister object_register = {NULL, 0};

void register_GameObject(GameObject *obj)
{
    GameObject **new_list = realloc(object_register.list,
                                    sizeof(GameObject *) * (object_register.object_count + 1));
    if (!new_list)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    object_register.list = new_list;
    object_register.list[object_register.object_count++] = obj;
}

GameObject *createGameObjectC(const char *name)
{
    GameObject *obj = malloc(sizeof(GameObject));
    obj->name = strdup(name);
    register_GameObject(obj);
    return obj;
}

GameObject *getGameObjectC(const char *name)
{
    for (int i = 0; i < object_register.object_count; i++)
    {
        GameObject *obj = object_register.list[i];
        if (strcmp(obj->name, name) == 0)
            return obj;
    }
    return NULL;
}

void destroyAllGameObjects(void)
{
    for (int i = 0; i < object_register.object_count; i++)
    {
        free(object_register.list[i]->name);
        free(object_register.list[i]);
    }
    free(object_register.list);
    object_register.list = NULL;
    object_register.object_count = 0;
}

PyMemberDef PyGameObject_members[] = {
    {"name", T_STRING, offsetof(PyGameObject, name), 0, "object name"},
    {NULL}};

PyTypeObject PyGameObjectType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "game.GameObject",
    .tp_basicsize = sizeof(PyGameObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_members = PyGameObject_members,
    .tp_repr = PyGameObject_repr,
};

PyObject *PyGameObject_repr(PyObject *self)
{
    PyGameObject *obj = (PyGameObject *)self;
    return PyUnicode_FromFormat("GameObject(name='%s')", obj->name);
}

PyObject *py_CreateGameObject(PyObject *self, PyObject *args, PyObject *kwds)
{
    const char *name;

    static char *kwlist[] = {"name", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "s|i", kwlist, &name))
        return NULL;

    createGameObjectC(name);

    PyGameObject *py_obj = (PyGameObject *)PyType_GenericNew(&PyGameObjectType, NULL, NULL);
    py_obj->name = strdup(name);

    return (PyObject *)py_obj;
}

PyObject *py_GetGameObject(PyObject *self, PyObject *args)
{
    const char *name;
    if (!PyArg_ParseTuple(args, "s", &name))
        return NULL;

    GameObject *c_obj = getGameObjectC(name);
    if (!c_obj)
        Py_RETURN_NONE;

    PyGameObject *py_obj = (PyGameObject *)PyType_GenericNew(&PyGameObjectType, NULL, NULL);
    py_obj->name = strdup(c_obj->name);

    return (PyObject *)py_obj;
}

PyMethodDef GameMethods[] = {
    {"CreateGameObject", (PyCFunction)py_CreateGameObject, METH_VARARGS | METH_KEYWORDS, "Create a game object"},
    {"GetGameObject", py_GetGameObject, METH_VARARGS, "Get a game object by name"},
    {NULL, NULL, 0, NULL}};

PyModuleDef game_module = {
    PyModuleDef_HEAD_INIT,
    "game",
    NULL,
    -1,
    GameMethods};

PyMODINIT_FUNC PyInit_game(void)
{
    if (PyType_Ready(&PyGameObjectType) < 0)
        return NULL;

    PyObject *m = PyModule_Create(&game_module);
    Py_INCREF(&PyGameObjectType);
    PyModule_AddObject(m, "GameObject", (PyObject *)&PyGameObjectType);
    return m;
}
