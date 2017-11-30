cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

project(HelloQt)

include(FindPackageMessage)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 QUIET COMPONENTS Core Widgets)
if(Qt5_FOUND)
  find_package_message(Qt5 "Found Qt: ${Qt5_DIR} (found version \"${Qt5_VERSION_MAJOR}.${Qt5_VERSION_MINOR}.${Qt5_VERSION_PATCH}\")" "[${Qt5Widgets_DIR}]")
  set(Qt_LIBRARIES Qt5::Widgets)
else()
  find_package(Qt4 QUIET)
  if(Qt4_FOUND)
    find_package_message(Qt4 "Found Qt: ${QT_QMAKE_EXECUTABLE} (found version \"${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}\")" "[${QT_QTGUI_INCLUDE_DIR}]")
    set(Qt_LIBRARIES Qt4::QtGui)
  else()
    message(FATAL_ERROR "Failed to find Qt v4 or v5")
  endif()
endif()

set(${PROJECT_NAME}Executable_SRCS
  main.cxx
  window.cxx)

set(${PROJECT_NAME}Executable_HDRS
  window.h)

add_executable(${PROJECT_NAME}Executable
  ${${PROJECT_NAME}Executable_SRCS}
  ${${PROJECT_NAME}Executable_HDRS})

target_link_libraries(${PROJECT_NAME}Executable
  ${Qt_LIBRARIES})

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Wall -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME}Executable PRIVATE -Wall -Wextra -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${PROJECT_NAME}Executable PRIVATE /W3)
endif()
