#ifndef REAL_Thymio_LEDS_ACTUATOR_H
#define REAL_Thymio_LEDS_ACTUATOR_H

#include <argos3/plugins/robots/Thymio/control_interface/ci_Thymio_leds_actuator.h>
#include <argos3/plugins/robots/Thymio/real_robot/real_Thymio_device.h>
#include "dbusinterface.h"
#include <QtDBus/QtDBus>

using namespace argos;

class CRealThymioLEDsActuator :
   public CCI_ThymioLedsActuator,
   public CRealThymioDevice {

public:

   CRealThymioLEDsActuator(Aseba::DBusInterface* ThymioInterface);
   
   virtual ~CRealThymioLEDsActuator();

   virtual void Do();

   virtual void SetProxHIntensity(std::vector<short> intensity);

   virtual void SetProxVIntensity(std::vector<short> intensity);

   virtual void SetProxHIntensity(const CCI_ThymioProximitySensor::TReadings intensity);

   virtual void SetProxVIntensity(const CCI_ThymioProximitySensor::TReadings intensity);
   
};

#endif
