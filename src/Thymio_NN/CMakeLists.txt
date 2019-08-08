

if(ARGOS_BUILD_FOR STREQUAL "thymio")

find_library(asebacppapi_LIBRARY NAMES asebacppapi HINTS /usr/local/lib)
include_directories(${LIBXML2_INCLUDE_DIR})

set(SFERES ${PROJECT_SOURCE_DIR}/sferes2) # location of sferes2 - where https://github.com/sferes2/sferes2 has been cloned
include_directories(${SFERES})
#message(${SFERES})

# Eigen3
SET(EIGEN3_INCLUDE_DIR "$ENV{EIGEN3_INCLUDE_DIR}")
IF(NOT EIGEN3_INCLUDE_DIR )
	MESSAGE( FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
ELSE()
	include_directories("${EIGEN3_INCLUDE_DIR}")
	add_definitions( -DEIGEN3_ENABLED )
ENDIF()

set(Boost_NO_BOOST_CMAKE      ON) # disable the search for boost-cmake
set(BOOST_INCLUDEDIR "/usr/include/boost/") # hint location to search for boost headers
set(BOOST_LIBRARYDIR "/usr/lib/x86_64-linux-gnu/") # hint location to search for boost libs
find_package(Boost COMPONENTS serialization REQUIRED)
# system unit_test_framework thread REQUIRED)
if(Boost_FOUND)
	link_directories(${Boost_LIBRARY_DIRS})
	include_directories(${Boost_INCLUDE_DIRS})
	message("Boost libs found in: " ${Boost_LIBRARY_DIRS})
	message("Boost headers found in: " ${Boost_INCLUDE_DIRS})
else(NOT Boost_FOUND)
	message(FATAL_ERROR "Unable to continue without BOOST")
endif()

add_executable(Thymio_NN
		  Thymio_NN.h
		  Thymio_NN.cpp
  	${CMAKE_SOURCE_DIR}/plugins/robots/thymio/real_robot/main.cpp
		${SFERES}
  	)

  target_link_libraries(Thymio_NN
		  argos3core_${ARGOS_BUILD_FOR}
		  argos3plugin_${ARGOS_BUILD_FOR}_thymio
		  argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
		  ${asebacppapi_LIBRARY}
		  ${LIBXML2_LIBRARIES}
		  ${Boost_LIBRARIES}
		  )

endif(ARGOS_BUILD_FOR STREQUAL "thymio")
