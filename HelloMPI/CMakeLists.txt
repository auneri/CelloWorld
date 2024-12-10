cmake_minimum_required(VERSION 3.15)

project(HelloMPI LANGUAGES C)

find_package(MPI REQUIRED COMPONENTS C)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE} main.c)

set_target_properties(${EXECUTABLE} PROPERTIES
  C_STANDARD 11
  C_STANDARD_REQUIRED ON
  C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wfatal-errors)
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU")
  target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wfatal-errors)
elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC")
  target_compile_options(${EXECUTABLE} PRIVATE /W4)
endif()

target_include_directories(${EXECUTABLE} PRIVATE ${MPI_C_INCLUDE_DIRS})

target_link_libraries(${EXECUTABLE} PRIVATE ${MPI_C_LIBRARIES})

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Test1
  COMMAND "${MPIEXEC}" --oversubscribe "${MPIEXEC_NUMPROC_FLAG}" 4 ${MPIEXEC_PREFLAGS} "$<TARGET_FILE:${EXECUTABLE}>" ${MPIEXEC_POSTFLAGS})
