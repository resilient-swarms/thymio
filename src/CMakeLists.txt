#
# Compile stuff
#
add_subdirectory(plugins)
add_subdirectory(testing)

if(ARGOS_BUILD_FOR STREQUAL "thymio")
  add_subdirectory(Thymio_NN)
endif(ARGOS_BUILD_FOR STREQUAL "thymio")