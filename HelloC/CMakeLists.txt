cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(HelloC LANGUAGES C)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE} main.c)

set_target_properties(${EXECUTABLE} PROPERTIES
  C_STANDARD 11
  C_STANDARD_REQUIRED ON
  C_EXTENSIONS OFF)

target_compile_options(${EXECUTABLE} PUBLIC
  "$<$<CXX_COMPILER_ID:Clang>:-Weverything;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:MSVC>:/W4>")

include(CTest)
enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>")
