#pragma once
#include <Python.h>
#include "game/game.h"
PyTypeObject PauseType;
PyTypeObject ResumeType;

PyObject *pause_call(PyObject *self, PyObject *args, PyObject *kwds);

PyObject *resume_call(PyObject *self, PyObject *args, PyObject *kwds);

PyMODINIT_FUNC PyInit_gamestate(void);