
if(ARGOS_BUILD_FOR_SIMULATOR)
  add_library(
	draw_position 
	MODULE	draw_position.h
			draw_position.cpp
	)
    target_link_libraries(
            draw_position
            argos3core_${ARGOS_BUILD_FOR}
            argos3plugin_${ARGOS_BUILD_FOR}_Thymio
            argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
            argos3plugin_${ARGOS_BUILD_FOR}_qtopengl
            ${ARGOS_QTOPENGL_LIBRARIES}
            )
endif(ARGOS_BUILD_FOR_SIMULATOR)	


