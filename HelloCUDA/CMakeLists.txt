cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(HelloCUDA LANGUAGES CUDA)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE}
  main.cu)

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>")
