#include "libs/scripting.h"
#include "api/main_api.h"
#include "api/scene_api.h"
#include "api/transform_api.h"

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
    PyObject *graphics = PyObject_GetAttrString(Aether_mod, "graphics");

    if (!scene || !transform || !graphics)
    {
        PyErr_Print();
        fprintf(stderr, "Modules could not be accessed\n");
        Py_XDECREF(Aether_mod);
        return;
    }

    Py_XDECREF(scene);
    Py_XDECREF(transform);
    Py_XDECREF(graphics);
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

    PyObject *result = PyRun_File(fp, path, Py_file_input, globals, globals);
    if (!result)
    {
        if (PyErr_Occurred())
        {
            PyErr_Print();
            PyErr_Clear();
        }
    }
    fclose(fp);
    inst->start_func = PyObject_GetAttrString(inst->module, "start");
    if (!inst->start_func)
        PyErr_Clear();
    inst->setup_func = PyObject_GetAttrString(inst->module, "setup");
    if (!inst->setup_func)
        PyErr_Clear();
    inst->update_func = PyObject_GetAttrString(inst->module, "update");
    if (!inst->update_func)
        PyErr_Clear();

    return inst;
}

void call_game_function(PyObject *func)
{
    if (func && PyCallable_Check(func))
    {
        PyObject_CallObject(func, NULL);
    }
}