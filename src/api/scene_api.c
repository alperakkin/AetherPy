#include "api/scene_api.h"
#include "libs/utils.h"
PyTypeObject apiGameObjectType;
PyTypeObject apiVector3PropType;

PyMemberDef apiGameObject_members[] = {
    {"name", T_STRING, offsetof(GameObject, name), 0, "Name"},
    {NULL}};

PyObject *apiGameObject_get_position(apiGameObject *self, void *closure)
{
    if (!self->c_obj)
    {
        PyErr_SetString(PyExc_AttributeError, "GameObject Not Exists!");
        return NULL;
    }
    apiVector3Prop *vec = (apiVector3Prop *)PyType_GenericNew(&apiVector3PropType, NULL, NULL);

    vec->c_obj = &self->c_obj->position;

    return (PyObject *)vec;
}
int apiGameObject_set_position(apiGameObject *self, apiVector3Prop *value, void *closure)
{
    if (!PyObject_TypeCheck(value, &apiVector3PropType))
    {
        PyErr_SetString(PyExc_TypeError, "Expected Vector3Prop");
        return -1;
    }
    apiVector3Prop *vec = (apiVector3Prop *)value;

    self->c_obj->position.x = vec->c_obj->x;
    self->c_obj->position.y = vec->c_obj->y;
    self->c_obj->position.z = vec->c_obj->z;

    return 0;
}

PyObject *apiGameObject_get_rotation(apiGameObject *self, void *closure)
{
    apiVector3Prop *vec = PyObject_New(apiVector3Prop, &apiVector3PropType);
    vec->c_obj = PyMem_Malloc(sizeof(Vector3Prop));

    double x_rad = normalize_rad(self->c_obj->rotation.x);
    double y_rad = normalize_rad(self->c_obj->rotation.y);
    double z_rad = normalize_rad(self->c_obj->rotation.z);
    vec->c_obj->x = rad_to_deg(x_rad);
    vec->c_obj->y = rad_to_deg(y_rad);
    vec->c_obj->z = rad_to_deg(z_rad);
    return (PyObject *)vec;
}

int apiGameObject_set_rotation(apiGameObject *self, apiVector3Prop *value, void *closure)
{
    if (!PyObject_TypeCheck(value, &apiVector3PropType))
    {
        PyErr_SetString(PyExc_TypeError, "Expected Vector3Prop");
        return -1;
    }
    apiVector3Prop *vec = (apiVector3Prop *)value;

    double x_deg = normalize_deg(vec->c_obj->x);
    double y_deg = normalize_deg(vec->c_obj->y);
    double z_deg = normalize_deg(vec->c_obj->z);

    self->c_obj->rotation.x = deg_to_rad(x_deg);
    self->c_obj->rotation.y = deg_to_rad(y_deg);
    self->c_obj->rotation.z = deg_to_rad(z_deg);

    return 0;
}

PyObject *apiGameObject_get_shape(apiGameObject *self, void *closure)
{
    if (!self->c_obj)
    {
        PyErr_SetString(PyExc_AttributeError, "GameObject Not Exists!");
        return NULL;
    }
    apiShape *shape = (apiShape *)PyType_GenericNew(&apiShapeType, NULL, NULL);

    shape->c_obj = (Shape *)self->c_obj->shape;

    return (PyObject *)shape;
}
int apiGameObject_set_shape(apiGameObject *self, apiShape *value, void *closure)
{
    if (!PyObject_TypeCheck(value, &apiShapeType))
    {
        PyErr_SetString(PyExc_TypeError, "Expected Shape");
        return -1;
    }
    apiShape *shape = (apiShape *)value;

    self->c_obj->shape = shape->c_obj;

    return 0;
}

PyGetSetDef apiGameObject_getset[] = {
    {"position", (getter)apiGameObject_get_position, (setter)apiGameObject_set_position, "position", NULL},
    {"rotation", (getter)apiGameObject_get_rotation, (setter)apiGameObject_set_rotation, "rotation", NULL},
    {"shape", (getter)apiGameObject_get_shape, (setter)apiGameObject_set_shape, "shape", NULL},
    {NULL}};

PyTypeObject apiGameObjectType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "Aether.GameObject",
    .tp_basicsize = sizeof(apiGameObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_members = apiGameObject_members,
    .tp_getset = apiGameObject_getset,
    .tp_repr = apiGameObject_repr,
};

PyObject *apiGameObject_repr(PyObject *self)
{
    apiGameObject *obj = (apiGameObject *)self;
    return PyUnicode_FromFormat("GameObject(name='%s')", obj->c_obj->name);
}

PyObject *py_CreateGameObject(PyObject *self, PyObject *args, PyObject *kwds)
{
    const char *name;
    static char *kwlist[] = {"name", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &name))
        return NULL;

    GameObject *c_obj = CreateGameObject(name);

    apiGameObject *py_obj = (apiGameObject *)PyType_GenericNew(&apiGameObjectType, NULL, NULL);
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

    apiGameObject *py_obj = (apiGameObject *)PyType_GenericNew(&apiGameObjectType, NULL, NULL);
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
    if (PyType_Ready(&apiGameObjectType) < 0)
        return NULL;

    PyObject *m = PyModule_Create(&scene_module);
    Py_INCREF(&apiGameObjectType);
    PyModule_AddObject(m, "GameObject", (PyObject *)&apiGameObjectType);

    return m;
}