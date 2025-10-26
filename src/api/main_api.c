#include "api/main_api.h"

PyModuleDef aether_module = {
    PyModuleDef_HEAD_INIT,
    "Aether",
    NULL,
    -1,
    NULL};

PyMODINIT_FUNC PyInit_Aether(void)
{

    PyObject *m = PyModule_Create(&aether_module);
    if (!m)
        return NULL;

    PyModule_AddObject(m, "__path__", PyList_New(0));

    // Modules
    PyObject *scene_mod = PyInit_scene();
    PyObject *transform_mod = PyInit_transform();
    PyObject *graphics_mod = PyInit_graphics();
    PyObject *controls_mod = PyInit_controls();
    PyObject *inputs_mod = PyInit_inputs();

    // Builtins
    void add_builtin_pause();

    // Add Modules
    PyModule_AddObject(m, "scene", scene_mod);
    PyModule_AddObject(m, "transform", transform_mod);
    PyModule_AddObject(m, "graphics", graphics_mod);
    PyModule_AddObject(m, "controls", controls_mod);
    PyModule_AddObject(m, "inputs", controls_mod);

    // Define Modules
    PyObject *sys_modules = PyImport_GetModuleDict();
    PyDict_SetItemString(sys_modules, "Aether.scene", scene_mod);
    PyDict_SetItemString(sys_modules, "Aether.transform", transform_mod);
    PyDict_SetItemString(sys_modules, "Aether.graphics", graphics_mod);
    PyDict_SetItemString(sys_modules, "Aether.controls", controls_mod);
    PyDict_SetItemString(sys_modules, "Aether.controls.inputs", inputs_mod);

    return m;
}