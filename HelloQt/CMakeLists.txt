cmake_minimum_required(VERSION 3.15)

project(HelloQt LANGUAGES CXX)

find_package(Qt6 QUIET COMPONENTS Core Widgets)
if(NOT Qt6_FOUND)
  find_package(Qt5 5.15 REQUIRED COMPONENTS Core Widgets)
endif()

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

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wextra -Wpedantic -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wextra -Wpedantic -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(${EXECUTABLE} PRIVATE /W4)
endif()

target_link_libraries(${EXECUTABLE} PRIVATE Qt::Widgets)

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Test1
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>" "--no-gui")
