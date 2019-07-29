#ifndef Thymio_DIFFUSION_H
#define Thymio_DIFFUSION_H

#include <argos3/core/utility/math/angles.h>
#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/thymio/control_interface/ci_thymio_leds_actuator.h>
#include <argos3/plugins/robots/thymio/control_interface/ci_thymio_proximity_sensor.h>
#include <argos3/plugins/robots/thymio/control_interface/ci_thymio_ground_sensor.h>
#include <argos3/core/utility/logging/argos_log.h>

#include <iostream>
#include <fstream>

using namespace argos;

class CSensorTest : public CCI_Controller {

public:

   /* Class constructor. */
   CSensorTest();

   /* Class destructor. */
   virtual ~CSensorTest();

   virtual void Init(TConfigurationNode& t_node);

   virtual void ControlStep();

   virtual void Reset() {}

   virtual void Destroy(){}

private:
   /* Pointer to the LEDs */
   CCI_ThymioLedsActuator*   m_pcLeds;
   /* Pointer to the differential steering actuator */
   CCI_DifferentialSteeringActuator* m_pcWheels;
   /* Pointer to the Thymio proximity sensor */
   CCI_ThymioProximitySensor* m_pcProximity;
   /* Pointer to the Thymio ground sensors */
   CCI_ThymioGroundSensor* m_pcGround;

   CDegrees m_cAlpha;

   Real m_fDelta;
   /* Wheel speed. */
   Real m_fWheelVelocity;

   /*Simulator tick*/
   Real m_tick;

   /* Angle tolerance range to go straight.
    * It is set to [-alpha,alpha]. */
   CRange<CRadians> m_cGoStraightAngleRange;

   std::ofstream sensor_readings;

   int timer;
   int dist;

};

#endif
