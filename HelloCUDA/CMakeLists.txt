cmake_minimum_required(VERSION 3.15)

project(HelloCUDA LANGUAGES CUDA)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE} main.cu)

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>")
