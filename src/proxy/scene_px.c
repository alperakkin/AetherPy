#include "proxy/scene_px.h"
PyTypeObject ProxyGameObjectType;
PyTypeObject ProxyVector3Type;

PyMemberDef ProxyGameObject_members[] = {
    {"name", T_STRING, offsetof(GameObject, name), 0, "Name"},
    {NULL}};

PyObject *ProxyGameObject_get_position(ProxyGameObject *self, void *closure)
{
    if (!self->c_obj)
    {
        PyErr_SetString(PyExc_AttributeError, "GameObject Not Exists!");
        return NULL;
    }
    ProxyVector3 *vec = (ProxyVector3 *)PyType_GenericNew(&ProxyVector3Type, NULL, NULL);

    vec->c_obj = &self->c_obj->position;

    return (PyObject *)vec;
}
int ProxyGameObject_set_position(ProxyGameObject *self, ProxyVector3 *value, void *closure)
{
    if (!PyObject_TypeCheck(value, &ProxyVector3Type))
    {
        PyErr_SetString(PyExc_TypeError, "Expected Vector3");
        return -1;
    }
    ProxyVector3 *vec = (ProxyVector3 *)value;

    self->c_obj->position.x = vec->c_obj->x;
    self->c_obj->position.y = vec->c_obj->y;
    self->c_obj->position.z = vec->c_obj->z;

    return 0;
}

PyObject *ProxyGameObject_get_rotation(ProxyGameObject *self, void *closure)
{
    ProxyVector3 *vec = PyObject_New(ProxyVector3, &ProxyVector3Type);

    vec->c_obj = &self->c_obj->rotation;
    return (PyObject *)vec;
}

PyGetSetDef ProxyGameObject_getset[] = {
    {"position", (getter)ProxyGameObject_get_position, (setter)ProxyGameObject_set_position, "position", NULL},
    {"rotation", (getter)ProxyGameObject_get_rotation, NULL, "rotation", NULL},
    {NULL}};

PyTypeObject ProxyGameObjectType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "Aether.GameObject",
    .tp_basicsize = sizeof(ProxyGameObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_members = ProxyGameObject_members,
    .tp_getset = ProxyGameObject_getset,
    .tp_repr = ProxyGameObject_repr,
};

PyObject *ProxyGameObject_repr(PyObject *self)
{
    ProxyGameObject *obj = (ProxyGameObject *)self;
    return PyUnicode_FromFormat("GameObject(name='%s')", obj->c_obj->name);
}

PyObject *py_CreateGameObject(PyObject *self, PyObject *args, PyObject *kwds)
{
    const char *name;
    static char *kwlist[] = {"name", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &name))
        return NULL;

    GameObject *c_obj = CreateGameObject(name);

    ProxyGameObject *py_obj = (ProxyGameObject *)PyType_GenericNew(&ProxyGameObjectType, NULL, NULL);
    py_obj->c_obj = c_obj;

    return (PyObject *)py_obj;
}

PyObject *py_GetGameObject(PyObject *self, PyObject *args)
{
    const char *name;
    if (!PyArg_ParseTuple(args, "s", &name))
        return NULL;

    GameObject *c_obj = GetGameObject(name);
    if (!c_obj)
        Py_RETURN_NONE;

    ProxyGameObject *py_obj = (ProxyGameObject *)PyType_GenericNew(&ProxyGameObjectType, NULL, NULL);
    py_obj->c_obj = c_obj;

    return (PyObject *)py_obj;
}

PyMethodDef SceneMethods[] = {
    {"CreateGameObject", (PyCFunction)py_CreateGameObject, METH_VARARGS | METH_KEYWORDS, "Create a game object"},
    {"GetGameObject", py_GetGameObject, METH_VARARGS, "Get a game object by name"},
    {NULL, NULL, 0, NULL}};

PyModuleDef scene_module = {
    PyModuleDef_HEAD_INIT,
    "scene",
    NULL,
    -1,
    SceneMethods};

PyMODINIT_FUNC PyInit_scene(void)
{
    if (PyType_Ready(&ProxyGameObjectType) < 0)
        return NULL;

    PyObject *m = PyModule_Create(&scene_module);
    Py_INCREF(&ProxyGameObjectType);
    PyModule_AddObject(m, "GameObject", (PyObject *)&ProxyGameObjectType);

    return m;
}