cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

project(HelloITK)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME}Executable
  main.cxx)

target_link_libraries(${PROJECT_NAME}Executable
  ${ITK_LIBRARIES})

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Wall -Wextra -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Wall -Wextra -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${PROJECT_NAME}Executable PRIVATE /W3)
endif()

include(CTest)
enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND $<TARGET_FILE:${PROJECT_NAME}Executable>)
