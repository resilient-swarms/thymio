#
# Find the ARGoS package
#
find_package(PkgConfig)
pkg_check_modules(ARGOS REQUIRED argos3_${ARGOS_BUILD_FOR})
set(ARGOS_PREFIX ${ARGOS_PREFIX} CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake)
#set(CMAKE_INSTALL_PREFIX ${ARGOS_PREFIX} CACHE STRING "Install path prefix, prepended onto install directories." FORCE)

#
# Check whether all the necessary libs have been installed to compile the
# code that depends on Qt and OpenGL
#
if(ARGOS_BUILD_FOR_SIMULATOR)
  include(ARGoSCheckQTOpenGL)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# Find Lua
#
find_package(Lua53)
if(LUA53_FOUND)
  include_directories(${LUA_INCLUDE_DIR})
else(LUA53_FOUND)
  MESSAGE( "Please point the environment variable LUA_DIR to your Lua installation -- include and lib.")
  MESSAGE("Will try to add include directory for Lua manually based on your LUA_DIR environment variable")
  include_directories($ENV{LUA_DIR})
ENDIF(LUA53_FOUND)

#find_package(Buzz)
#if(BUZZ_FOUND)
#  include_directories(${BUZZ_C_INCLUDE_DIR})
#endif(BUZZ_FOUND)


##find_package( Qt5Core REQUIRED )

#find_package(LibXml2)
#include_directories(${LIBXML2_INCLUDE_DIR})

#
# Set ARGoS include dir
#
include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS})

#
# Set ARGoS link dir
#
link_directories(${ARGOS_LIBRARY_DIRS})
