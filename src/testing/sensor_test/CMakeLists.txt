if(ARGOS_BUILD_FOR_SIMULATOR OR ARGOS_BUILD_FOR STREQUAL "thymio")
   add_library(
        sensor_test MODULE
        sensor_test.h
        sensor_test.cpp
        )
endif(ARGOS_BUILD_FOR_SIMULATOR OR ARGOS_BUILD_FOR STREQUAL "thymio")

#if(ARGOS_BUILD_FOR STREQUAL "thymio")
#  add_library( sensor_test
#  	sensor_test.h
#  	sensor_test.cpp
##        ${CMAKE_SOURCE_DIR}/plugins/robots/Thymio/real_robot/main.cpp
    
#  	)

#endif(ARGOS_BUILD_FOR STREQUAL "thymio")


target_link_libraries(sensor_test
  argos3core_${ARGOS_BUILD_FOR}
  argos3plugin_${ARGOS_BUILD_FOR}_thymio
  argos3plugin_${ARGOS_BUILD_FOR}_genericrobot)





