#include "api/game_api.h"

PyObject *pause_call(PyObject *self, PyObject *args, PyObject *kwds)
{

    game_state.paused = true;
    Py_RETURN_NONE;
}

PyObject *resume_call(PyObject *self, PyObject *args, PyObject *kwds)
{
    game_state.paused = false;
    Py_RETURN_NONE;
}

PyTypeObject PauseType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "gamestate.PAUSE",
    .tp_basicsize = sizeof(PyObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_call = (ternaryfunc)pause_call,

};
PyTypeObject ResumeType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "gamestate.RESUME",
    .tp_basicsize = sizeof(PyObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_call = (ternaryfunc)pause_call,

};

PyMethodDef gamestate_methods[] = {
    {"PAUSE", (PyCFunction)pause_call, METH_VARARGS | METH_KEYWORDS, "PAUSE GAME"},
    {"RESUME", (PyCFunction)resume_call, METH_VARARGS | METH_KEYWORDS, "RESUME GAME"},
    {NULL, NULL, 0, NULL}};

PyModuleDef gamestate_module = {
    PyModuleDef_HEAD_INIT,
    "gamestate",
    NULL,
    -1,
    gamestate_methods};

PyMODINIT_FUNC PyInit_gamestate(void)
{
    if (PyType_Ready(&PauseType) < 0)
        return NULL;
    if (PyType_Ready(&ResumeType) < 0)
        return NULL;

    PyObject *m = PyModule_Create(&gamestate_module);
    Py_INCREF(&PauseType);
    Py_INCREF(&ResumeType);
    PyModule_AddObject(m, "PauseModule", (PyObject *)&PauseType);
    PyModule_AddObject(m, "ResumeModule", (PyObject *)&ResumeType);
    return m;
}
