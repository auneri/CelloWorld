cmake_minimum_required(VERSION 3.15)

project(HelloFortran LANGUAGES Fortran)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE} main.f)

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Test1
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>")
