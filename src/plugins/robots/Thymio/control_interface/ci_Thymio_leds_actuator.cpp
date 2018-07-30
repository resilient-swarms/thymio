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

#ifdef ARGOS_WITH_LUA
   void CCI_ThymioLedsActuator::CreateLuaState(lua_State* pt_lua_state) {
//      CLuaUtility::OpenRobotStateTable(pt_lua_state, "leds");
//      CLuaUtility::AddToTable(pt_lua_state, "_instance", this);
//      CLuaUtility::AddToTable(pt_lua_state, "set_single_color", &LuaLEDSetSingleColor);
//      CLuaUtility::AddToTable(pt_lua_state, "set_all_colors", &LuaLEDSetAllColors);
//      CLuaUtility::CloseRobotStateTable(pt_lua_state);
   }
#endif
}
