cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(HelloPythonCxx LANGUAGES CXX)

find_package(Python QUIET REQUIRED COMPONENTS Development Interpreter)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE} main.cxx)

target_compile_options(${EXECUTABLE} PUBLIC
  "$<$<CXX_COMPILER_ID:Clang>:-Weverything;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:MSVC>:/W4>")

target_include_directories(${EXECUTABLE} PRIVATE
  ${Python_INCLUDE_DIRS})

target_link_libraries(${EXECUTABLE} PRIVATE
  ${Python_LIBRARIES})

include(CTest)
enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>")

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  get_filename_component(PYTHONHOME ${Python_EXECUTABLE} DIRECTORY)
  set_tests_properties(${PROJECT_NAME}Tests PROPERTIES
    ENVIRONMENT "PYTHONHOME=${PYTHONHOME}")
endif()
