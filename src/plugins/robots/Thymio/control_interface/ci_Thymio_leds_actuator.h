#ifndef CI_THYMIO_LEDS_ACTUATOR_H
#define CI_THYMIO_LEDS_ACTUATOR_H

namespace argos {
    class CCI_ThymioLedsActuator;
}

#include <argos3/core/control_interface/ci_actuator.h>
//#include <argos3/plugins/robots/generic/control_interface/ci_leds_actuator.h>
#include <argos3/plugins/robots/Thymio/control_interface/ci_Thymio_proximity_sensor.h>

namespace argos {
   class CCI_ThymioLedsActuator : public CCI_Actuator{

   public:

       typedef std::vector<short> TSettings;

       typedef std::vector<short> Intensity;

   public:

       CCI_ThymioLedsActuator() {}

       virtual ~CCI_ThymioLedsActuator() {}

       virtual void SetProxHIntensity(std::vector<short> intensity) = 0;

       virtual void SetProxVIntensity(std::vector<short> intensity) = 0;

       virtual void SetProxHIntensity(const CCI_ThymioProximitySensor::TReadings intensity) = 0;

       virtual void SetProxVIntensity(const CCI_ThymioProximitySensor::TReadings intensity) = 0;

#ifdef ARGOS_WITH_LUA
       virtual void CreateLuaState(lua_State* pt_lua_state){}
#endif

   protected:

       TSettings m_tSettings;

    };
}

#endif // CI_THYMIO_LEDS_ACTUATOR_H
