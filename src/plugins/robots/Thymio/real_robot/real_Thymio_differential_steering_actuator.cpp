#include "real_Thymio_differential_steering_actuator.h"
#include <argos3/core/utility/logging/argos_log.h>

/****************************************/
/****************************************/

CRealThymioDifferentialSteeringActuator::CRealThymioDifferentialSteeringActuator(Aseba::DBusInterface* ThymioInterface) :
   CRealThymioDevice(ThymioInterface) {

}
   
/****************************************/
/****************************************/

CRealThymioDifferentialSteeringActuator::~CRealThymioDifferentialSteeringActuator() {
  Aseba::DBusInterface* Interface = this->GetInterface();
  Interface->setVariable("thymio-II", "motor.left.target", Values({0}));
  Interface->setVariable("thymio-II", "motor.right.target", Values({0}));
}
   
/****************************************/
/****************************************/

void CRealThymioDifferentialSteeringActuator::Do() {
   // kh4_set_speed(m_fCurrentVelocity[0] / KH4_SPEED_TO_MM_S,
   //               m_fCurrentVelocity[1] / KH4_SPEED_TO_MM_S,
   //               GetDSPic());
  // Aseba::DBusInterface* Interface = this->GetInterface();
  // Interface->setVariable("thymio-II", "motor.left.target", m_fCurrentVelocity[0] );
  // Interface->setVariable("thymio-II", "motor.right.target", m_fCurrentVelocity[1] );
}

/****************************************/
/****************************************/

void CRealThymioDifferentialSteeringActuator::SetLinearVelocity(Real f_left_velocity,
                                                                   Real f_right_velocity) {
   // m_fCurrentVelocity[0] = f_left_velocity;
   // m_fCurrentVelocity[1] = f_right_velocity;
  Aseba::DBusInterface* Interface = this->GetInterface();
  Interface->setVariable("thymio-II", "motor.left.target",  {(signed short)f_left_velocity } );
  Interface->setVariable("thymio-II", "motor.right.target", {(signed short)f_right_velocity} );
}

/****************************************/
/****************************************/

