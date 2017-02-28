cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(HelloCUDA)

find_package(CUDA REQUIRED)

cuda_add_executable(${PROJECT_NAME}Executable
  main.cu)

target_link_libraries(${PROJECT_NAME}Executable
  ${CUDA_LIBRARIES})

include(CTest)
enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND $<TARGET_FILE:${PROJECT_NAME}Executable>)
