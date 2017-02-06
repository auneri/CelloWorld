cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

project(HelloFortran LANGUAGES Fortran)

add_executable(${PROJECT_NAME}Executable
  main.f)

if(CMAKE_Fortran_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Wall -Wextra -Wpedantic -Wfatal-errors)
endif()
