project(asebacppapi)
include(CPack)

find_library(asebacommon asebacommon)
if(NOT asebacommon)
  message(FATAL_ERROR "asebacommon not found")
else()
  message(STATUS "asebacommon found at ${asebacommon}")
endif()

find_library(asebadashelplugins asebadashelplugins)
if(NOT asebadashelplugins)
  message(FATAL_ERROR "asebadashelplugins not found")
else()
  message(STATUS "asebadashelplugins found at ${asebadashelplugins}")
endif()

find_library(asebacompiler asebacompiler)
if(NOT asebacompiler)
  message(FATAL_ERROR "asebacompiler not found")
else()
  message(STATUS "asebacompiler found at ${asebacompiler}")
endif()

find_library(dashel dashel)
if(NOT dashel)
  message(FATAL_ERROR "dashel not found")
else()
  message(STATUS "dashel found at ${dashel}")
endif()

set(thymio_interface
        thymio_interface.cpp
        thymio_interface.h
        )


add_library(asebacppapi SHARED ${thymio_interface})
target_link_libraries(asebacppapi 
	asebadashelplugins
	asebacompiler
	${LIBXML2_LIBRARIES} 
	asebacommon
	dashel
	udev
	)

install(TARGETS asebacppapi
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )

set(asebacppapi_header
        thymio_interface.h
        )
install(FILES ${asebacppapi_header}
        DESTINATION include/aseba/switches/asebacppapi
        )