#find_library(asebacppapi_LIBRARY NAMES asebacppapi HINTS /usr/local/lib)
#include_directories(${LIBXML2_INCLUDE_DIR})

if(ARGOS_BUILD_FOR_SIMULATOR)
   add_library(
        thymio_diffusion MODULE
		   thymio_diffusion.h
		   thymio_diffusion.cpp
        )

   target_link_libraries(thymio_diffusion
		   argos3core_${ARGOS_BUILD_FOR}
		   argos3plugin_${ARGOS_BUILD_FOR}_thymio
		   argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
		   ${LIBXML2_LIBRARIES}
		   )

   add_subdirectory(loop_functions)
   add_subdirectory(trajectory_loop_functions)
endif(ARGOS_BUILD_FOR_SIMULATOR)

if(ARGOS_BUILD_FOR STREQUAL "thymio")
  add_executable(thymio_diffusion
		  thymio_diffusion.h
		  thymio_diffusion.cpp
  	${CMAKE_SOURCE_DIR}/src/plugins/robots/thymio/real_robot/main.cpp
  	)

  target_link_libraries(thymio_diffusion
		  asebacppapi
		  argos3core_${ARGOS_BUILD_FOR}
		  argos3plugin_${ARGOS_BUILD_FOR}_thymio
		  argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
		  ${LIBXML2_LIBRARIES}
		  )
endif(ARGOS_BUILD_FOR STREQUAL "thymio")
