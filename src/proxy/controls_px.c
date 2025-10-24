#include "proxy/controls_px.h"
PyTypeObject ProxyControlPropType;

PyObject *ProxyControlProp_repr(ProxyControlProp *self)
{
    ControlProp *obj = (ControlProp *)self->c_obj;
    if (!obj)
    {
        PyErr_SetString(PyExc_AttributeError, "Control Prop not assigned");
        return NULL;
    }
    char buf[128];
    snprintf(buf, sizeof(buf), "InputControl(object=%s)",
             obj->object->name);

    return PyUnicode_FromFormat(buf);
}

PyTypeObject ProxyControlPropType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "Aether.control",
    .tp_basicsize = sizeof(ProxyControlProp),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_repr = (reprfunc)ProxyControlProp_repr,

};

PyObject *py_createControl(PyObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *py_object = NULL;
    PyObject *py_ctrl_dict = NULL;

    static char *kwlist[] = {"object", "ctrl", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &py_object, &py_ctrl_dict))
        return NULL;

    if (!PyObject_TypeCheck(py_object, &ProxyGameObjectType))
    {
        PyErr_SetString(PyExc_TypeError, "object must be a GameObject");
        return NULL;
    }

    GameObject *c_obj = ((ProxyGameObject *)py_object)->c_obj;

    PyObject *keys = PyDict_Keys(py_ctrl_dict);
    Py_ssize_t count = PyList_Size(keys);

    ControlBinding *bindings = malloc(sizeof(ControlBinding) * count);

    for (Py_ssize_t i = 0; i < count; i++)
    {
        PyObject *py_key = PyList_GetItem(keys, i);
        PyObject *py_val = PyDict_GetItem(py_ctrl_dict, py_key);

        const char *key_str = PyUnicode_AsUTF8(py_key);
        bindings[i].key = key_str[0];

        PyObject *py_on = PyDict_GetItemString(py_val, "on");
        PyObject *py_delta = PyDict_GetItemString(py_val, "delta");

        bindings[i].property = (PropertyType)PyLong_AsLong(py_on);
        bindings[i].delta = (float)PyFloat_AsDouble(py_delta);
    }

    Py_DECREF(keys);

    ControlProp *c_ctrl = CreateControl(c_obj, bindings, (int)count);

    free(bindings);

    ProxyControlProp *py_ctrl = (ProxyControlProp *)PyType_GenericNew(&ProxyControlPropType, NULL, NULL);
    py_ctrl->c_obj = c_ctrl;

    return (PyObject *)py_ctrl;
}

PyMethodDef ControlMethods[] = {
    {"InputControl", (PyCFunction)py_createControl, METH_VARARGS | METH_KEYWORDS, "Create Input Control Object"},
    {NULL, NULL, 0, NULL}};

PyModuleDef controls_module = {
    PyModuleDef_HEAD_INIT,
    "controls",
    NULL,
    -1,
    ControlMethods};

PyMODINIT_FUNC PyInit_controls(void)
{
    if (PyType_Ready(&ProxyControlPropType) < 0)
        return NULL;

    PyObject *m = PyModule_Create(&controls_module);
    Py_INCREF(&ProxyControlPropType);
    PyModule_AddIntConstant(m, "POS_X", POS_X);
    PyModule_AddIntConstant(m, "POS_Y", POS_Y);
    PyModule_AddIntConstant(m, "ROT_X", ROT_X);
    PyModule_AddIntConstant(m, "ROT_Y", ROT_Y);
    PyModule_AddIntConstant(m, "SIZE_X", SIZE_X);
    PyModule_AddIntConstant(m, "SIZE_Y", SIZE_Y);
    PyModule_AddObject(m, "InputControlProp", (PyObject *)&ProxyControlPropType);
    return m;
}