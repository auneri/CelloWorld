cmake_minimum_required(VERSION 3.15)

project(HelloBoost LANGUAGES CXX)

set(EXECUTABLE ${PROJECT_NAME}Executable)

find_package(Boost QUIET REQUIRED COMPONENTS program_options)

add_executable(${EXECUTABLE}
  main.cxx)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(${EXECUTABLE} PRIVATE -Wall -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(${EXECUTABLE} PRIVATE /W4)
endif()

target_include_directories(${EXECUTABLE} PRIVATE
  ${Boost_INCLUDE_DIRS})

target_link_libraries(${EXECUTABLE} PRIVATE
  ${Boost_LIBRARIES})

enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND "$<TARGET_FILE:${EXECUTABLE}>")
