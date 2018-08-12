#
# Find the ARGoS package
#
find_package(PkgConfig)
pkg_check_modules(ARGOS REQUIRED argos3_${ARGOS_BUILD_FOR})
set(ARGOS_PREFIX ${ARGOS_PREFIX} CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake)
set(CMAKE_INSTALL_PREFIX ${ARGOS_PREFIX} CACHE STRING "Install path prefix, prepended onto install directories." FORCE)

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
find_package(Lua52)
if(LUA52_FOUND)
  include_directories(${LUA_INCLUDE_DIR})
endif(LUA52_FOUND)

find_package(Buzz)
if(BUZZ_FOUND)
  include_directories(${BUZZ_C_INCLUDE_DIR})
endif(BUZZ_FOUND)

find_package(Qt5 COMPONENTS Widgets )
#    if(Qt5Widgets_FOUND AND Qt5Gui_FOUND)
#        if(Qt5_VERSION VERSION_GREATER 5.4)
                # QT is OK, now check for OpenGL
#                find_package(OpenGL)
                # All the required libraries are OK
#                set(ARGOS_COMPILE_QTOPENGL ON)

                # These are required by Qt5
                set(CMAKE_AUTOMOC ON)
                set(CMAKE_CXX_STANDARD 14)
                set(CMAKE_INCLUDE_CURRENT_DIR ON)
                # Paths
                add_definitions(${Qt5Widgets_DEFINITIONS} )
                include_directories(${Qt5Widgets_INCLUDE_DIRS} )
                set(ARGOS_QTOPENGL_LIBRARIES ${Qt5Widgets_LIBRARIES} )
# Qt and Qwt
#find_package(Qt5 OPTIONAL_COMPONENTS Core Gui Widgets OpenGL Network Help Concurrent Xml Svg Test LinguistTools)


#if (UNIX AND NOT APPLE)
#        find_package(Qt5X11Extras)
        find_package(Qt5DBus)
#endif ()

#if(Qt5_FOUND)
#    add_definitions(${Qt5_DEFINITIONS})
#    include_directories(${Qt5_INCLUDE_DIRS} )
##    message("found QtDBus")
#endif(Qt5_FOUND)

#
# Set ARGoS include dir
#
include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS})

#
# Set ARGoS link dir
#
link_directories(${ARGOS_LIBRARY_DIRS})
