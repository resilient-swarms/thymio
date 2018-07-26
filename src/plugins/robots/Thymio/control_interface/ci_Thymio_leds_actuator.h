#ifndef CI_THYMIO_LEDS_ACTUATOR_H
#define CI_THYMIO_LEDS_ACTUATOR_H

#include <argos3/core/control_interface/ci_actuator.h>

namespace argos {
   class CCI_ThymioLedActuator : CCI_Actuator{
       virtual void SetColor(int index, int value);
   };
}

#endif // CI_THYMIO_LEDS_ACTUATOR_H
