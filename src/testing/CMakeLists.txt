add_subdirectory(thymio_diffusion)

if(ARGOS_BUILD_FOR STREQUAL "thymio")
    add_subdirectory(sensor_test)
    add_subdirectory(sensor_test2)
    add_subdirectory(ground_sensor_test)
    add_subdirectory(accelerometer_test)
    add_subdirectory(accelerometer_test2)
endif(ARGOS_BUILD_FOR STREQUAL "thymio")
