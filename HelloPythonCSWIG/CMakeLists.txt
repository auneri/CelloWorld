cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
if(POLICY CMP0078)  # introduced in CMake v3.13
  cmake_policy(SET CMP0078 NEW)
endif()
if(POLICY CMP0086)  # introduced in CMake v3.14
  cmake_policy(SET CMP0086 NEW)
endif()

project(HelloPythonCSWIG LANGUAGES C)

set(Python_FIND_FRAMEWORK LAST)
set(Python_FIND_VIRTUALENV ONLY)
find_package(Python REQUIRED COMPONENTS Development Interpreter)

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

set_source_files_properties(library.i PROPERTIES
  SWIG_FLAGS "-builtin;-py3")
swig_add_library(${MODULE}
  LANGUAGE python
  SOURCES library.i)

target_include_directories(${MODULE} PRIVATE
  ${PROJECT_SOURCE_DIR}
  ${Python_INCLUDE_DIRS})

target_link_libraries(${MODULE} PRIVATE
  ${LIBRARY})

if(APPLE)
  set_target_properties(${MODULE} PROPERTIES
    LINK_FLAGS "-undefined dynamic_lookup")
else()
  target_link_libraries(${MODULE} PRIVATE
    ${Python_LIBRARIES})
endif()

configure_file(
  tests.py
  ${PROJECT_BINARY_DIR}/${MODULE}Tests.py
  COPYONLY)

add_custom_command(
  TARGET ${MODULE}
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:${MODULE}>" "Python/$<TARGET_FILE_NAME:${MODULE}>"
  COMMAND "${CMAKE_COMMAND}" -E copy "${MODULE}.py" "Python/${MODULE}.py"
  COMMAND "${CMAKE_COMMAND}" -E copy "${MODULE}Tests.py" "Python/${MODULE}Tests.py"
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND "${Python_EXECUTABLE}" -m "${MODULE}Tests"
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Python)
