#include "scripting.h"

void initialize_scripting_engine()
{
    PyImport_AppendInittab("Aether", PyInit_Aether);
    Py_Initialize();
    PyRun_SimpleString("import sys\nsys.path.append('.')\nimport Aether\n");
}

void finalize_scripting_engine()
{
    Py_Finalize();
}

Module *load_script(char *name, char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp)
    {
        fprintf(stderr, "Could not open script: %s\n", path);
        return NULL;
    }

    Module *inst = malloc(sizeof(Module));

    inst->module = PyImport_AddModule(name);
    inst->name = strdup(name);

    PyObject *globals = PyModule_GetDict(inst->module);

    PyRun_File(fp, path, Py_file_input, globals, globals);
    fclose(fp);

    inst->start_func = PyObject_GetAttrString(inst->module, "start");
    if (!inst->start_func)
    {
        PyErr_Clear();
        inst->start_func = NULL;
    }
    inst->setup_func = PyObject_GetAttrString(inst->module, "setup");
    if (!inst->setup_func)
    {
        PyErr_Clear();
        inst->setup_func = NULL;
    }
    inst->update_func = PyObject_GetAttrString(inst->module, "update");
    if (!inst->update_func)
    {
        PyErr_Clear();
        inst->update_func = NULL;
    }
    return inst;
}

void call_game_function(Module *instance, char *name)
{
    PyObject *func = NULL;
    if (strcmp(name, "start") == 0)
        func = instance->start_func;
    else if (strcmp(name, "setup") == 0)
        func = instance->setup_func;
    else if (strcmp(name, "update") == 0)
        func = instance->update_func;

    if (func && PyCallable_Check(func))
    {
        PyObject_CallObject(func, NULL);
    }
}