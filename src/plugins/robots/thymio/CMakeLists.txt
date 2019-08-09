#
# Thymio headers
#

set(ARGOS3_HEADERS_PLUGINS_ROBOTS_THYMIO_CONTROLINTERFACE
  control_interface/ci_thymio_ground_sensor.h
  control_interface/ci_thymio_proximity_sensor.h
  control_interface/ci_thymio_leds_actuator.h
  control_interface/ci_thymio_acc_sensor.h
  )

if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_THYMIO_SIMULATOR
    simulator/dynamics2d_thymio_model.h
    simulator/thymio_entity.h
    simulator/thymio_measures.h
    simulator/thymio_proximity_default_sensor.h
    simulator/thymio_ground_rotzonly_sensor.h
    simulator/thymio_led_actuator.h
#    simulator/Thymio_acc_sensor.h
    )
endif(ARGOS_BUILD_FOR_SIMULATOR)

if(ARGOS_BUILD_FOR STREQUAL "thymio")
    set(ARGOS3_HEADERS_PLUGINS_ROBOTS_THYMIO_REALROBOT
      real_robot/real_thymio.h
      real_robot/real_thymio_device.h
      real_robot/real_thymio_differential_steering_actuator.h
      real_robot/real_thymio_leds_actuator.h
      # real_robot/real_Thymio_battery_sensor.h
      real_robot/real_thymio_ground_sensor.h
      real_robot/real_thymio_proximity_sensor.h
      real_robot/real_thymio_acc_sensor.h
#      real_robot/real_robot.h
      )
endif(ARGOS_BUILD_FOR STREQUAL "thymio") #endif(ARGOS_BUILD_FOR STREQUAL "thymio"s)


#
# Thymio sources
#
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_THYMIO
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_THYMIO_CONTROLINTERFACE}
  control_interface/ci_thymio_ground_sensor.cpp
  control_interface/ci_thymio_proximity_sensor.cpp
  control_interface/ci_thymio_leds_actuator.cpp
  control_interface/ci_thymio_acc_sensor.cpp
  )

if(ARGOS_BUILD_FOR_SIMULATOR)
    set(ARGOS3_SOURCES_PLUGINS_ROBOTS_THYMIO
      ${ARGOS3_SOURCES_PLUGINS_ROBOTS_THYMIO}
      ${ARGOS3_HEADERS_PLUGINS_ROBOTS_THYMIO_SIMULATOR}
      simulator/dynamics2d_thymio_model.cpp
      simulator/thymio_entity.cpp
      simulator/thymio_measures.cpp
      simulator/thymio_ground_rotzonly_sensor.cpp
      simulator/thymio_proximity_default_sensor.cpp
      simulator/thymio_led_actuator.cpp
#      simulator/Thymio_acc_sensor.cpp
      )
  # Compile the graphical visualization only if the necessary libraries have been found
    include(ARGoSCheckQTOpenGL)
      if(ARGOS_COMPILE_QTOPENGL)
        set(ARGOS3_HEADERS_PLUGINS_ROBOTS_THYMIO_SIMULATOR
            ${ARGOS3_HEADERS_PLUGINS_ROBOTS_THYMIO_SIMULATOR}
            simulator/qtopengl_thymio.h
            )
        set(ARGOS3_SOURCES_PLUGINS_ROBOTS_THYMIO
            ${ARGOS3_SOURCES_PLUGINS_ROBOTS_THYMIO}
            simulator/qtopengl_thymio.h
            simulator/qtopengl_thymio.cpp
            )
  endif(ARGOS_COMPILE_QTOPENGL)
endif(ARGOS_BUILD_FOR_SIMULATOR)


if(ARGOS_BUILD_FOR STREQUAL "thymio")
    set(ARGOS3_SOURCES_PLUGINS_ROBOTS_THYMIO
      ${ARGOS3_SOURCES_PLUGINS_ROBOTS_THYMIO}
      ${ARGOS3_HEADERS_PLUGINS_ROBOTS_THYMIO_REALROBOT}
      real_robot/real_thymio.cpp
      real_robot/real_thymio_device.cpp
      real_robot/real_thymio_differential_steering_actuator.cpp
      real_robot/real_thymio_leds_actuator.cpp
#       real_robot/real_Thymio_battery_sensor.cpp
      real_robot/real_thymio_ground_sensor.cpp
      real_robot/real_thymio_proximity_sensor.cpp
      real_robot/real_thymio_acc_sensor.cpp
#      real_robot/real_robot.cpp
#      real_robot/thymio_interface.cpp
      )
endif(ARGOS_BUILD_FOR STREQUAL "thymio")

#
# Create Thymio plugin
#
add_library(
  argos3plugin_${ARGOS_BUILD_FOR}_thymio
  SHARED ${ARGOS3_SOURCES_PLUGINS_ROBOTS_THYMIO})

target_link_libraries(
  argos3plugin_${ARGOS_BUILD_FOR}_thymio
  argos3plugin_${ARGOS_BUILD_FOR}_genericrobot)

if(ARGOS_BUILD_FOR STREQUAL "thymio")
  target_link_libraries (
    argos3plugin_${ARGOS_BUILD_FOR}_thymio
    asebacppapi
  )
endif(ARGOS_BUILD_FOR STREQUAL "thymio")

if(ARGOS_BUILD_FOR_SIMULATOR)
  target_link_libraries(
    argos3plugin_${ARGOS_BUILD_FOR}_thymio
    argos3plugin_${ARGOS_BUILD_FOR}_dynamics2d
    )
  if(ARGOS_COMPILE_QTOPENGL)
    target_link_libraries(
      argos3plugin_${ARGOS_BUILD_FOR}_thymio
      argos3plugin_${ARGOS_BUILD_FOR}_qtopengl
      )
  endif(ARGOS_COMPILE_QTOPENGL)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# Installation
#
install(
  FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_THYMIO_CONTROLINTERFACE}
  DESTINATION include/argos3/plugins/robots/thymio/control_interface
  )

if(ARGOS_BUILD_FOR_SIMULATOR)
  install(
    FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_THYMIO_SIMULATOR}
    DESTINATION include/argos3/plugins/robots/thymio/simulator
    )
endif(ARGOS_BUILD_FOR_SIMULATOR)

if(BUILD_FOR_THYMIO AND NOT ARGOS_BUILD_FOR_SIMULATOR)
    install(
      FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_THYMIO_REALROBOT}
      DESTINATION include/argos3/plugins/robots/thymio/real_robot
      )
    install(
      FILES real_robot/main.cpp
      DESTINATION include/argos3/plugins/robots/thymio/real_robot
      )
endif(BUILD_FOR_THYMIO AND NOT ARGOS_BUILD_FOR_SIMULATOR)

install(
  TARGETS argos3plugin_${ARGOS_BUILD_FOR}_thymio
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos3
  ARCHIVE DESTINATION lib/argos3
  )
