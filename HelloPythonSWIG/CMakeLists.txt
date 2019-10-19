cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
if(POLICY CMP0078)  # introduced in CMake v3.13
  cmake_policy(SET CMP0078 NEW)
endif()
if(POLICY CMP0086)  # introduced in CMake v3.14
  cmake_policy(SET CMP0086 NEW)
endif()

project(HelloPythonSWIG LANGUAGES C)

find_package(Python QUIET REQUIRED COMPONENTS Development)
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

set(LIBRARY ${PROJECT_NAME}Library)
set(MODULE ${PROJECT_NAME})

add_library(${LIBRARY}
  library.c)

set_target_properties(${LIBRARY} PROPERTIES
  C_STANDARD 11
  C_STANDARD_REQUIRED ON
  C_EXTENSIONS OFF)

target_compile_options(${LIBRARY} PUBLIC
  "$<$<C_COMPILER_ID:Clang>:-Weverything;-Wfatal-errors>"
  "$<$<C_COMPILER_ID:GNU>:-Wall;-Wextra;-Wfatal-errors>"
  "$<$<C_COMPILER_ID:MSVC>:/W3>")

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

add_custom_command(
  TARGET ${MODULE_REAL}
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:${MODULE_REAL}>" "Python/$<TARGET_FILE_NAME:${MODULE_REAL}>"
  COMMAND "${CMAKE_COMMAND}" -E copy "${MODULE}.py" "Python/${MODULE}.py"
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

find_package(Python QUIET COMPONENTS Interpreter)
if(Python_EXECUTABLE)
  configure_file(
    tests.py
    ${PROJECT_BINARY_DIR}/Python/${MODULE}Tests.py
    COPYONLY)

  enable_testing()
  add_test(
    NAME ${PROJECT_NAME}Tests
    COMMAND "${Python_EXECUTABLE}" -m "${MODULE}Tests"
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Python)
else()
  message(WARNING "Python_EXECUTABLE needs to be defined to run the tests")
endif()
