#include "real_Thymio_differential_steering_actuator.h"
#include <argos3/core/utility/logging/argos_log.h>

/****************************************/
/****************************************/

static int Thymio_POSITIONMARGIN             = 20;
static int Thymio_PID_P                      = 10;
static int Thymio_PID_I                      = 5;
static int Thymio_PID_D                      = 1;
static int Thymio_SPEEDPROFILE_ACC_INC       = 3;
static int Thymio_SPEEDPROFILE_ACC_DIV       = 0;
static int Thymio_SPEEDPROFILE_MIN_SPEED_ACC = 20;
static int Thymio_SPEEDPROFILE_MIN_SPEED_DEC = 1;
static int Thymio_SPEEDPROFILE_MAX_SPEED     = 400;

/****************************************/
/****************************************/

CRealThymioDifferentialSteeringActuator::CRealThymioDifferentialSteeringActuator(knet_dev_t* pt_dspic) :
   CRealThymioDevice(pt_dspic) {
   LOG << "[INFO] Differential Steering actuator parameters:" << std::endl;
   kh4_SetPositionMargin(Thymio_POSITIONMARGIN, GetDSPic());
   LOG << "[INFO]   Position Margin = "
       << Thymio_POSITIONMARGIN
       << std::endl;
   kh4_ConfigurePID(Thymio_PID_P,
                    Thymio_PID_I,
                    Thymio_PID_D, GetDSPic());
   LOG << "[INFO]   PID factors = <"
       << Thymio_PID_P << ", "
       << Thymio_PID_I << ", "
       << Thymio_PID_D << ">"
       << std::endl;
   kh4_SetSpeedProfile(Thymio_SPEEDPROFILE_ACC_INC,
                       Thymio_SPEEDPROFILE_ACC_DIV,
                       Thymio_SPEEDPROFILE_MIN_SPEED_ACC,
                       Thymio_SPEEDPROFILE_MIN_SPEED_DEC,
                       Thymio_SPEEDPROFILE_MAX_SPEED,
                       GetDSPic());
   LOG << "[INFO]   Speed profile = <"
       << "acc_inc = "       << Thymio_SPEEDPROFILE_ACC_INC << ", "
       << "acc_div = "       << Thymio_SPEEDPROFILE_ACC_DIV << ", "
       << "min_speed_acc = " << Thymio_SPEEDPROFILE_MIN_SPEED_ACC << ", "
       << "min_speed_dec = " << Thymio_SPEEDPROFILE_MIN_SPEED_DEC << ", "
       << "max_speed = "     << Thymio_SPEEDPROFILE_MAX_SPEED << ">"
       << std::endl;
   kh4_SetMode(kh4RegSpeedProfile, GetDSPic());
}
   
/****************************************/
/****************************************/

CRealThymioDifferentialSteeringActuator::~CRealThymioDifferentialSteeringActuator() {
   kh4_set_speed(0, 0, GetDSPic());
   kh4_SetMode(kh4RegIdle, GetDSPic());
}
   
/****************************************/
/****************************************/

void CRealThymioDifferentialSteeringActuator::Do() {
   kh4_set_speed(m_fCurrentVelocity[0] / KH4_SPEED_TO_MM_S,
                 m_fCurrentVelocity[1] / KH4_SPEED_TO_MM_S,
                 GetDSPic());
}

/****************************************/
/****************************************/

void CRealThymioDifferentialSteeringActuator::SetLinearVelocity(Real f_left_velocity,
                                                                   Real f_right_velocity) {
   m_fCurrentVelocity[0] = f_left_velocity;
   m_fCurrentVelocity[1] = f_right_velocity;
}

/****************************************/
/****************************************/

