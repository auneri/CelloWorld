cmake_minimum_required(VERSION 3.15)

project(HelloMPI LANGUAGES C)

find_package(MPI REQUIRED COMPONENTS C)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE}
  main.c)

target_compile_options(${EXECUTABLE} PRIVATE
  "$<$<CXX_COMPILER_ID:Clang>:-Weverything;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:MSVC>:/W4>")

target_include_directories(${EXECUTABLE} PRIVATE
  ${MPI_C_INCLUDE_DIRS})

target_link_libraries(${EXECUTABLE} PRIVATE
  ${MPI_C_LIBRARIES})

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND "${MPIEXEC}" --oversubscribe "${MPIEXEC_NUMPROC_FLAG}" 4 ${MPIEXEC_PREFLAGS} "$<TARGET_FILE:${EXECUTABLE}>" ${MPIEXEC_POSTFLAGS})
