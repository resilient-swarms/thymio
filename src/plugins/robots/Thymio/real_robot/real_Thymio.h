#ifndef REAL_Thymio_H
#define REAL_Thymio_H

#include "real_robot.h"
#include <argos3/plugins/robots/Thymio/real_robot/real_Thymio_device.h>
// #include <Thymio/Thymio.h>
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

   inline Aseba::DBusInterface* GetInterface() const {
      return ThymioInterface;
   }

private:

   Aseba::DBusInterface*            ThymioInterface;
   std::vector<CRealThymioDevice*>  m_vecActuators;
   std::vector<CRealThymioDevice*>  m_vecSensors;
};

#endif // REAL_Thymio_H
