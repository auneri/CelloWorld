cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(HelloPythonCpp CXX)

find_package(PythonInterp REQUIRED)
get_filename_component(PYTHONHOME "${PYTHON_EXECUTABLE}" DIRECTORY)
if(UNIX)
  get_filename_component(PYTHONHOME "${PYTHONHOME}" DIRECTORY)
endif()

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
