
#include "scripting.h"
#include "game.h"

void initialize_scripting_engine()
{
    PyImport_AppendInittab("game", PyInit_game);
    Py_Initialize();
    PyRun_SimpleString("import sys\nsys.path.append('.')\nimport game\n");
}

void finalize_scripting_engine()
{
    Py_Finalize();
}

Module *load_script(const char *name, const char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp)
    {
        fprintf(stderr, "Could not open script: %s\n", path);
        return NULL;
    }

    Module *inst = malloc(sizeof(Module));

    inst->module = PyImport_AddModule(name);
    PyObject *globals = PyModule_GetDict(inst->module);

    PyRun_File(fp, path, Py_file_input, globals, globals);
    fclose(fp);

    inst->setup_func = PyObject_GetAttrString(inst->module, "setup");
    inst->update_func = PyObject_GetAttrString(inst->module, "update");

    return inst;
}

void call_game_function(Module *instance, char *name)
{
    PyObject *func = strcmp(name, "setup") == 0 ? instance->setup_func : instance->update_func;

    if (func && PyCallable_Check(func))
        PyObject_CallObject(func, NULL);
}