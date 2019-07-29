#ifndef REAL_Thymio_ACC_SENSOR_H
#define REAL_Thymio_ACC_SENSOR_H

#include <argos3/plugins/robots/thymio/control_interface/ci_thymio_acc_sensor.h>
#include <argos3/plugins/robots/thymio/real_robot/real_thymio_device.h>

using namespace argos;

class CRealThymioAccSensor :
   public CCI_Thymio_acc_sensor,
   public CRealThymioDevice {

public:

   CRealThymioAccSensor(Aseba::ThymioInterface* ThymioInterface);
   
   virtual ~CRealThymioAccSensor();

   virtual void Do();
   
};

#endif // REAL_Thymio_acc_SENSOR_H
