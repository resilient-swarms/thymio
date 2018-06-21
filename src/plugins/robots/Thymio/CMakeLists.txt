#
# Thymio headers
#
# argos3/plugins/robots/Thymio/control_interface
set(ARGOS3_HEADERS_PLUGINS_ROBOTS_Thymio_CONTROLINTERFACE
  control_interface/ci_Thymio_encoder_sensor.h
  control_interface/ci_Thymio_ground_sensor.h
  # control_interface/ci_Thymio_lidar_sensor.h
  # control_interface/ci_Thymio_light_sensor.h
  control_interface/ci_Thymio_proximity_sensor.h
  #control_interface/ci_Thymio_ultrasound_sensor.h
  )
# if(BUZZ_FOUND)
#   set(ARGOS3_HEADERS_PLUGINS_ROBOTS_Thymio_CONTROLINTERFACE
#     ${ARGOS3_HEADERS_PLUGINS_ROBOTS_Thymio_CONTROLINTERFACE}
#     control_interface/buzz_controller_Thymio.h)
# endif(BUZZ_FOUND)
# argos3/plugins/robots/Thymio/simulator
if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_Thymio_SIMULATOR
    simulator/dynamics2d_Thymio_model.h
    simulator/Thymio_entity.h
    # simulator/Thymio_light_rotzonly_sensor.h
    simulator/Thymio_measures.h
    simulator/Thymio_ground_rotzonly_sensor.h
    # simulator/Thymio_lidar_default_sensor.h
    simulator/Thymio_proximity_default_sensor.h
    #simulator/Thymio_ultrasound_default_sensor.h
    )
endif(ARGOS_BUILD_FOR_SIMULATOR)
# argos3/plugins/robots/Thymio/real_robot
if(ARGOS_BUILD_FOR STREQUAL "khiv")
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_Thymio_REALROBOT
    real_robot/real_Thymio.h
    real_robot/real_Thymio_device.h
    real_robot/real_Thymio_differential_steering_actuator.h
    #real_robot/real_Thymio_gripper_actuator.h
    real_robot/real_Thymio_leds_actuator.h
    real_robot/real_Thymio_battery_sensor.h
    real_robot/real_Thymio_ground_sensor.h
    # real_robot/real_Thymio_lidar_sensor.h
    real_robot/real_Thymio_proximity_sensor.h
    #real_robot/real_Thymio_ultrasound_sensor.h
    )
endif(ARGOS_BUILD_FOR STREQUAL "khiv")

#
# Thymio sources
#
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_Thymio
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_Thymio_CONTROLINTERFACE}
  control_interface/ci_Thymio_encoder_sensor.cpp
  control_interface/ci_Thymio_ground_sensor.cpp
  # control_interface/ci_Thymio_lidar_sensor.cpp
  # control_interface/ci_Thymio_light_sensor.cpp
  control_interface/ci_Thymio_proximity_sensor.cpp
  #control_interface/ci_Thymio_ultrasound_sensor.cpp
  )
# if(BUZZ_FOUND)
#   set(ARGOS3_SOURCES_PLUGINS_ROBOTS_Thymio
#     ${ARGOS3_SOURCES_PLUGINS_ROBOTS_Thymio}
#     control_interface/buzz_controller_Thymio.cpp)
# endif(BUZZ_FOUND)

if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_Thymio
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_Thymio}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_Thymio_SIMULATOR}
    simulator/dynamics2d_Thymio_model.cpp
    simulator/Thymio_entity.cpp
    # simulator/Thymio_light_rotzonly_sensor.cpp
    simulator/Thymio_measures.cpp
    simulator/Thymio_ground_rotzonly_sensor.cpp
    # simulator/Thymio_lidar_default_sensor.cpp
    simulator/Thymio_proximity_default_sensor.cpp
    #simulator/Thymio_ultrasound_default_sensor.cpp
    )
  # Compile the graphical visualization only if the necessary libraries have been found
  include(ARGoSCheckQTOpenGL)
  if(ARGOS_COMPILE_QTOPENGL)
    set(ARGOS3_HEADERS_PLUGINS_ROBOTS_Thymio_SIMULATOR
      ${ARGOS3_HEADERS_PLUGINS_ROBOTS_Thymio_SIMULATOR}
      simulator/qtopengl_Thymio.h)
    set(ARGOS3_SOURCES_PLUGINS_ROBOTS_Thymio
      ${ARGOS3_SOURCES_PLUGINS_ROBOTS_Thymio}
      simulator/qtopengl_Thymio.h
      simulator/qtopengl_Thymio.cpp)
  endif(ARGOS_COMPILE_QTOPENGL)
