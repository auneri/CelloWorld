cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

project(HelloQt4)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(${PROJECT_NAME}Executable_SRCS
  main.cc
  window.cc)

set(${PROJECT_NAME}Executable_HDRS
  window.h)

qt4_wrap_cpp(${PROJECT_NAME}Executable_QT_SRCS
  window.h)

add_executable(${PROJECT_NAME}Executable
  ${${PROJECT_NAME}Executable_SRCS}
  ${${PROJECT_NAME}Executable_HDRS}
  ${${PROJECT_NAME}Executable_QT_SRCS})

target_link_libraries(${PROJECT_NAME}Executable
  ${QT_LIBRARIES})

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Weverything -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${PROJECT_NAME}Executable PRIVATE /Wall)
endif()
