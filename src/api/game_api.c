#include "api/game_api.h"

static PyObject *pause_getter(PyObject *self, void *closure)
{
    if (game_state.paused)
        Py_RETURN_TRUE;
    else
        Py_RETURN_FALSE;
}

static int pause_setter(PyObject *self, PyObject *value, void *closure)
{
    printf("Value: %u\n", PyObject_IsTrue(value));
    game_state.paused = PyObject_IsTrue(value);
    return 0;
}

static PyGetSetDef pause_getset[] = {
    {"PAUSE", pause_getter, pause_setter, "PAUSE", NULL},
    {NULL}};

static PyType_Slot pause_slots[] = {
    {Py_tp_getset, pause_getset},
    {0, NULL}};

static PyType_Spec pause_spec = {
    "BuiltinPause",
    sizeof(PyObject),
    0,
    Py_TPFLAGS_DEFAULT,
    pause_slots};

void add_builtin_pause()
{
    PyObject *pause_type = PyType_FromSpec(&pause_spec);
    if (!pause_type)
        return;

    PyObject *builtins = PyEval_GetBuiltins();
    if (!builtins)
    {
        Py_DECREF(pause_type);
        return;
    }

    PyDict_SetItemString(builtins, "PAUSE", pause_type);
    Py_DECREF(pause_type);
}