#pragma once
#include <Python.h>

typedef struct
{
    PyObject *module;
    PyObject *setup_func;
    PyObject *update_func;
} Module;

void initialize_scripting_engine();
void finalize_scripting_engine();
Module *load_script(const char *name, const char *path);
void call_game_function(Module *instance, char *name);