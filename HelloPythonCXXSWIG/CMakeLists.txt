cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
if(POLICY CMP0086)  # introduced in CMake v3.14
  cmake_policy(SET CMP0086 NEW)
endif()

project(HelloPythonCXXSWIG LANGUAGES CXX)

set(Python_FIND_FRAMEWORK LAST)
set(Python_FIND_VIRTUALENV ONLY)
find_package(Python REQUIRED COMPONENTS Development Interpreter)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

set(LIBRARY ${PROJECT_NAME}Library)
set(MODULE ${PROJECT_NAME})

add_library(${LIBRARY}
  library.cxx)

set_target_properties(${LIBRARY} PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF)

target_compile_options(${LIBRARY} PUBLIC
  "$<$<CXX_COMPILER_ID:Clang>:-Weverything;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:MSVC>:/W3>")

set_source_files_properties(library.i PROPERTIES
  CPLUSPLUS ON
  SWIG_FLAGS "-builtin;-py3")
swig_add_library(${MODULE}
  LANGUAGE python
  SOURCES library.i)
set(MODULE_REAL ${SWIG_MODULE_${MODULE}_REAL_NAME})

target_include_directories(${MODULE_REAL} PRIVATE
  ${PROJECT_SOURCE_DIR}
  ${Python_INCLUDE_DIRS})

target_link_libraries(${MODULE_REAL} PRIVATE
  ${LIBRARY}
  ${Python_LIBRARIES})

configure_file(
  tests.py
  ${PROJECT_BINARY_DIR}/Python/${MODULE}Tests.py
  COPYONLY)

add_custom_command(
  TARGET ${MODULE_REAL}
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:${MODULE_REAL}>" "Python/$<TARGET_FILE_NAME:${MODULE_REAL}>"
  COMMAND "${CMAKE_COMMAND}" -E copy "${MODULE}.py" "Python/${MODULE}.py"
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND "${Python_EXECUTABLE}" -m "${MODULE}Tests"
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Python)
