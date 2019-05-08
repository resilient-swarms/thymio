/**
 * @file <argos3/plugins/robots/thymio/simulator/thymio_proximity_default_sensor.h>
 */

#ifndef Thymio_PROXIMITY_DEFAULT_SENSOR_H
#define Thymio_PROXIMITY_DEFAULT_SENSOR_H

#include <string>
#include <map>

namespace argos
{
   class CThymioProximityDefaultSensor;
}

#include <argos3/plugins/robots/thymio/control_interface/ci_thymio_proximity_sensor.h>
#include <argos3/plugins/robots/generic/simulator/proximity_default_sensor.h>

namespace argos
{

   class CThymioProximityDefaultSensor : public CCI_ThymioProximitySensor,
                                            public CSimulatedSensor
   {

   public:

      CThymioProximityDefaultSensor();

      virtual ~CThymioProximityDefaultSensor();

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();

      virtual void Reset();

   private:

      CProximityDefaultSensor* m_pcProximityImpl;

   };

}

#endif
