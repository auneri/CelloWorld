cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

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

if (CMAKE_CONFIGURATION_TYPES)
  add_custom_target(test_verbose ${CMAKE_CTEST_COMMAND} --force-new-ctest-process --output-on-failure --build-config "$<CONFIGURATION>")
else()
  add_custom_target(test_verbose ${CMAKE_CTEST_COMMAND} --force-new-ctest-process --output-on-failure)
endif()
set_target_properties(test_verbose PROPERTIES PROJECT_LABEL "RUN_TESTS_VERBOSE")
