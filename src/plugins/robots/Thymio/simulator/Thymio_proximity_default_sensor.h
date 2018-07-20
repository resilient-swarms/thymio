/**
 * @file <argos3/plugins/robots/Thymio/simulator/Thymio_proximity_default_sensor.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef Thymio_PROXIMITY_DEFAULT_SENSOR_H
#define Thymio_PROXIMITY_DEFAULT_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CThymioProximityDefaultSensor;
}

#include <argos3/plugins/robots/Thymio/control_interface/ci_Thymio_proximity_sensor.h>
#include <argos3/plugins/robots/generic/simulator/proximity_default_sensor.h>

namespace argos {

   class CThymioProximityDefaultSensor : public CCI_ThymioProximitySensor,
                                            public CSimulatedSensor {

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
