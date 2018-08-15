#find_package( Qt5Core REQUIRED )

if(ARGOS_BUILD_FOR_SIMULATOR AND NOT BUILD_FOR_THYMIO)
   add_library(
        sensor_test2 MODULE
        sensor_test2.h
        sensor_test2.cpp
        )
endif(ARGOS_BUILD_FOR_SIMULATOR AND NOT BUILD_FOR_THYMIO)

if(BUILD_FOR_THYMIO)
  add_executable( sensor_test2
  	sensor_test2.h
  	sensor_test2.cpp
  	${CMAKE_SOURCE_DIR}/plugins/robots/Thymio/real_robot/main.cpp
    
  	)

endif(BUILD_FOR_THYMIO)

target_link_libraries( sensor_test2
  	argos3core_${ARGOS_BUILD_FOR}
  	argos3plugin_${ARGOS_BUILD_FOR}_Thymio
  	argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
        Qt5::DBus
  	)

qt5_use_modules( sensor_test2
                   DBus Test )

