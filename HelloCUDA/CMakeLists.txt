cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(HelloCUDA LANGUAGES CUDA)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE} main.cu)

include(CTest)
enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>")
