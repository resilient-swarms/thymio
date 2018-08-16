#find_package( Qt5Core REQUIRED )

if(ARGOS_BUILD_FOR_SIMULATOR AND NOT BUILD_FOR_THYMIO)
   add_library(
        ground_sensor_test MODULE
        ground_sensor_test.h
        ground_sensor_test.cpp
        )
endif(ARGOS_BUILD_FOR_SIMULATOR AND NOT BUILD_FOR_THYMIO)

if(BUILD_FOR_THYMIO)
  add_executable( ground_sensor_test
  	ground_sensor_test.h
  	ground_sensor_test.cpp
  	${CMAKE_SOURCE_DIR}/plugins/robots/Thymio/real_robot/main.cpp
    
  	)

endif(BUILD_FOR_THYMIO)

target_link_libraries( ground_sensor_test
  	argos3core_${ARGOS_BUILD_FOR}
  	argos3plugin_${ARGOS_BUILD_FOR}_Thymio
  	argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
        Qt5::DBus
  	)

qt5_use_modules( ground_sensor_test
                   DBus Test )

