find_library(asebacppapi_LIBRARY NAMES asebacppapi HINTS /usr/local/lib)
include_directories(${LIBXML2_INCLUDE_DIR})

if(ARGOS_BUILD_FOR_SIMULATOR)
   add_library(
        accelerometer_test MODULE
        accelerometer_test.h
        accelerometer_test.cpp
        )
endif(ARGOS_BUILD_FOR_SIMULATOR)

if(ARGOS_BUILD_FOR STREQUAL "thymio")
  add_executable( accelerometer_test
  	accelerometer_test.h
  	accelerometer_test.cpp
  	${CMAKE_SOURCE_DIR}/plugins/robots/Thymio/real_robot/main.cpp
  	)
endif(ARGOS_BUILD_FOR STREQUAL "thymio")

target_link_libraries( accelerometer_test
        argos3core_${ARGOS_BUILD_FOR}
        argos3plugin_${ARGOS_BUILD_FOR}_Thymio
        argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
        ${asebacppapi_LIBRARY}
        ${LIBXML2_LIBRARIES}
        )

