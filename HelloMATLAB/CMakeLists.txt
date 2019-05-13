cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(HelloMATLAB LANGUAGES C)

set(LIBRARY ${PROJECT_NAME}Library)

add_library(${LIBRARY} SHARED library.cxx)

target_compile_options(${LIBRARY} PUBLIC
  "$<$<CXX_COMPILER_ID:Clang>:-Weverything;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:MSVC>:/Wall>")

add_custom_command(
  TARGET ${LIBRARY} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${LIBRARY}> ${PROJECT_BINARY_DIR}/MATLAB/$<TARGET_FILE_NAME:${LIBRARY}>)

configure_file(
  library.h
  ${PROJECT_BINARY_DIR}/MATLAB/${LIBRARY}.h
  @ONLY)

find_program(MATLAB_EXECUTABLE matlab)
if(MATLAB_EXECUTABLE)
  configure_file(
    tests.m
    ${PROJECT_BINARY_DIR}/MATLAB/${PROJECT_NAME}Tests.m
    @ONLY)
  set(SCRIPT
    "addpath('${PROJECT_BINARY_DIR}/MATLAB')"
    "try; run('${PROJECT_BINARY_DIR}/MATLAB/${PROJECT_NAME}Tests.m')"
    "catch err; fprintf(2, '%s\\n', getReport(err, 'extended')); exit(1)"
    "end; exit(0)")

  include(CTest)
  enable_testing()
  if(UNIX)
    add_test(
      NAME ${PROJECT_NAME}Tests
      COMMAND "${MATLAB_EXECUTABLE}" -nojvm -nodesktop -nosplash -r "${SCRIPT}")
  elseif(WIN32)
    add_test(
      NAME ${PROJECT_NAME}Tests
      COMMAND "${MATLAB_EXECUTABLE}" -nojvm -automation -wait -r "${SCRIPT}")
  else()
    message(FATAL_ERROR "Platform is not supported")
  endif()
else()
  message(WARNING "MATLAB_EXECUTABLE needs to be defined to run the tests")
endif()
