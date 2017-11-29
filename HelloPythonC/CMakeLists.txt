cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(HelloPythonC C)

find_package(PythonInterp REQUIRED)

find_package(PythonLibs ${PYTHON_VERSION_STRING} EXACT REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}Executable
  main.c)

target_link_libraries(${PROJECT_NAME}Executable
  ${PYTHON_LIBRARIES})

configure_file(
  tests.py
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Tests.py
  @ONLY)

include(CTest)
enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND $<TARGET_FILE:${PROJECT_NAME}Executable> ${PROJECT_NAME}Tests argc)
set_property(
  TEST ${PROJECT_NAME}Tests
  APPEND
  PROPERTY ENVIRONMENT PYTHONPATH=${PROJECT_BINARY_DIR})
