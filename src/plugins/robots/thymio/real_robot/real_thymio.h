#ifndef REAL_Thymio_H
#define REAL_Thymio_H

#include <argos3/core/real_robot/real_robot.h>
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/plugins/robots/thymio/real_robot/real_thymio_device.h>

#include <aseba/switches/asebacppapi/thymio_interface.h>

using namespace argos;

class CRealThymio : public CRealRobot {
public:
   Aseba::ThymioInterface* ThymioInterface;
public:

   CRealThymio();
   virtual  ~CRealThymio();
   virtual void            InitRobot();
   virtual void            Destroy();
   virtual CCI_Actuator*   MakeActuator(const std::string& str_name);
   virtual CCI_Sensor*     MakeSensor(const std::string& str_name);
   virtual void            Sense();
   virtual void            Act();

   inline Aseba::ThymioInterface* GetInterface() const {
      return ThymioInterface;
   }

private:

   std::vector<CRealThymioDevice*>  m_vecActuators;
   std::vector<CRealThymioDevice*>  m_vecSensors;
};

#endif // REAL_Thymio_H
