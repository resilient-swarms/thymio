#
# Set minimum required version
#
cmake_minimum_required(VERSION 2.8.12)

#
# Deactivate RPATH for MacOSX
#
set(CMAKE_MACOSX_RPATH 0)


#
# Set the path additional cmake files must be searched for
#
set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)


#
# Set CMake policies to select wanted behaviors
#
# Use new policies introduced up to this version
cmake_policy(VERSION 2.8.12)
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif(POLICY CMP0042)

#
# Include path points to the base source dir
#
#include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})
#include_directories(${CMAKE_SOURCE_DIR})

#
# Make sure we are under Unix
#
if(NOT UNIX)
  message(FATAL_ERROR "ARGoS compiles only under UNIX, sorry!")
endif(NOT UNIX)

#
# Set build options
#
include(${CMAKE_SOURCE_DIR}/cmake/ARGoSBuildOptions.cmake)

#
# Set compiler flags
#
include(${CMAKE_SOURCE_DIR}/cmake/ARGoSBuildFlags.cmake)

#
# Check for libraries
#
include(${CMAKE_SOURCE_DIR}/cmake/ARGoSBuildChecks.cmake)

#
# Set up CPack for later use
#
#include(${CMAKE_SOURCE_DIR}/cmake/ARGoSPackaging.cmake)

if(ARGOS_BUILD_FOR STREQUAL "thymio")
  find_package(LibXml2)
  if (NOT LIBXML2_FOUND)
    messaga(FATAL_ERROR "LibXml2 not found")
  else()
    include_directories(${LIBXML2_INCLUDE_DIR})
  endif (LIBXML2_FOUND)
endif(ARGOS_BUILD_FOR STREQUAL "thymio")



#
# Compile stuff
#
add_subdirectory(src)
if(ARGOS_BUILD_FOR STREQUAL "thymio")
  add_subdirectory(thymiointerface)
endif(ARGOS_BUILD_FOR STREQUAL "thymio")