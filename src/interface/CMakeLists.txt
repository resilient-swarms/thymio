#if(Qt5DBus_FOUND AND Qt5Test_FOUND)
#        set(CMAKE_AUTOMOC ON)

if(ARGOS_BUILD_FOR STREQUAL "thymio")
#        set(asebadbus
#                real_robot/dbusinterface.cpp
#                real_robot/dbusinterface.h
##                real_robot/main.cpp
#        )

        add_library(asebadbus
            real_robot/dbusinterface.cpp
            real_robot/dbusinterface.h
#            ${CMAKE_SOURCE_DIR}/plugins/robots/Thymio/real_robot/main.cpp
            )
        target_link_libraries(asebadbus
            Qt5::DBus
            Qt5::Test
#            argos3core_${ARGOS_BUILD_FOR}
#            argos3plugin_${ARGOS_BUILD_FOR}_Thymio
#            argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
            )
        qt5_use_modules( asebadbus
                              DBus Test )

endif(ARGOS_BUILD_FOR STREQUAL "thymio")
#endif()

#add_executable(ARGOS3_SOURCES_PLUGINS_ROBOTS_Thymio
#    ${CMAKE_SOURCE_DIR}/plugins/robots/Thymio/real_robot/main.cpp)

