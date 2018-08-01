/* Include the controller definition */
#include "sensor_test.h"
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include <argos3/core/utility/math/vector2.h>

/****************************************/
/****************************************/

CSensorTest::CSensorTest() :
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

void CSensorTest::Init(TConfigurationNode& t_node) {

   m_pcWheels    = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
   m_pcLeds      = GetActuator<CCI_ThymioLedsActuator          >("thymio_led");
   m_pcProximity = GetSensor  <CCI_ThymioProximitySensor       >("Thymio_proximity"     );
   m_pcGround    = GetSensor  <CCI_ThymioGroundSensor          >("Thymio_ground");

}

/****************************************/
/****************************************/

void CSensorTest::ControlStep() {

   /* Get readings from proximity sensor */
   const CCI_ThymioProximitySensor::TReadings& tProxReads = m_pcProximity->GetReadings();
   /* Get readings from ground sensor */
   const CCI_ThymioGroundSensor::TReadings& tGroundReads = m_pcGround->GetReadings();

   m_pcLeds->SetProxHIntensity(tProxReads);

//   LOG << tGroundReads;
   std::cout<< "Ground 1 "<< tGroundReads[0]<<"\n";
   std::cout<< "Ground 2 "<< tGroundReads[1]<<"\n";
   std::cout<< "proximity :"<<tProxReads;

   m_pcWheels->SetLinearVelocity(0,0);

}

CSensorTest::~CSensorTest(){
    m_pcWheels->SetLinearVelocity(0.0f, 0.0f);
}

/****************************************/
/****************************************/

REGISTER_CONTROLLER(CSensorTest, "sensor_test_controller")
