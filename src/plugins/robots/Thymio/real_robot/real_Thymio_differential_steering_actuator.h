#ifndef REAL_Thymio_DIFFERENTIAL_STEERING_ACTUATOR_H
#define REAL_Thymio_DIFFERENTIAL_STEERING_ACTUATOR_H

#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/Thymio/real_robot/real_Thymio_device.h>

using namespace argos;

class CRealThymioDifferentialSteeringActuator :
   public CCI_DifferentialSteeringActuator,
   public CRealThymioDevice {

public:

   CRealThymioDifferentialSteeringActuator(knet_dev_t* pt_dspic);
   
   virtual ~CRealThymioDifferentialSteeringActuator();

   virtual void Do();
   
   virtual void SetLinearVelocity(Real f_left_velocity,
                                  Real f_right_velocity);
};

#endif
