#ifndef REAL_Thymio_LEDS_ACTUATOR_H
#define REAL_Thymio_LEDS_ACTUATOR_H

#include <argos3/plugins/robots/generic/control_interface/ci_leds_actuator.h>
#include <argos3/plugins/robots/Thymio/real_robot/real_Thymio_device.h>

using namespace argos;

class CRealThymioLEDsActuator :
   public CCI_LEDsActuator,
   public CRealThymioDevice {

public:

   CRealThymioLEDsActuator(knet_dev_t* pt_dspic);
   
   virtual ~CRealThymioLEDsActuator();

   virtual void Do();
   
};

#endif
