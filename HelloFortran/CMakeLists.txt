cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(HelloFortran LANGUAGES Fortran)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE}
  main.f)

target_compile_options(${EXECUTABLE} PUBLIC
  "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wpedantic;-Wfatal-errors>")

include(CTest)
enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>")
