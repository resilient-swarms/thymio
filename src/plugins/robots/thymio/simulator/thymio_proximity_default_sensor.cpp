/**
 * @file <argos3/plugins/robots/thymio/simulator/thymio_proximity_default_sensor.cpp>
 */

#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/simulator.h>
#include <argos3/plugins/simulator/entities/proximity_sensor_equipped_entity.h>

#include "thymio_proximity_default_sensor.h"

namespace argos {

/****************************************/
/****************************************/

class CThymioProximitySensorImpl : public CProximityDefaultSensor
{

public:

    virtual void SetRobot(CComposableEntity& c_entity)
    {
        try
        {
            m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
            m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity>("controller"));
            m_pcProximityEntity = &(c_entity.GetComponent<CProximitySensorEquippedEntity>("proximity_sensors[proximity]"));
            m_pcProximityEntity->Enable();
        }
        catch(CARGoSException& ex)
        {
            THROW_ARGOSEXCEPTION_NESTED("Can't set robot for the Thymio proximity default sensor", ex);
        }
    }

    // needs to be modified for Thymio
    virtual Real CalculateReading(Real f_distance) // f_distance is in meters
    {
        std::cout << "Distance = " << f_distance << std::endl;

        Real x, y;
        //if(0<=x && x<=11) // in meters, not cms.
        if(0.0<=f_distance && f_distance<=0.11) // in meters, not cms.
        {
            x = f_distance * 100.0f; // x is in cm
            y = -2.055*x*x*x*x+43.41*x*x*x-292.9*x*x+312.2*x+4362.0;
        }
        else
            y = 0.0;

        std::cout << "y = " << y << std::endl;
        return y/4500.0; // Normalize by approx. max sensor value
    }
};

/****************************************/
/****************************************/

CThymioProximityDefaultSensor::CThymioProximityDefaultSensor() :
    m_pcProximityImpl(new CThymioProximitySensorImpl()) {}

/****************************************/
/****************************************/

CThymioProximityDefaultSensor::~CThymioProximityDefaultSensor()
{
    delete m_pcProximityImpl;
}

/****************************************/
/****************************************/

void CThymioProximityDefaultSensor::SetRobot(CComposableEntity& c_entity)
{
    try
    {
        m_pcProximityImpl->SetRobot(c_entity);
    }
    catch(CARGoSException& ex)
    {
        THROW_ARGOSEXCEPTION_NESTED("Can't set robot for the Thymio proximity default sensor", ex);
    }
}

/****************************************/
/****************************************/

void CThymioProximityDefaultSensor::Init(TConfigurationNode& t_tree)
{
    m_pcProximityImpl->Init(t_tree);

    Real fRange = 0.11f; // in meters
    GetNodeAttributeOrDefault(t_tree, "range", fRange, fRange);
    std::cout << "Range = " << fRange;
}

/****************************************/
/****************************************/

void CThymioProximityDefaultSensor::Update()
{
    m_pcProximityImpl->Update();
    for(size_t i = 0; i < m_pcProximityImpl->GetReadings().size(); ++i)
    {
        m_tReadings[i].Value = m_pcProximityImpl->GetReadings()[i];
    }
}

/****************************************/
/****************************************/

void CThymioProximityDefaultSensor::Reset()
{
    m_pcProximityImpl->Reset();
}

/****************************************/
/****************************************/

REGISTER_SENSOR(CThymioProximityDefaultSensor,
                "Thymio_proximity", "default",
                "",
                "1.0",
                "The Thymio proximity sensor.",
                "This sensor accesses the Thymio proximity sensor. For a complete description\n"
                "of its usage, refer to the ci_Thymio_proximity_sensor.h interface. For the XML\n"
                "configuration, refer to the default proximity sensor.\n",
                "Usable"
                );

}
