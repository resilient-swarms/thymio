if(ARGOS_BUILD_FOR_SIMULATOR)
  add_library(Thymio_diffusion MODULE Thymio_diffusion.h Thymio_diffusion.cpp)
endif(ARGOS_BUILD_FOR_SIMULATOR)
if(ARGOS_BUILD_FOR STREQUAL "khiv")
  add_executable(Thymio_diffusion Thymio_diffusion.h Thymio_diffusion.cpp ${CMAKE_SOURCE_DIR}/plugins/robots/Thymio/real_robot/main.cpp)
endif(ARGOS_BUILD_FOR STREQUAL "khiv")

target_link_libraries(Thymio_diffusion
  argos3core_${ARGOS_BUILD_FOR}
  argos3plugin_${ARGOS_BUILD_FOR}_Thymio
  argos3plugin_${ARGOS_BUILD_FOR}_genericrobot)
