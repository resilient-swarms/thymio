find_package( Qt5Core REQUIRED )

if(ARGOS_BUILD_FOR_SIMULATOR AND NOT BUILD_FOR_THYMIO)
   add_library(
        sensor_test MODULE
        sensor_test.h
        sensor_test.cpp
        )
endif(ARGOS_BUILD_FOR_SIMULATOR AND NOT BUILD_FOR_THYMIO)

if(BUILD_FOR_THYMIO)
  add_executable( sensor_test
  	sensor_test.h
  	sensor_test.cpp
  	${CMAKE_SOURCE_DIR}/plugins/robots/Thymio/real_robot/main.cpp
    
  	)

endif(BUILD_FOR_THYMIO)

target_link_libraries( sensor_test
  	argos3core_${ARGOS_BUILD_FOR}
  	argos3plugin_${ARGOS_BUILD_FOR}_Thymio
  	argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
        Qt5::DBus
  	)

qt5_use_modules( sensor_test
                   DBus Test )

