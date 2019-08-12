/* Include the controller definition */
#include "ground_sensor_test.h"
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include <argos3/core/utility/math/vector2.h>

#include <unistd.h>

//#include <time.h>

//#include <sys/time.h>

#include <argos3/core/utility/math/general.h>

/****************************************/
/****************************************/

CGroundSensorTest::CGroundSensorTest() :
   m_pcWheels(NULL),
   m_pcProximity(NULL),
   m_pcGround(NULL),
   m_pcLeds(NULL),
   m_cAlpha(10.0f),
   m_fDelta(0.5f),
   m_fWheelVelocity(2.5f),
   m_cGoStraightAngleRange(-ToRadians(m_cAlpha),
                           ToRadians(m_cAlpha)) {}

/****************************************/
/****************************************/

void CGroundSensorTest::Init(TConfigurationNode& t_node) {

   m_pcWheels    = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
   m_pcLeds      = GetActuator<CCI_ThymioLedsActuator          >("thymio_led");
   m_pcProximity = GetSensor  <CCI_ThymioProximitySensor       >("thymio_proximity"     );
   m_pcGround    = GetSensor  <CCI_ThymioGroundSensor          >("thymio_ground");
   m_tick        = 0;


   timer = 0;
   try {
       sensor_readings.open("ground_sensor_readings.csv");
   } catch (std::exception& e) {
       std::cout << e.what();
   }
   m_pcLeds->SetProxVIntensity({0,0});
   m_pcLeds->SetProxHIntensity({0,0,0,0,0,0,0,0});

}

/****************************************/
/****************************************/

void CGroundSensorTest::ControlStep() {
   /*Increase tick*/
    m_tick++;
    timer++;

   /* Get readings from ground sensor */
   const CCI_ThymioGroundSensor::TReadings& tGroundReads = m_pcGround->GetReadings();

   std::cout<<m_tick<<") ";
   std::cout<< "Ground sensor left: "<< tGroundReads[0] <<"\n";
   std::cout<< "Ground sensor right: "<< tGroundReads[1] <<"\n";

   left_ground_sensor_readings.push_back( tGroundReads[0].Value );
   right_ground_sensor_readings.push_back( tGroundReads[1].Value );


   if( timer % 100 == 0){
       char str [80];
       m_pcLeds->SetProxHIntensity({32,32,32,32,32,32,32,32});
       std::cout<< "Please enter the name of this section of the experiment: ";

       scanf ("%s",str);
       sensor_readings<<"left sensor,right sensor, "<<str<<"\n";


       /* Save readings to file*/
//       sensor_readings<<"left sensor";
       for(size_t i=0; i<=left_ground_sensor_readings.size();i++)
        {
           sensor_readings<<","<<left_ground_sensor_readings[i];
           sensor_readings<<","<<right_ground_sensor_readings[i];
           sensor_readings<<"\n";
       }

       left_ground_sensor_readings.clear();
       right_ground_sensor_readings.clear();

       sensor_readings<<"\n";
       sensor_readings.flush();


       m_pcLeds->SetProxHIntensity({0,0,0,0,0,0,0,0});
        timer = 0;
   }
//   timer++;


//   m_pcWheels->SetLinearVelocity(0,0);
}

CGroundSensorTest::~CGroundSensorTest(){
    try {
        sensor_readings.flush();
        sensor_readings.close();
    } catch (std::exception& e) {
        std::cout << e.what();
    }
    m_pcLeds->SetProxHIntensity({0,0,0,0,0,0,0,0});
    m_pcWheels->SetLinearVelocity(0.0f, 0.0f);
}

/****************************************/
/****************************************/

REGISTER_CONTROLLER(CGroundSensorTest, "ground_sensor_test_controller")
