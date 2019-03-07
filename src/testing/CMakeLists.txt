add_subdirectory(Thymio_diffusion)

if(ARGOS_BUILD_FOR STREQUAL "thymio")
    add_subdirectory(sensor_test)
    add_subdirectory(sensor_test2)
    add_subdirectory(ground_sensor_test)
    add_subdirectory(Accelerometer_test)
    add_subdirectory(Accelerometer_test2)
endif(ARGOS_BUILD_FOR STREQUAL "thymio")
