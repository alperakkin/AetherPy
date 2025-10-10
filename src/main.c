#include <Python.h>
#include <stdio.h>

PyMODINIT_FUNC PyInit_engine(void);

int main()
{
    PyImport_AppendInittab("engine", PyInit_engine);
    Py_Initialize();

    PyRun_SimpleString("import sys\nsys.path.append('.')\nimport engine\n");

    FILE *fp = fopen("player.py", "r");
    if (!fp)
    {
        printf("Cannot open player.py\n");
        return 1;
    }
    PyRun_SimpleFile(fp, "player.py");
    fclose(fp);

    PyObject *mainModule = PyImport_AddModule("__main__");
    PyObject *func = PyObject_GetAttrString(mainModule, "setup");
    if (func && PyCallable_Check(func))
        PyObject_CallObject(func, NULL);

    func = PyObject_GetAttrString(mainModule, "update");
    if (func && PyCallable_Check(func))
        PyObject_CallObject(func, NULL);

    Py_Finalize();
    return 0;
}
