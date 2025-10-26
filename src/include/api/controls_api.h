#pragma once
#include <stdio.h>
#include <Python.h>
#include "game/scene.h"
#include "game/controls.h"
#include "api/scene_api.h"

typedef struct
{
    PyObject_HEAD ControlProp *c_obj;

} apiControlProp;

PyMODINIT_FUNC PyInit_controls(void);
PyMODINIT_FUNC PyInit_inputs(void);