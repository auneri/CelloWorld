cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

project(HelloPython)

add_library(${PROJECT_NAME}Library
  library.cc)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(${PROJECT_NAME}Library PRIVATE -Weverything -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME}Library PRIVATE -Wall -Wextra -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${PROJECT_NAME}Library PRIVATE /Wall)
endif()

find_package(PythonInterp REQUIRED)
find_package(PythonLibs ${PYTHON_VERSION_STRING} EXACT REQUIRED)
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

set_source_files_properties(library.i PROPERTIES CPLUSPLUS ON)
swig_add_module(${PROJECT_NAME} python
  library.i)
swig_link_libraries(${PROJECT_NAME}
  ${PROJECT_NAME}Library
  ${PYTHON_LIBRARIES})
target_include_directories(${SWIG_MODULE_${PROJECT_NAME}_REAL_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}
  ${PYTHON_INCLUDE_PATH})
add_custom_command(
  TARGET ${SWIG_MODULE_${PROJECT_NAME}_REAL_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${SWIG_MODULE_${PROJECT_NAME}_REAL_NAME}> Python/$<TARGET_FILE_NAME:${SWIG_MODULE_${PROJECT_NAME}_REAL_NAME}>
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_NAME}.py Python/${PROJECT_NAME}.py
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

if(PYTHON_EXECUTABLE)
  include(CTest)
  enable_testing()

  configure_file(
    tests.py
    ${PROJECT_BINARY_DIR}/Python/${PROJECT_NAME}Tests.py
    @ONLY)

  add_test(
    NAME ${PROJECT_NAME}Tests
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Python
    COMMAND ${PYTHON_EXECUTABLE} -m ${PROJECT_NAME}Tests)
else()
  message(WARNING "PYTHON_EXECUTABLE needs to be defined to run the tests")
endif()
