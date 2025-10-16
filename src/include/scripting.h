#pragma once
#include "proxy.h"

typedef struct
{
    PyObject *module;
    PyObject *start_func;
    PyObject *setup_func;
    PyObject *update_func;
    char *name;
} Module;

void initialize_scripting_engine();
void finalize_scripting_engine();
Module *load_script(char *name, char *path);
void call_game_function(Module *instance, char *name);