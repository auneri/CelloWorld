cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(HelloITK)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME}Executable
  main.cxx)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Wall -Wextra -Wfatal-errors)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Wall -Wextra -Wfatal-errors -Wno-unused-local-typedefs)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  target_compile_options(${PROJECT_NAME}Executable PRIVATE /W3)
endif()

target_link_libraries(${PROJECT_NAME}Executable
  PRIVATE ${ITK_LIBRARIES})

include(CTest)
enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND $<TARGET_FILE:${PROJECT_NAME}Executable>)
