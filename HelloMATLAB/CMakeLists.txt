cmake_minimum_required(VERSION 3.15)

project(HelloMATLAB LANGUAGES CXX)

set(LIBRARY ${PROJECT_NAME}Library)

add_library(${LIBRARY} SHARED library.cxx)

set_target_properties(${LIBRARY} PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(${LIBRARY} PRIVATE -Wall -Wextra -Wpedantic -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(${LIBRARY} PRIVATE -Wall -Wextra -Wpedantic -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(${LIBRARY} PRIVATE /W4)
endif()

configure_file(
  tests.m
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Tests.m
  @ONLY)

add_custom_command(
  TARGET ${LIBRARY}
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:${LIBRARY}>" "MATLAB/$<TARGET_FILE_NAME:${LIBRARY}>"
  COMMAND "${CMAKE_COMMAND}" -E copy "${PROJECT_NAME}Tests.m" "MATLAB/${PROJECT_NAME}Tests.m"
  COMMAND "${CMAKE_COMMAND}" -E copy "${PROJECT_SOURCE_DIR}/library.h" "MATLAB/${LIBRARY}.h"
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

find_program(MATLAB_EXECUTABLE matlab)
if(MATLAB_EXECUTABLE)
  set(SCRIPT
    "addpath('${PROJECT_BINARY_DIR}/MATLAB')"
    "try; run('${PROJECT_BINARY_DIR}/MATLAB/${PROJECT_NAME}Tests.m')"
    "catch err; fprintf(2, '%s\\n', getReport(err, 'extended')); exit(1)"
    "end; exit(0)")

  enable_testing()
  if(UNIX)
    add_test(
      NAME ${PROJECT_NAME}Test1
      COMMAND "${MATLAB_EXECUTABLE}" -nojvm -nodesktop -nosplash -r "${SCRIPT}")
  elseif(WIN32)
    add_test(
      NAME ${PROJECT_NAME}Test1
      COMMAND "${MATLAB_EXECUTABLE}" -nojvm -automation -wait -r "${SCRIPT}")
  else()
    message(FATAL_ERROR "Platform is not supported")
  endif()
else()
  message(WARNING "MATLAB_EXECUTABLE needs to be defined to run the tests")
endif()
