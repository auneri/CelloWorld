cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

project(HelloMATLAB)

add_library(${PROJECT_NAME}Library SHARED
  library.cxx)
add_custom_command(
  TARGET ${PROJECT_NAME}Library POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}Library> ${PROJECT_BINARY_DIR}/MATLAB/$<TARGET_FILE_NAME:${PROJECT_NAME}Library>)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(${PROJECT_NAME}Library PRIVATE -Weverything -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME}Library PRIVATE -Wall -Wextra -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${PROJECT_NAME}Library PRIVATE /Wall)
endif()

configure_file(
  library.h
  ${PROJECT_BINARY_DIR}/MATLAB/${PROJECT_NAME}Library.h
  @ONLY)

find_program(MATLAB_EXECUTABLE matlab)
if(MATLAB_EXECUTABLE)
  include(CTest)
  enable_testing()

  configure_file(
    tests.m
    ${PROJECT_BINARY_DIR}/MATLAB/${PROJECT_NAME}Tests.m
    @ONLY)

  if(UNIX)
    set(MATLAB_EXE "${MATLAB_EXECUTABLE}" -nojvm -nodesktop -nosplash)
  elseif(WIN32)
    set(MATLAB_EXE "${MATLAB_EXECUTABLE}" -nojvm -automation -wait)
  else()
    message(FATAL_ERROR "Platform is not supported")
  endif()
  set(SCRIPT
    "addpath('${PROJECT_BINARY_DIR}/MATLAB')"
    "try; run('${PROJECT_BINARY_DIR}/MATLAB/${PROJECT_NAME}Tests.m')"
    "catch err; fprintf(2, '%s\\n', getReport(err, 'extended')); exit(1)"
    "end; exit(0)")
  add_test(
    NAME ${PROJECT_NAME}Tests
    COMMAND ${MATLAB_EXE} -r "${SCRIPT}")
else()
  message(WARNING "MATLAB_EXECUTABLE needs to be defined to run the tests")
endif()
