#include <Python.h>  // include before standard headers

#include <cstdlib>
#include <iostream>


int main(int, char *argv[]) {

  wchar_t *program = Py_DecodeLocale(argv[0], NULL);
  if (program == NULL) {
    std::cerr << "Py_DecodeLocale failed" << std::endl;
    return EXIT_FAILURE;
  }

  PyStatus status;
  PyConfig config;
  PyConfig_InitPythonConfig(&config);

  status = PyConfig_SetString(&config, &config.program_name, program);
  if (PyStatus_Exception(status)) {
    PyConfig_Clear(&config);
    PyMem_RawFree(program);
    std::cerr << "PyConfig_SetString failed" << std::endl;
    return EXIT_FAILURE;
  }

  status = Py_InitializeFromConfig(&config);
  PyConfig_Clear(&config);
  if (PyStatus_Exception(status)) {
    std::cerr << "Py_InitializeFromConfig failed" << std::endl;
    PyMem_RawFree(program);
    return EXIT_FAILURE;
  }

  PyRun_SimpleString("print('hello, world')\n");

  if (Py_FinalizeEx() < 0) {
    std::cerr << "Py_FinalizeEx failed" << std::endl;
    return EXIT_FAILURE;
  }

  PyMem_RawFree(program);

  return EXIT_SUCCESS;
}
