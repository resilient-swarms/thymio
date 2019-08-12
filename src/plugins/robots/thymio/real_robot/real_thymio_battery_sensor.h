#ifndef REAL_Thymio_BATTERY_SENSOR_H
#define REAL_Thymio_BATTERY_SENSOR_H

#include <argos3/plugins/robots/generic/control_interface/ci_battery_sensor.h>
#include <argos3/plugins/robots/thymio/real_robot/real_thymio_device.h>

using namespace argos;

class CRealThymioBatterySensor :
   public CCI_BatterySensor,
   public CRealThymioDevice {

public:

   CRealThymioBatterySensor(knet_dev_t* pt_dspic);
   
   virtual ~CRealThymioBatterySensor();

   virtual void Do();
   
};

#endif // REAL_Thymio_BATTERY_SENSOR_H
