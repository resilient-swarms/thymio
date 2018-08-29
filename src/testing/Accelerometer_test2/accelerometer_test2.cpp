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

   start = std::clock();
   timer = 0;
   rate = 20;
   try {
       acc_sensor_readings.open("acc_sensor_readings.csv");
   } catch (std::exception e) {
       std::cout << e.what();
   }

}

/****************************************/
/****************************************/

void CAccelerometerTest::ControlStep() {

//    std::cout<< "time: "<<timer/rate<<" ";
    std::cout<< m_pcAccelerometer->accValues.x<<" ";
    std::cout<< m_pcAccelerometer->accValues.y<<" ";
    std::cout<< m_pcAccelerometer->accValues.z<<"\n";

    m_pcLeds->SetProxHIntensity({32,32,32,32,32,32,32,32});
    m_pcLeds->SetProxHIntensity({0,0,0,0,0,0,0,0});

    if(timer == 0){
        m_pcLeds->SetProxHIntensity({32,32,32,32,32,32,32,32});
        m_pcLeds->SetProxHIntensity({0,0,0,0,0,0,0,0});
    }

    if(timer < 10)
    {
        m_pcWheels->SetLinearVelocity(0,0);
        acc_sensor_readings << timer<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.x<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.y<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.z<<"\n";

    }
    else if(timer < 30){
        m_pcWheels->SetLinearVelocity(2,-2);
        acc_sensor_readings << timer<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.x<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.y<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.z<<"\n";
    }
    else if(timer < 40){
        m_pcWheels->SetLinearVelocity(0,0);
        acc_sensor_readings << timer<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.x<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.y<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.z<<"\n";
    }
    else if(timer < 60){
        m_pcWheels->SetLinearVelocity(-2,2);
        acc_sensor_readings << timer<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.x<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.y<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.z<<"\n";
    }
    else if(timer < 70){
        m_pcWheels->SetLinearVelocity(0,0);
        acc_sensor_readings << timer<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.x<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.y<<",";
        acc_sensor_readings << m_pcAccelerometer->accValues.z<<"\n";
    }

    if(timer == 70)
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

    //total running time is 70sec we have 5 readings each second it is worst that proximity sensors cause they are
    //updated almost 5 times a second (16Hz)
    timer = (int)(( std::clock() - start )*100/(double) CLOCKS_PER_SEC);
//    std::cout<<( std::clock() - start )/(double) CLOCKS_PER_SEC;
    std::cout<<timer<<") ";

}

CAccelerometerTest::~CAccelerometerTest(){

    m_pcWheels->SetLinearVelocity(0.0f, 0.0f);
}

/****************************************/
/****************************************/

REGISTER_CONTROLLER(CAccelerometerTest, "accelerometer_test2_controller")
