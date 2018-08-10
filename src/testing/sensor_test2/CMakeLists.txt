if(ARGOS_BUILD_FOR_SIMULATOR)
   add_library(
        sensor_test2 MODULE
        sensor_test2.h
        sensor_test2.cpp
        )
endif(ARGOS_BUILD_FOR_SIMULATOR)

if(ARGOS_BUILD_FOR STREQUAL "thymio")
  add_library( sensor_test2
  	sensor_test2.h
  	sensor_test2.cpp
#        ${CMAKE_SOURCE_DIR}/plugins/robots/Thymio/real_robot/main.cpp
  	)

endif(ARGOS_BUILD_FOR STREQUAL "thymio")

target_link_libraries( sensor_test2
        argos3core_${ARGOS_BUILD_FOR}
        argos3plugin_${ARGOS_BUILD_FOR}_Thymio
        argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
        )
