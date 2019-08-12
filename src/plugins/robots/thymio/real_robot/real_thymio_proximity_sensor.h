#ifndef REAL_Thymio_PROXIMITY_SENSOR_H
#define REAL_Thymio_PROXIMITY_SENSOR_H

#include <argos3/plugins/robots/thymio/control_interface/ci_thymio_proximity_sensor.h>
#include <argos3/plugins/robots/thymio/real_robot/real_thymio_device.h>
#include <aseba/switches/asebacppapi/thymio_interface.h>

using namespace argos;

class CRealThymioProximitySensor :
   public CCI_ThymioProximitySensor,
   public CRealThymioDevice {


public:

   CRealThymioProximitySensor(Aseba::ThymioInterface* ThymioInterface);
   
   virtual ~CRealThymioProximitySensor();

   virtual void Do();

};

#endif // REAL_Thymio_PROXIMITY_SENSOR_H
