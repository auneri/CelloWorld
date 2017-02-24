cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

project(HelloCudaTools CXX)

find_package(CUDA REQUIRED)
find_package(CudaTools REQUIRED)

add_executable(${PROJECT_NAME}Executable
  main.cc)

target_link_libraries(${PROJECT_NAME}Executable
  ${CUDA_LIBRARIES}
  CudaTools)
