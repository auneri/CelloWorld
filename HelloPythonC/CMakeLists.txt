cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(HelloPythonC LANGUAGES C)

find_package(Python QUIET REQUIRED COMPONENTS Development Interpreter)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE}
  main.c)

target_compile_options(${EXECUTABLE} PUBLIC
  "$<$<C_COMPILER_ID:Clang>:-Weverything;-Wfatal-errors>"
  "$<$<C_COMPILER_ID:GNU>:-Wall;-Wextra;-Wfatal-errors>"
  "$<$<C_COMPILER_ID:MSVC>:/W3>")

target_include_directories(${EXECUTABLE} PRIVATE
  ${Python_INCLUDE_DIRS})

target_link_libraries(${EXECUTABLE} PRIVATE
  ${Python_LIBRARIES})

configure_file(
  tests.py
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Tests.py
  COPYONLY)

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>" "${PROJECT_NAME}Tests" argc)

if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
  get_filename_component(PYTHONHOME ${Python_EXECUTABLE} DIRECTORY)
  set_tests_properties(${PROJECT_NAME}Tests PROPERTIES
    ENVIRONMENT "PYTHONHOME=${PYTHONHOME};PYTHONPATH=${PROJECT_BINARY_DIR}")
else()
  set_tests_properties(${PROJECT_NAME}Tests PROPERTIES
    ENVIRONMENT "PYTHONPATH=${PROJECT_BINARY_DIR}")
endif()
