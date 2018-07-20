/**
 * @file <argos3/plugins/robots/Thymio/control_interface/ci_Thymio_proximity_sensor.h>
 *
 * @brief This file provides the definition of the Thymio IV proximity sensor.
 *
 * This file provides the definition of the Thymio IV proximity sensor.
 * The sensors are evenly spaced on a ring around the base of the robot.
 * The readings are normalized between 0 and 1, and are in the following
 * order (seeing the robot from TOP, the camera is the FRONT):
 * 
 *      front
 * 
 * l      2      r
 * e    1   3    i
 * f  0       4  g
 * t             h
 *      6   5    t
 * 
 *       back   
 *
 * @author 
 */

#ifndef CCI_Thymio_PROXIMITY_SENSOR_H
#define CCI_Thymio_PROXIMITY_SENSOR_H

namespace argos {
   class CCI_ThymioProximitySensor;
}

#include <argos3/core/control_interface/ci_sensor.h>
#include <argos3/core/utility/math/angles.h>

namespace argos {

   class CCI_ThymioProximitySensor : public CCI_Sensor {

   public:

      struct SReading {
         Real Value;
         CRadians Angle;

         SReading() :
            Value(0.0f) {}

         SReading(Real f_value,
                  const CRadians& c_angle) :
            Value(f_value),
            Angle(c_angle) {}
      };

      typedef std::vector<SReading> TReadings;

   public:

      /**
       * Class constructor
       */
      CCI_ThymioProximitySensor();

      /**
       * Class destructor
       */
      virtual ~CCI_ThymioProximitySensor() {}

      /**
       * Returns the readings of this sensor
       */
      const TReadings& GetReadings() const;

#ifdef ARGOS_WITH_LUA
      virtual void CreateLuaState(lua_State* pt_lua_state);

      virtual void ReadingsToLuaState(lua_State* pt_lua_state);
#endif

   protected:

      TReadings m_tReadings;

   };

   std::ostream& operator<<(std::ostream& c_os, const CCI_ThymioProximitySensor::SReading& s_reading);
   std::ostream& operator<<(std::ostream& c_os, const CCI_ThymioProximitySensor::TReadings& t_readings);

}

#endif
