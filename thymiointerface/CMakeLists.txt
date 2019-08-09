include(CPack)

set(ASEBA $ENV{ASEBA}) # location of Thymio plugin installation -- include and libs
IF( NOT ASEBA )
    MESSAGE( FATAL_ERROR "Please point the environment variable ASEBA to the location of the aseba installation (include and libs)")
ELSE()
    include_directories(${ASEBA}/include)
    link_directories(${ASEBA}/lib)
ENDIF()

#set(CMAKE_AUTOMOC ON)

set(aseba_cpp_api_SRCS
        thymio_interface.cpp
        thymio_interface.h
        )

add_executable(aseba_cpp_api ${aseba_cpp_api_SRCS})
target_link_libraries(aseba_cpp_api asebadashelplugins asebacompiler ${LIBXML2_LIBRARIES} asebacommon dashel)


add_library(asebacppapi SHARED ${aseba_cpp_api_SRCS})
target_link_libraries(asebacppapi asebadashelplugins asebacompiler ${LIBXML2_LIBRARIES} asebacommon dashel)
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