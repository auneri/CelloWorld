cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

project(HelloMPI C)

find_package(MPI REQUIRED)

add_executable(${PROJECT_NAME}Executable
  main.c)

target_link_libraries(${PROJECT_NAME}Executable
  ${MPI_LIBRARIES})

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Weverything -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Wall -Wextra -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${PROJECT_NAME}Executable PRIVATE /Wall)
endif()

include(CTest)
enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND ${MPIEXEC} -n 4 $<TARGET_FILE:${PROJECT_NAME}Executable>)