endif(ARGOS_BUILD_FOR_SIMULATOR)
if(ARGOS_BUILD_FOR STREQUAL "khiv")
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_Thymio
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_Thymio}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_Thymio_REALROBOT}
    real_robot/real_Thymio.cpp
    real_robot/real_Thymio_device.cpp
    real_robot/real_Thymio_differential_steering_actuator.cpp
    #real_robot/real_Thymio_gripper_actuator.cpp
    real_robot/real_Thymio_leds_actuator.cpp
    real_robot/real_Thymio_battery_sensor.cpp
    real_robot/real_Thymio_ground_sensor.cpp
    # real_robot/real_Thymio_lidar_sensor.cpp
    real_robot/real_Thymio_proximity_sensor.cpp
    #real_robot/real_Thymio_ultrasound_sensor.cpp
    )
endif(ARGOS_BUILD_FOR STREQUAL "khiv")

#
# Create Thymio plugin
#
add_library(
  argos3plugin_${ARGOS_BUILD_FOR}_Thymio
  SHARED ${ARGOS3_SOURCES_PLUGINS_ROBOTS_Thymio})

target_link_libraries(
  argos3plugin_${ARGOS_BUILD_FOR}_Thymio
  argos3plugin_${ARGOS_BUILD_FOR}_genericrobot)

if(ARGOS_BUILD_FOR_SIMULATOR)
  target_link_libraries(
    argos3plugin_${ARGOS_BUILD_FOR}_Thymio
    argos3plugin_${ARGOS_BUILD_FOR}_dynamics2d
    )
  if(ARGOS_COMPILE_QTOPENGL)
    target_link_libraries(
      argos3plugin_${ARGOS_BUILD_FOR}_Thymio
      argos3plugin_${ARGOS_BUILD_FOR}_qtopengl
      )
  endif(ARGOS_COMPILE_QTOPENGL)
else(ARGOS_BUILD_FOR_SIMULATOR)
  target_link_libraries(
    argos3plugin_${ARGOS_BUILD_FOR}_Thymio
    -lThymio)
endif(ARGOS_BUILD_FOR_SIMULATOR)
# if(BUZZ_FOUND)
#   target_link_libraries(
#     argos3plugin_${ARGOS_BUILD_FOR}_Thymio
#     argos3plugin_${ARGOS_BUILD_FOR}_buzz ${BUZZ_LIBRARY})
# endif(BUZZ_FOUND)

#
# Installation
#
install(
  FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_Thymio_CONTROLINTERFACE}
  DESTINATION include/argos3/plugins/robots/Thymio/control_interface)

if(ARGOS_BUILD_FOR_SIMULATOR)
  install(
    FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_Thymio_SIMULATOR}
    DESTINATION include/argos3/plugins/robots/Thymio/simulator)

  # install(
  #   FILES simulator/Thymio_texture_bottom.png 
  #         simulator/Thymio_texture_side.png
  #         simulator/Thymio_texture_top.png
  #   DESTINATION include/argos3/plugins/simulator/visualizations/qt-opengl/textures)
else(ARGOS_BUILD_FOR_SIMULATOR)
  install(
    FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_Thymio_REALROBOT} 
    DESTINATION include/argos3/plugins/robots/Thymio/real_robot)
  install(
    FILES real_robot/main.cpp 
    DESTINATION include/argos3/plugins/robots/Thymio/real_robot)
endif(ARGOS_BUILD_FOR_SIMULATOR)

install(TARGETS argos3plugin_${ARGOS_BUILD_FOR}_Thymio
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos3
  ARCHIVE DESTINATION lib/argos3)
