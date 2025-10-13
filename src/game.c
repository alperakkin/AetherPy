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
    obj->position.x = 0.0f;
    obj->position.y = 0.0f;
    obj->position.z = 0.0f;

    obj->rotation.x = 0.0f;
    obj->rotation.y = 0.0f;
    obj->rotation.z = 0.0f;
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

static PyObject *PyVector3_getx(PyVector3 *self, void *closure)
{
    return PyFloat_FromDouble(self->c_vec->x);
}

static int PyVector3_setx(PyVector3 *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_vec->x = (float)v;
    return 0;
}

static PyObject *PyVector3_gety(PyVector3 *self, void *closure)
{
    return PyFloat_FromDouble(self->c_vec->y);
}

static int PyVector3_sety(PyVector3 *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_vec->y = (float)v;
    return 0;
}

static PyObject *PyVector3_getz(PyVector3 *self, void *closure)
{
    return PyFloat_FromDouble(self->c_vec->z);
}

static int PyVector3_setz(PyVector3 *self, PyObject *value, void *closure)
{
    double v = PyFloat_AsDouble(value);
    self->c_vec->z = (float)v;
    return 0;
}

static PyObject *PyVector3_repr(PyVector3 *self)
{
    if (!self->c_vec)
    {
        PyErr_SetString(PyExc_AttributeError, "Vector3 not assigned");
        return NULL;
    }
    char buf[128];
    snprintf(buf, sizeof(buf), "Vector3(x=%f, y=%f, z=%f)",
             (double)self->c_vec->x,
             (double)self->c_vec->y,
             (double)self->c_vec->z);

    return PyUnicode_FromFormat(buf);
}

static PyGetSetDef PyVector3_getset[] = {
    {"x", (getter)PyVector3_getx, (setter)PyVector3_setx, "x", NULL},
    {"y", (getter)PyVector3_gety, (setter)PyVector3_sety, "y", NULL},
    {"z", (getter)PyVector3_getz, (setter)PyVector3_setz, "z", NULL},
    {NULL}};

PyTypeObject PyVector3Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "game.Vector3",
    .tp_basicsize = sizeof(PyVector3),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_getset = PyVector3_getset,
    .tp_repr = (reprfunc)PyVector3_repr,
};

PyMemberDef PyGameObject_members[] = {
    {"name", T_STRING, offsetof(PyGameObject, name), 0, "Name"},
    {NULL}};

static PyObject *PyGameObject_get_position(PyGameObject *self, void *closure)
{
    if (!self->c_obj)
    {
        PyErr_SetString(PyExc_AttributeError, "GameObject Not Exists!");
        return NULL;
    }
    PyVector3 *vec = PyObject_New(PyVector3, &PyVector3Type);

    vec->c_vec = &self->c_obj->position;
    return (PyObject *)vec;
}

static PyObject *PyGameObject_get_rotation(PyGameObject *self, void *closure)
{
    PyVector3 *vec = PyObject_New(PyVector3, &PyVector3Type);

    vec->c_vec = &self->c_obj->rotation;
    return (PyObject *)vec;
}

static PyGetSetDef PyGameObject_getset[] = {
    {"position", (getter)PyGameObject_get_position, NULL, "Position", NULL},
    {"rotation", (getter)PyGameObject_get_rotation, NULL, "Rotation", NULL},
    {NULL}};

PyTypeObject PyGameObjectType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "game.GameObject",
    .tp_basicsize = sizeof(PyGameObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_members = PyGameObject_members,
    .tp_getset = PyGameObject_getset,
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
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &name))
        return NULL;

    GameObject *c_obj = createGameObjectC(name);

    PyGameObject *py_obj = (PyGameObject *)PyType_GenericNew(&PyGameObjectType, NULL, NULL);
    py_obj->name = strdup(name);
    py_obj->c_obj = c_obj;

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
    py_obj->c_obj = c_obj;

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
    if (PyType_Ready(&PyVector3Type) < 0)
        return NULL;

    PyObject *m = PyModule_Create(&game_module);
    Py_INCREF(&PyGameObjectType);
    PyModule_AddObject(m, "GameObject", (PyObject *)&PyGameObjectType);
    Py_INCREF(&PyVector3Type);
    PyModule_AddObject(m, "Vector3", (PyObject *)&PyVector3Type);

    return m;
}
