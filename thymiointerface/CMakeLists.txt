include(CPack)

set(ASEBA $ENV{ASEBA}) # location of aseba plugin installation -- include and libs
#IF( NOT ASEBA )
#    MESSAGE( FATAL_ERROR "Please point the environment variable ASEBA to the location of the aseba installation (include and libs)")
#ELSE()
#    include_directories(${ASEBA}/include)
#    #link_directories(${ASEBA}/lib)
#ENDIF()

find_library(asebacommon asebacommon HINTS ${ASEBA})
find_library(asebadashelplugins asebadashelplugins HINTS ${ASEBA})
find_library(asebacompiler asebacompiler HINTS ${ASEBA})
find_library(dashel dashel HINTS ${ASEBA})

set(thymio_interface
        thymio_interface.cpp
        thymio_interface.h
        )


add_library(asebacppapi SHARED ${thymio_interface})
target_link_libraries(asebacppapi 
	${asebadashelplugins}
	${asebacompiler}
	${LIBXML2_LIBRARIES} 
	${asebacommon}
	${dashel}
	)
install(TARGETS asebacppapi
        LIBRARY DESTINATION ${ASEBA}/lib
        ARCHIVE DESTINATION ${ASEBA}/lib
        )

set(asebacppapi
        thymio_interface.h
        )
install(FILES ${asebacppapi}
        DESTINATION include/aseba/switches/asebacppapi
        )