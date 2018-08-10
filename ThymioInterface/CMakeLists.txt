# emacs: -*- CMake -*-
# kate: replace-tabs off; tab-width 4; indent-width 4; tab-indents true; indent-mode normal
# vim: ts=4:sw=4:noexpandtab

# project name
project(ThymioInterface)

# ensure a minimal version of CMake
cmake_minimum_required(VERSION 3.5)
include(FeatureSummary)

# additional CMake modules
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/CMakeModules)


# testing and defines
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


#feature_summary( WHAT PACKAGES_FOUND PACKAGES_NOT_FOUND ENABLED_FEATURES DISABLED_FEATURES)

include(CPack)

# libxml2
find_package(LibXml2)
if (LIBXML2_FOUND)
	include_directories(${LIBXML2_INCLUDE_DIR})

	add_executable(thymiointerface
		thymio_interface.cpp
	)
        target_link_libraries(thymiointerface asebadashelplugins asebacompiler ${LIBXML2_LIBRARIES} asebacommon dashel)
endif (LIBXML2_FOUND)

