#find_library(asebacppapi_LIBRARY NAMES asebacppapi HINTS /usr/local/lib)
include_directories(${LIBXML2_INCLUDE_DIR})

if(ARGOS_BUILD_FOR_SIMULATOR)
   add_library(
        sensor_test MODULE
        sensor_test.h
        sensor_test.cpp
        )
endif(ARGOS_BUILD_FOR_SIMULATOR)

if(ARGOS_BUILD_FOR STREQUAL "thymio")
  add_executable( sensor_test
        sensor_test.h
        sensor_test.cpp
        ${CMAKE_SOURCE_DIR}/src/plugins/robots/thymio/real_robot/main.cpp
        )
endif(ARGOS_BUILD_FOR STREQUAL "thymio")

target_link_libraries(sensor_test
        argos3core_${ARGOS_BUILD_FOR}
        argos3plugin_${ARGOS_BUILD_FOR}_thymio
        argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
        ${asebacppapi}
        ${LIBXML2_LIBRARIES}
        )

