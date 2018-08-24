/* Include the controller definition */
#include "accelerometer_test.h"
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include <argos3/core/utility/math/vector2.h>

#include <unistd.h>

#include <argos3/core/utility/rate.h>

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

   m_pcWheels           = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
   m_pcLeds             = GetActuator<CCI_ThymioLedsActuator          >("thymio_led");
   m_pcAccelerometer    = GetSensor  <CCI_Thymio_acc_sensor           >("Thymio_accelerometer");

   std::cout<<"accelerometer: "<<m_pcAccelerometer;

   timer = 0;
   rate = 5;
   try {
       acc_sensor_readings.open("acc_sensor_readings.csv");
   } catch (std::exception e) {
       std::cout << e.what();
   }

}

/****************************************/
/****************************************/

void CAccelerometerTest::ControlStep() {

    std::cout<< "time: "<<timer/rate<<" ";
    std::cout<< m_pcAccelerometer->accValues.x<<" ";
    std::cout<< m_pcAccelerometer->accValues.y<<" ";
    std::cout<< m_pcAccelerometer->accValues.z<<"\n";

    m_pcLeds->SetProxHIntensity({32,32,32,32,32,32,32,32});
    m_pcLeds->SetProxHIntensity({0,0,0,0,0,0,0,0});

    if(timer/rate % 5 == 0){
        m_pcLeds->SetProxHIntensity({32,32,32,32,32,32,32,32});
        m_pcLeds->SetProxHIntensity({0,0,0,0,0,0,0,0});
    }

    if(timer/rate <= 5)
    {
        m_pcWheels->SetLinearVelocity(0,0);
        acc_sensor_readings << timer<<",";
        acc_sensor_readings << m_pcAccelerometer<<",";
    }
    else if(timer/rate<= 15){
        m_pcWheels->SetLinearVelocity(2,-2);
        acc_sensor_readings << timer<<",";
        acc_sensor_readings << m_pcAccelerometer<<",";
    }
    else if(timer/rate<= 20){
        m_pcWheels->SetLinearVelocity(0,0);
        acc_sensor_readings << timer<<",";
        acc_sensor_readings << m_pcAccelerometer<<",";
    }
    else if(timer/rate<= 30){
        m_pcWheels->SetLinearVelocity(-2,2);
        acc_sensor_readings << timer<<",";
        acc_sensor_readings << m_pcAccelerometer<<",";
    }
    else if(timer/rate<= 35){
        m_pcWheels->SetLinearVelocity(0,0);
        acc_sensor_readings << timer<<",";
        acc_sensor_readings << m_pcAccelerometer<<",";
    }

    if(timer/rate == 35)
    {
        char c;
        try {
            acc_sensor_readings<<"\n";
            acc_sensor_readings.close();
            std::cout<< "File is exported! end of the experiment!";
        } catch (std::exception e) {
            std::cout << e.what();
        }
        std::cin>> c;
    }
    timer++;

}

CAccelerometerTest::~CAccelerometerTest(){

    m_pcWheels->SetLinearVelocity(0.0f, 0.0f);
}

/****************************************/
/****************************************/

REGISTER_CONTROLLER(CAccelerometerTest, "accelerometer_test_controller")
