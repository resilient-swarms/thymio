#ifndef REAL_Thymio_DIFFERENTIAL_STEERING_ACTUATOR_H
#define REAL_Thymio_DIFFERENTIAL_STEERING_ACTUATOR_H

#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/thymio/real_robot/real_thymio_device.h>
#include <aseba/switches/asebacppapi/thymio_interface.h>

using namespace argos;

class CRealThymioDifferentialSteeringActuator :
   public CCI_DifferentialSteeringActuator,
   public CRealThymioDevice {

public:

   CRealThymioDifferentialSteeringActuator(Aseba::ThymioInterface* ThymioInterface);
   
   virtual ~CRealThymioDifferentialSteeringActuator();

   virtual void Do();
   
   virtual void SetLinearVelocity(Real f_left_velocity,
                                  Real f_right_velocity);
};

#endif
