cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(HelloMPI C)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

add_executable(${PROJECT_NAME}Executable
  main.c)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Weverything -Wfatal-errors)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Wall -Wextra -Wfatal-errors)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  target_compile_options(${PROJECT_NAME}Executable PRIVATE /W4)
endif()

target_link_libraries(${PROJECT_NAME}Executable
  PRIVATE ${MPI_LIBRARIES})

if(MPI_COMPILE_FLAGS)
  set_target_properties(${PROJECT_NAME}Executable PROPERTIES COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
  set_target_properties(${PROJECT_NAME}Executable PROPERTIES LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()

include(CTest)
enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 4 ${MPIEXEC_PREFLAGS} $<TARGET_FILE:${PROJECT_NAME}Executable> ${MPIEXEC_POSTFLAGS})
