cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(HelloBoost)

if(WIN32)
  set(Boost_ROOT_DIR "" CACHE PATH "")
  set(BOOST_ROOT ${Boost_ROOT_DIR})
endif()
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS program_options REQUIRED)

add_executable(${PROJECT_NAME}Executable
  main.cxx)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Weverything -Wfatal-errors)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Wall -Wextra -Wfatal-errors)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  target_compile_options(${PROJECT_NAME}Executable PRIVATE /Wall)
endif()

target_link_libraries(${PROJECT_NAME}Executable
  PRIVATE ${Boost_LIBRARIES})

include(CTest)
enable_testing()
add_test(
  NAME ${PROJECT_NAME}Tests
  COMMAND $<TARGET_FILE:${PROJECT_NAME}Executable>)
