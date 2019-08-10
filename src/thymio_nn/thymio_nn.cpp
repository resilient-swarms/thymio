/* Include the controller definition */
#include "thymio_nn.h"
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include "nn_loader.h"

/****************************************/
/****************************************/

CThymioNN::CThymioNN() :
   m_sWheelTurningParams(),
   m_pcLeds(NULL),
   m_pcWheels(NULL),
   m_pcProximity(NULL),
   m_pcGround(NULL),
   m_fLeftSpeed(0.0f),
   m_fRightSpeed(0.0f)
   {
   }

/****************************************/
/****************************************/

void CThymioNN::SWheelTurningParams::Init(TConfigurationNode &t_node)
{
    try
    {
        GetNodeAttribute(t_node, "max_speed", MaxSpeed);
    }
    catch(CARGoSException& ex)
        THROW_ARGOSEXCEPTION_NESTED("Error initializing controller wheel turning parameters.", ex)
}

/****************************************/
/****************************************/

void CThymioNN::Init(TConfigurationNode& t_node)
{
    m_pcLeds = GetActuator<CCI_ThymioLedsActuator>("thymio_led");
    m_pcWheels = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
    m_pcProximity = GetSensor<CCI_ThymioProximitySensor>("Thymio_proximity");
    m_pcGround = GetSensor<CCI_ThymioGroundSensor>("Thymio_ground");

    Reset();

    /* Wheel turning */
    m_sWheelTurningParams.Init(GetNode(t_node, "wheel_turning"));

    nn = nn_loader::Load();
    nn.init();
}

/****************************************/
/****************************************/

void CThymioNN::ControlStep()
{
    /* Get readings from proximity sensor */
    const CCI_ThymioProximitySensor::TReadings& tProxReads = m_pcProximity->GetReadings();
    /* Get readings from ground sensor */
    //const CCI_ThymioGroundSensor::TReadings& tGroundReads = m_pcGround->GetReadings();

    m_pcLeds->SetProxHIntensity(tProxReads);

    inputs = InputStep();
    nn.step(inputs);
    nn.get_outf();

    m_fLeftSpeed = m_sWheelTurningParams.MaxSpeed * nn.get_outf()[0];
    m_fRightSpeed = m_sWheelTurningParams.MaxSpeed * nn.get_outf()[1];

    m_pcWheels->SetLinearVelocity(m_fLeftSpeed,m_fRightSpeed);
}

CThymioNN::~CThymioNN()
{
    m_pcWheels->SetLinearVelocity(0.0f, 0.0f);
}

std::vector<float> CThymioNN::InputStep()
{
    std::vector<Real> readings = GetNormalizedSensorReadings();
    std::vector<float> in = std::vector<float>(readings.begin(), readings.end());
    in.push_back(+1.0); //Bias input

    return in;
}

std::vector<Real> CThymioNN::GetNormalizedSensorReadings()
{

    std::vector<Real> norm_readings;
    /* Get readings from proximity sensor */
    const CCI_ThymioProximitySensor::TReadings& tProxReads = m_pcProximity->GetReadings();
    for(UInt8 i = 0; i < tProxReads.size(); ++i)
        norm_readings.push_back((1.0f - tProxReads[i].Value) * 2.0f - 1.0f);

    /* Get readings from ground sensor */
    const CCI_ThymioGroundSensor::TReadings& tGroundReads = m_pcGround->GetReadings();
    for(UInt8 i = 0; i < tGroundReads.size(); ++i)
        norm_readings.push_back((1.0f - tGroundReads[i].Value) * 2.0f - 1.0f);

    return norm_readings;
}

/****************************************/
/****************************************/

REGISTER_CONTROLLER(CThymioNN, "thymio_nn_controller")
