cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(HelloQt LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE}
  main.cxx
  window.cxx
  window.h)

set_target_properties(${EXECUTABLE} PROPERTIES
  AUTOMOC ON
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF)

target_compile_options(${EXECUTABLE} PRIVATE
  "$<$<CXX_COMPILER_ID:Clang>:-Weverything;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:MSVC>:/W4>")

target_link_libraries(${EXECUTABLE} PRIVATE Qt5::Widgets)
