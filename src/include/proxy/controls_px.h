#pragma once
#include <stdio.h>
#include <Python.h>
#include "game/scene.h"
#include "game/controls.h"
#include "proxy/scene_px.h"

typedef struct
{
    PyObject_HEAD ControlProp *c_obj;

} ProxyControlProp;

PyMODINIT_FUNC PyInit_controls(void);
PyMODINIT_FUNC PyInit_inputs(void);