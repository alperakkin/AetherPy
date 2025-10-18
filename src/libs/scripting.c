#include "libs/scripting.h"
#include "proxy/main_px.h"
#include "proxy/scene_px.h"
#include "proxy/transform_px.h"

void initialize_scripting_engine()
{
    int aether = PyImport_AppendInittab("Aether", PyInit_Aether);
    if (aether == -1)
    {
        fprintf(stderr, "Failed to add Aether to inittab\n");
        return;
    }

    Py_Initialize();
    PyRun_SimpleString("import sys\nsys.path.append('.')\n");

    PyObject *Aether_mod = PyImport_ImportModule("Aether");
    if (!Aether_mod)
    {
        PyErr_Print();
        fprintf(stderr, "Could not import Aether module\n");
        return;
    }

    PyObject *scene = PyObject_GetAttrString(Aether_mod, "scene");
    PyObject *transform = PyObject_GetAttrString(Aether_mod, "transform");

    if (!scene || !transform)
    {
        PyErr_Print();
        fprintf(stderr, "Modules could not be accessed\n");
        Py_XDECREF(Aether_mod);
        return;
    }

    Py_XDECREF(scene);
    Py_XDECREF(transform);
    Py_XDECREF(Aether_mod);
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
    if (!inst->module)
    {
        PyErr_Print();
        return NULL;
    }

    PyObject *globals = PyModule_GetDict(inst->module);

    PyRun_File(fp, path, Py_file_input, globals, globals);
    fclose(fp);
    inst->start_func = PyObject_GetAttrString(inst->module, "start");
    inst->setup_func = PyObject_GetAttrString(inst->module, "setup");
    inst->update_func = PyObject_GetAttrString(inst->module, "update");

    return inst;
}

void call_game_function(PyObject *func)
{
    if (func && PyCallable_Check(func))
    {
        PyObject_CallObject(func, NULL);
    }
}