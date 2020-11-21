cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(HelloBoost LANGUAGES CXX)

set(EXECUTABLE ${PROJECT_NAME}Executable)

find_package(Boost QUIET REQUIRED COMPONENTS program_options)

add_executable(${EXECUTABLE}
  main.cxx)

target_compile_options(${EXECUTABLE} PRIVATE
  "$<$<CXX_COMPILER_ID:Clang>:-Weverything;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wfatal-errors>"
  "$<$<CXX_COMPILER_ID:MSVC>:/Wall>")

target_include_directories(${EXECUTABLE} PRIVATE
  ${Boost_INCLUDE_DIRS})

target_link_libraries(${EXECUTABLE} PRIVATE
  ${Boost_LIBRARIES})

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>")
