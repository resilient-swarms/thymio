#ifndef REAL_Thymio_LEDS_ACTUATOR_H
#define REAL_Thymio_LEDS_ACTUATOR_H

#include <argos3/plugins/robots/generic/control_interface/ci_leds_actuator.h>
#include <argos3/plugins/robots/Thymio/real_robot/real_Thymio_device.h>
#include "dbusinterface.h"

using namespace argos;

class CRealThymioLEDsActuator :
   public CCI_LEDsActuator,
   public CRealThymioDevice {

public:

   CRealThymioLEDsActuator(Aseba::DBusInterface* ThymioInterface);
   
   virtual ~CRealThymioLEDsActuator();

   virtual void Do();

   virtual void SetLed(Real brightness);
   
};

#endif
