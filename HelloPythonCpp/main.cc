#include <Python.h>  // include before standard headers

#include <cstdlib>
#include <iostream>


int main(int, char *argv[]) {

#if PY_MAJOR_VERSION >= 3
  wchar_t *program = Py_DecodeLocale(argv[0], NULL);
  if (program == NULL) {
    std::cerr << "Py_DecodeLocale failed" << std::endl;
    return EXIT_FAILURE;
  }
#else
  char *program = argv[0];
#endif

  Py_SetProgramName(program);
  Py_Initialize();
  PyRun_SimpleString("print('hello, world')\n");

#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 6
  if (Py_FinalizeEx() < 0) {
    std::cerr << "Py_FinalizeEx failed" << std::endl;
    return EXIT_FAILURE;
  }
#else
  Py_Finalize();
#endif

#if PY_MAJOR_VERSION >= 3
  PyMem_RawFree(program);
#endif

  return EXIT_SUCCESS;
}
