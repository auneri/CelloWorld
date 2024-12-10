cmake_minimum_required(VERSION 3.15)

project(HelloCUDA LANGUAGES CUDA)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE} main.cu)

set_target_properties(${EXECUTABLE} PROPERTIES
  CUDA_STANDARD 11
  CUDA_STANDARD_REQUIRED ON
  CUDA_ARCHITECTURES OFF)

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Test1
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>")
