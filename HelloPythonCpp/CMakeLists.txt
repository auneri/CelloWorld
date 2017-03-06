cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(HelloPythonCpp)

find_package(PythonInterp REQUIRED)
get_filename_component(PYTHON_BIN_DIR "${PYTHON_EXECUTABLE}" DIRECTORY)
get_filename_component(PYTHONHOME "${PYTHON_BIN_DIR}" DIRECTORY)

find_package(PythonLibs ${PYTHON_VERSION_STRING} EXACT REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}Executable
  main.cc)

target_link_libraries(${PROJECT_NAME}Executable
  ${PYTHON_LIBRARIES})

include(CTest)
enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND $<TARGET_FILE:${PROJECT_NAME}Executable>)
set_property(
  TEST ${PROJECT_NAME}Tests
  PROPERTY ENVIRONMENT PYTHONHOME=${PYTHONHOME})
