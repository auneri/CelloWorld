#include <Python.h>  // include before standard headers

#include <stdio.h>
#include <stdlib.h>


static int ARGC = 0;


static PyObject* HelloPythonC_argc(PyObject *self, PyObject *args) {
  (void)self;
  if (!PyArg_ParseTuple(args, ":argc")) return NULL;
  return PyLong_FromLong(ARGC);
}


static PyMethodDef HelloPythonCMethods[] = {
  {"argc", HelloPythonC_argc, METH_VARARGS, "Return the number of arguments received by the process."},
  {NULL, NULL, 0, NULL}
};


static PyModuleDef HelloPythonCModule = {
  PyModuleDef_HEAD_INIT, "HelloPythonC", NULL, -1, HelloPythonCMethods, NULL, NULL, NULL, NULL
};


static PyObject* PyInit_HelloPythonC(void) {
  return PyModule_Create(&HelloPythonCModule);
}


int main(int argc, char *argv[]) {
  PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;
  int i;

  if (argc < 3) {
    fprintf(stderr, "Usage: HelloPythonC module_name function_name [args]\n");
    return EXIT_FAILURE;
  }
  ARGC = argc;

  PyImport_AppendInittab("HelloPythonC", &PyInit_HelloPythonC);
  Py_Initialize();
  pName = PyUnicode_DecodeFSDefault(argv[1]);  // error checking of pName left out

  pModule = PyImport_Import(pName);
  Py_DECREF(pName);

  if (pModule != NULL) {
    pFunc = PyObject_GetAttrString(pModule, argv[2]);  // pFunc is a new reference

    if (pFunc && PyCallable_Check(pFunc)) {
      pArgs = PyTuple_New(argc - 3);
      for (i = 0; i < argc - 3; ++i) {
        pValue = PyLong_FromLong(atoi(argv[i + 3]));
        if (!pValue) {
          Py_DECREF(pArgs);
          Py_DECREF(pModule);
          fprintf(stderr, "Cannot convert argument\n");
          return EXIT_FAILURE;
        }
        PyTuple_SetItem(pArgs, i, pValue);  // pValue reference stolen here
      }
      pValue = PyObject_CallObject(pFunc, pArgs);
      Py_DECREF(pArgs);
      if (pValue == Py_None) {
      } else if (pValue != NULL) {
        printf("Result: %ld\n", PyLong_AsLong(pValue));
        Py_DECREF(pValue);
      } else {
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyErr_Print();
        fprintf(stderr, "Call failed\n");
        return EXIT_FAILURE;
      }
    } else {
      if (PyErr_Occurred()) PyErr_Print();
      fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
    }
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
  } else {
    PyErr_Print();
    fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
    return EXIT_FAILURE;
  }

  Py_Finalize();
  return EXIT_SUCCESS;
}
