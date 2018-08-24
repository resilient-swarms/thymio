/* Include the controller definition */
#include "accelerometer_test.h"
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include <argos3/core/utility/math/vector2.h>

#include <unistd.h>

#include <time.h>

#include <sys/time.h>

#include <argos3/core/utility/math/general.h>

/****************************************/
/****************************************/

CAccelerometerTest::CAccelerometerTest() :
   m_pcWheels(NULL),
   m_pcAccelerometer(NULL),
   m_pcLeds(NULL),
   m_cAlpha(10.0f),
   m_fDelta(0.5f),
   m_fWheelVelocity(2.5f),
   m_cGoStraightAngleRange(-ToRadians(m_cAlpha),
                           ToRadians(m_cAlpha)) {}

/****************************************/
/****************************************/

void CAccelerometerTest::Init(TConfigurationNode& t_node) {

   m_pcWheels    = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
   m_pcLeds      = GetActuator<CCI_ThymioLedsActuator          >("thymio_led");
   m_pcAccelerometer = GetSensor<CCI_Thymio_acc_sensor>         ("accelerometer");

   m_tick        = 0;
   std::cout<< m_pcAccelerometer;


   dist = 11;
   timer = 0;
   try {
       acc_sensor_readings.open("acc_sensor_readings.csv");
       acc_sensor_readings<< dist <<"cm";
   } catch (std::exception e) {
       std::cout << e.what();
   }

}

/****************************************/
/****************************************/

void CAccelerometerTest::ControlStep() {
   /*Increase tick*/
    m_tick++;
    timer++;

   char c;
   if( timer % 100 == 0){
       m_pcLeds->SetProxHIntensity({32,32,32,32,32,32,32,32});
       acc_sensor_readings << "\n" << --dist <<"cm";
       acc_sensor_readings.flush();
//       sleep(5);
       std::cin>>c;
       m_pcLeds->SetProxHIntensity({0,0,0,0,0,0,0,0});
       timer = 0;
   }

}

CAccelerometerTest::~CAccelerometerTest(){
    try {
        acc_sensor_readings<<"\n";
        acc_sensor_readings.close();
    } catch (std::exception e) {
        std::cout << e.what();
    }
    m_pcWheels->SetLinearVelocity(0.0f, 0.0f);
}

/****************************************/
/****************************************/

REGISTER_CONTROLLER(CAccelerometerTest, "accelerometer_test_controller")
