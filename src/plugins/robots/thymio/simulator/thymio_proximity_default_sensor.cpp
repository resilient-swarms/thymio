/**
 * @file <argos3/plugins/robots/thymio/simulator/thymio_proximity_default_sensor.cpp>
 */

#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/simulator.h>
#include <argos3/plugins/simulator/entities/proximity_sensor_equipped_entity.h>

#include "thymio_proximity_default_sensor.h"

namespace argos
{

/****************************************/
/****************************************/

class CThymioProximitySensorImpl : public CProximityDefaultSensor
{

public:
    /* range of the sensors */
    Real f_range;

    virtual void SetRobot(CComposableEntity &c_entity)
    {
        try
        {
            m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
            m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity>("controller"));
            m_pcProximityEntity = &(c_entity.GetComponent<CProximitySensorEquippedEntity>("proximity_sensors[proximity]"));
            m_pcProximityEntity->Enable();
        }
        catch (CARGoSException &ex)
        {
            THROW_ARGOSEXCEPTION_NESTED("Can't set robot for the Thymio proximity default sensor", ex);
        }
    }

    // needs to be modified for Thymio
    virtual Real CalculateReading(Real f_distance) // f_distance is in meters
    {
        //std::cout << "Distance = " << f_distance << " meters " << std::endl;

        Real x, y;
        //if(0<=x && x<=11) // in meters, not cms.
        if (0.0 <= f_distance && f_distance <= f_range) // in meters, not cms.
        {
            x = f_distance * 100.0f; // x is in cm
            //std::cout << "distance in centimeters = " << x << std::endl;
            x *= 0.11 / f_range; // convert the f_range back to the original 0.11m scale of the real-life thymio observations
            //std::cout << "scaled distance = " << x << std::endl;
            //y = -2.055*x*x*x*x+43.41*x*x*x-292.9*x*x+312.2*x+4362.0;
            y = -40.0 * x * x + 40 * x + 4400.0; // remove unnecessary non-linearities, maintain similar range and shape (has y=0 at x=11)
        }
        else
            y = 0.0;
        
        //std::cout << "y before normalisation = " << y << std::endl;
        y /= 4400.0; // Normalize by max sensor value
        //std::cout << "y after normalisation = " << y << std::endl;
        return y;
    }
};

/****************************************/
/****************************************/

CThymioProximityDefaultSensor::CThymioProximityDefaultSensor() : m_pcProximityImpl(new CThymioProximitySensorImpl())
{
}

/****************************************/
/****************************************/

CThymioProximityDefaultSensor::~CThymioProximityDefaultSensor()
{
    delete m_pcProximityImpl;
}

/****************************************/
/****************************************/

void CThymioProximityDefaultSensor::SetRobot(CComposableEntity &c_entity)
{
    try
    {
        m_pcProximityImpl->SetRobot(c_entity);
    }
    catch (CARGoSException &ex)
    {
        THROW_ARGOSEXCEPTION_NESTED("Can't set robot for the Thymio proximity default sensor", ex);
    }
}

/****************************************/
/****************************************/

void CThymioProximityDefaultSensor::Init(TConfigurationNode &t_tree)
{
    m_pcProximityImpl->Init(t_tree);

    Real fRange = 0.11f; // in meters
    GetNodeAttributeOrDefault(t_tree, "range", dynamic_cast<CThymioProximitySensorImpl *>(m_pcProximityImpl)->f_range, fRange);
    //std::cout << "Range = " << dynamic_cast<CThymioProximitySensorImpl *>(m_pcProximityImpl)->f_range;
} // namespace argos

/****************************************/
/****************************************/

void CThymioProximityDefaultSensor::Update()
{
    m_pcProximityImpl->Update();
    for (size_t i = 0; i < m_pcProximityImpl->GetReadings().size(); ++i)
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
                "Usable");
} // namespace argos
