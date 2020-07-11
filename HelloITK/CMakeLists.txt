cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(HelloITK LANGUAGES CXX)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

set(EXECUTABLE ${PROJECT_NAME}Executable)

add_executable(${EXECUTABLE}
  main.cxx)

target_compile_options(${EXECUTABLE} PUBLIC
  "$<$<CXX_COMPILER_ID:Clang>:-Weverything;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wfatal-errors;-Wno-unused-local-typedefs>"
  "$<$<CXX_COMPILER_ID:MSVC>:/W3>")

target_link_libraries(${EXECUTABLE} PRIVATE
  ${ITK_LIBRARIES})

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>")
