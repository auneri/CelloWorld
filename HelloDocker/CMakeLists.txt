cmake_minimum_required(VERSION 3.15)

project(HelloDocker LANGUAGES CXX)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE} main.cxx)

set_target_properties(${EXECUTABLE} PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wextra -Wpedantic -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wextra -Wpedantic -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(${EXECUTABLE} PRIVATE /W4)
endif()

enable_testing()
if(DEFINED ENV{ISDOCKER})
  add_test(
    NAME ${PROJECT_NAME}Test1
    COMMAND "$<TARGET_FILE:${EXECUTABLE}>")
else()
  add_test(
    NAME ${PROJECT_NAME}Test1
    COMMAND docker build --tag hello_docker "${PROJECT_SOURCE_DIR}")
  add_test(
    NAME ${PROJECT_NAME}Test2
    COMMAND docker run --rm hello_docker)
endif()
