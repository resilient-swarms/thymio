#ifndef Thymio_DIFFUSION_H
#define Thymio_DIFFUSION_H

#include <argos3/core/utility/math/angles.h>
#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/Thymio/control_interface/ci_Thymio_leds_actuator.h>
#include <argos3/plugins/robots/Thymio/control_interface/ci_Thymio_acc_sensor.h>
#include <argos3/core/utility/logging/argos_log.h>

#include <iostream>
#include <fstream>

#include <ctime>

using namespace argos;

class CAccelerometerTest : public CCI_Controller {

public:

   /* Class constructor. */
   CAccelerometerTest();

   /* Class destructor. */
   virtual ~CAccelerometerTest();

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
   CCI_Thymio_acc_sensor* m_pcAccelerometer;

   CDegrees m_cAlpha;

   Real m_fDelta;
   /* Wheel speed. */
   Real m_fWheelVelocity;

   /* Angle tolerance range to go straight.
    * It is set to [-alpha,alpha]. */
   CRange<CRadians> m_cGoStraightAngleRange;

   std::ofstream acc_sensor_readings;

   std::clock_t start;
   int timer;
   int rate;

};

#endif
