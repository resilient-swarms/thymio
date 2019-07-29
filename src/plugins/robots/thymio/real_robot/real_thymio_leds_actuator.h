#ifndef REAL_Thymio_LEDS_ACTUATOR_H
#define REAL_Thymio_LEDS_ACTUATOR_H

#include <argos3/plugins/robots/thymio/control_interface/ci_thymio_leds_actuator.h>
#include <argos3/plugins/robots/thymio/real_robot/real_thymio_device.h>
#include <aseba/switches/asebacppapi/thymio_interface.h>

using namespace argos;

class CRealThymioLEDsActuator :
   public CCI_ThymioLedsActuator,
   public CRealThymioDevice {

public:

   CRealThymioLEDsActuator(Aseba::ThymioInterface* ThymioInterface);
   
   virtual ~CRealThymioLEDsActuator();

   virtual void Do();
   
   virtual void SetColor(CColor led_rgb_color);

   virtual void SetColors(std::vector<CColor> led_rgb_colors);

   virtual void SetProxHIntensity(std::vector<short> intensity);

   virtual void SetProxVIntensity(std::vector<short> intensity);

   virtual void SetProxHIntensity(const CCI_ThymioProximitySensor::TReadings intensity);

   virtual void SetProxVIntensity(const CCI_ThymioProximitySensor::TReadings intensity);
   
};

#endif
