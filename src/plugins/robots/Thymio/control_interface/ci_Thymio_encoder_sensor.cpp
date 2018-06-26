/**
 * @file <argos3/plugins/robots/Thymio/control_interface/ci_Thymio_encoder_sensor.cpp>
 *
 * @author 
 */

#include "ci_Thymio_encoder_sensor.h"

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#endif

namespace argos {
   
  /****************************************/
  /****************************************/
   
  const CCI_ThymioEncoderSensor::SReading& CCI_ThymioEncoderSensor::GetReading() const {
    return m_sReading;
  }
  
  /****************************************/
  /****************************************/
   
#ifdef ARGOS_WITH_LUA
  void CCI_ThymioEncoderSensor::CreateLuaState(lua_State* pt_lua_state) {
    CLuaUtility::OpenRobotStateTable (pt_lua_state, "wheels"                                              );
    CLuaUtility::StartTable          (pt_lua_state, "encoder"                                             );
    CLuaUtility::AddToTable          (pt_lua_state, "distance_left",  m_sReading.CoveredDistanceLeftWheel );
    CLuaUtility::AddToTable          (pt_lua_state, "distance_right", m_sReading.CoveredDistanceRightWheel);
    CLuaUtility::AddToTable          (pt_lua_state, "axis_length",    m_sReading.WheelAxisLength          );
    CLuaUtility::EndTable            (pt_lua_state                                                        );
    CLuaUtility::CloseRobotStateTable(pt_lua_state                                                        );
  }
#endif

  /****************************************/
  /****************************************/

#ifdef ARGOS_WITH_LUA
  void CCI_ThymioEncoderSensor::ReadingsToLuaState(lua_State* pt_lua_state) {
    lua_getfield  (pt_lua_state, -1                                 , "wheels" );
    lua_getfield  (pt_lua_state, -1                                 , "encoder");
    lua_pushnumber(pt_lua_state, m_sReading.CoveredDistanceLeftWheel           );
    lua_setfield  (pt_lua_state, -2                                 , "distance_left");
    lua_pushnumber(pt_lua_state, m_sReading.CoveredDistanceRightWheel);
    lua_setfield  (pt_lua_state, -2                                 , "distance_right");
    lua_pop       (pt_lua_state,  2                                            );
  }
#endif


  /****************************************/
  /****************************************/

}
