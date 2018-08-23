#include "ci_Thymio_leds_actuator.h"

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#endif

//namespace argos {
//    class CCI_LEDsActuator;
//}


namespace argos {


    void CCI_ThymioLedsActuator::SetProxHIntensity(Intensity intensities){
        for(size_t i = 0; i < m_tSettings.size(); ++i)
        {
            m_tSettings[i] = (short) intensities[i];
//            this->SetSingleIntensity(i,intensities[i]);
        }
    }

    void CCI_ThymioLedsActuator::SetProxVIntensity(Intensity intensities){
        for(size_t i = 0; i < m_tSettings.size(); ++i)
        {
            m_tSettings[i] = (short) intensities[i];
//            this->SetSingleIntensity(i,intensities[i]);
        }
    }

    void CCI_ThymioLedsActuator::SetProxHIntensity(const CCI_ThymioProximitySensor::TReadings intensity){
        for(size_t i = 0; i < m_tSettings.size(); ++i)
        {
            m_tSettings[i] = (short) intensity[i].Value;
//            this->SetSingleIntensity(i,intensity[i].Value);
        }
    }

    void CCI_ThymioLedsActuator::SetProxVIntensity(const CCI_ThymioProximitySensor::TReadings intensity){
        for(size_t i = 0; i < m_tSettings.size(); ++i)
        {
            m_tSettings[i] = (short) intensity[i].Value;
//            this->SetSingleIntensity(i,intensity[i].Value);
        }
    }

}
