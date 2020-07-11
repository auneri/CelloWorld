cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(HelloPythonCXX LANGUAGES CXX)

set(Python_FIND_FRAMEWORK LAST)
set(Python_FIND_VIRTUALENV ONLY)
find_package(Python REQUIRED COMPONENTS Development Interpreter)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE}
  main.cxx)

target_compile_options(${EXECUTABLE} PUBLIC
  "$<$<CXX_COMPILER_ID:Clang>:-Weverything;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:MSVC>:/W4>")

target_include_directories(${EXECUTABLE} PRIVATE
  ${Python_INCLUDE_DIRS})

target_link_libraries(${EXECUTABLE} PRIVATE
  ${Python_LIBRARIES})

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>")

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  get_filename_component(PYTHONHOME ${Python_EXECUTABLE} DIRECTORY)
  set_tests_properties(${PROJECT_NAME}Tests PROPERTIES
    ENVIRONMENT "PYTHONHOME=${PYTHONHOME}")
endif()
