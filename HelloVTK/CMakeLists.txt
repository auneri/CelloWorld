cmake_minimum_required(VERSION 3.15)

project(HelloVTK LANGUAGES CXX)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE}
  main.cxx)

target_compile_options(${EXECUTABLE} PRIVATE
  "$<$<CXX_COMPILER_ID:Clang>:-Weverything;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:MSVC>:/W4>")

target_link_libraries(${EXECUTABLE} PRIVATE
  ${VTK_LIBRARIES})
