cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(CelloWorld)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB FOLDERS "${PROJECT_SOURCE_DIR}/Hello*")
foreach(FOLDER ${FOLDERS})
  get_filename_component(NAME ${FOLDER} NAME)
  option(BUILD_${NAME} "Build ${NAME}" OFF)
  if(BUILD_${NAME})
    add_subdirectory(${NAME})
  endif()
endforeach()

enable_testing()
