#ifndef REAL_Thymio_H
#define REAL_Thymio_H

//#include <argos3/plugins/robots/Thymio/real_robot/real_robot.h>
#include "real_robot.h"
#include <argos3/plugins/robots/Thymio/real_robot/real_Thymio_device.h>
#include "real_Thymio_differential_steering_actuator.h"
// #include "real_Thymio_leds_actuator.h"
// #include "real_Thymio_battery_sensor.h"
// #include "real_Thymio_ground_sensor.h"
// #include "real_Thymio_lidar_sensor.h"
#include "real_Thymio_proximity_sensor.h"
#include <argos3/core/utility/logging/argos_log.h>

#include "dbusinterface.h"

using namespace argos;

class CRealThymio : public CRealRobot {

public:

   CRealThymio();
   virtual  ~CRealThymio();
   virtual void            InitRobot();
   virtual void            Destroy();
   virtual CCI_Actuator*   MakeActuator(const std::string& str_name);
   virtual CCI_Sensor*     MakeSensor(const std::string& str_name);
   virtual void            Sense();
   virtual void            Act();

private:

   std::vector<CRealThymioDevice*>  m_vecActuators;
   std::vector<CRealThymioDevice*>  m_vecSensors;
};

#endif // REAL_Thymio_H
