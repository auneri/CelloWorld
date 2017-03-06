#include <cstdlib>
#include <iostream>

#include <Python.h>


int main(int, char *argv[]) {
  wchar_t *program = Py_DecodeLocale(argv[0], NULL);
  if (program == NULL) {
    std::cerr << "Fatal error: cannot decode argv[0]" << std::endl;
    return EXIT_FAILURE;
  }
  Py_SetProgramName(program);
  Py_Initialize();
  PyRun_SimpleString("print('hello, world')\n");
  Py_Finalize();
  PyMem_RawFree(program);
  return EXIT_SUCCESS;
}
