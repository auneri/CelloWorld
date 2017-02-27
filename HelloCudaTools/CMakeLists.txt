cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(HelloCudaTools)

find_package(CudaTools REQUIRED)

add_executable(${PROJECT_NAME}Executable
  main.cc)

target_link_libraries(${PROJECT_NAME}Executable
  ${CudaTools_LIBRARIES})
