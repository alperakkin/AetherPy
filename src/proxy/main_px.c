#include "main_px.h"

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

    PyObject *scene_mod = PyInit_scene();
    PyObject *transform_mod = PyInit_transform();

    PyModule_AddObject(m, "scene", scene_mod);
    PyModule_AddObject(m, "transform", transform_mod);

    PyObject *sys_modules = PyImport_GetModuleDict();
    PyDict_SetItemString(sys_modules, "Aether.scene", scene_mod);
    PyDict_SetItemString(sys_modules, "Aether.transform", transform_mod);

    return m;
}