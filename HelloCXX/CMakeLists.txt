cmake_minimum_required(VERSION 3.15)

project(HelloCXX LANGUAGES CXX)

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
add_test(
  NAME ${PROJECT_NAME}Test1
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>")
