include(CPack)

find_package(aseba)
if (NOT ASEBA_FOUND)
    message(FATAL_ERROR "aseba package not found")
else()
    include_directories(${ASEBA_INCLUDE_DIR})
endif (ASEBA_FOUND)

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
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
        )

set(asebacppapi
        thymio_interface.h
        )
install(FILES ${asebacppapi}
        DESTINATION include/aseba/switches/asebacppapi
        )