cmake_minimum_required(VERSION 3.15)

project(HelloPythonC LANGUAGES C)

set(Python_FIND_FRAMEWORK LAST)
set(Python_FIND_VIRTUALENV ONLY)
find_package(Python REQUIRED COMPONENTS Development Interpreter)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE} main.c)

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wextra -Wpedantic -Wfatal-errors)
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU")
  target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wextra -Wpedantic -Wfatal-errors)
elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC")
  target_compile_options(${EXECUTABLE} PRIVATE /W3)
endif()

target_include_directories(${EXECUTABLE} PRIVATE ${Python_INCLUDE_DIRS})

target_link_libraries(${EXECUTABLE} PRIVATE ${Python_LIBRARIES})

configure_file(
  tests.py
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Tests.py
  COPYONLY)

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Test1
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>" "${PROJECT_NAME}Tests" argc)

if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
  get_filename_component(PYTHONHOME ${Python_EXECUTABLE} DIRECTORY)
  set_tests_properties(${PROJECT_NAME}Test1 PROPERTIES
    ENVIRONMENT "PYTHONHOME=${PYTHONHOME};PYTHONPATH=${PROJECT_BINARY_DIR}")
else()
  set_tests_properties(${PROJECT_NAME}Test1 PROPERTIES
    ENVIRONMENT "PYTHONPATH=${PROJECT_BINARY_DIR}")
endif()
