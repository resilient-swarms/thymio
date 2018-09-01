/* Include the controller definition */
#include "accelerometer_test2.h"
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
   m_fWheelVelocity(20),
   m_cGoStraightAngleRange(-ToRadians(m_cAlpha),
                           ToRadians(m_cAlpha)) {}

/****************************************/
/****************************************/

void CAccelerometerTest::Init(TConfigurationNode& t_node) {

   m_pcWheels           = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
   m_pcLeds             = GetActuator<CCI_ThymioLedsActuator          >("thymio_led");
   m_pcAccelerometer    = GetSensor  <CCI_Thymio_acc_sensor           >("Thymio_accelerometer");

   std::cout<<"accelerometer: "<<m_pcAccelerometer;

   start = std::clock();
   timer = 0;
   rate = 20;
   second = 0.00f;

   try {
       acc_sensor_readings.open("acc_sensor_readings.csv");
   } catch (std::exception e) {
       std::cout << e.what();
   }
   m_pcLeds->SetProxHIntensity({32,32,32,32,32,32,32,32});
   m_pcLeds->SetProxHIntensity({0,0,0,0,0,0,0,0});

}

/****************************************/
/****************************************/

void CAccelerometerTest::ControlStep() {

    std::cout<< m_pcAccelerometer->accValues.x<<" ";
    std::cout<< m_pcAccelerometer->accValues.y<<" ";
    std::cout<< m_pcAccelerometer->accValues.z<<"\n";

    if(timer > second )
    {
        if(second < 10)
        {
            m_pcWheels->SetLinearVelocity(0,0);
        }
        else if(second < 30){
            m_pcWheels->SetLinearVelocity(m_fWheelVelocity,-m_fWheelVelocity);//clockwise
        }
        else if(second < 40){
            m_pcWheels->SetLinearVelocity(0,0);
        }
        else if(second < 60){
            m_pcWheels->SetLinearVelocity(-m_fWheelVelocity,m_fWheelVelocity);//counter clockwise
        }
        else if(second < 70){
            m_pcWheels->SetLinearVelocity(0,0);
        }
        else
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

        second += 1.00f; // means a second has passed add to second to prepare it for next second
        std::cout<<second<<"\t One second passed!!!\n";
    }

    acc_sensor_readings << second<<",";
    acc_sensor_readings << m_pcAccelerometer->accValues.x<<",";
    acc_sensor_readings << m_pcAccelerometer->accValues.y<<",";
    acc_sensor_readings << m_pcAccelerometer->accValues.z<<"\n";

    timer = (( std::clock() - start )*100/(double) CLOCKS_PER_SEC);
//    std::cout<<( std::clock() - start )/(double) CLOCKS_PER_SEC;
    std::cout<<timer<<") ";

}

CAccelerometerTest::~CAccelerometerTest(){

    m_pcWheels->SetLinearVelocity(0.0f, 0.0f);
}

/****************************************/
/****************************************/

REGISTER_CONTROLLER(CAccelerometerTest, "accelerometer_test2_controller")
