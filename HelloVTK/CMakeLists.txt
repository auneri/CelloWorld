cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(HelloVTK)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(${PROJECT_NAME}Executable
  main.cxx)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Wall -Wextra -Wfatal-errors)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Wall -Wextra -Wfatal-errors)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  target_compile_options(${PROJECT_NAME}Executable PRIVATE /W4)
endif()

target_link_libraries(${PROJECT_NAME}Executable
  PRIVATE ${VTK_LIBRARIES})
