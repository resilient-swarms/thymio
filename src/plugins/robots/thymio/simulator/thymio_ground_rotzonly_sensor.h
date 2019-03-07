/**
 * @file <argos3/plugins/robots/thymio/simulator/thymio_ground_rotzonly_sensor.h>
 */

#ifndef Thymio__GROUND_ROTZONLY_SENSOR_H
#define Thymio__GROUND_ROTZONLY_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CThymioGroundRotZOnlySensor;
   class CGroundSensorEquippedEntity;
   class CFloorEntity;
}

#include <argos3/plugins/robots/thymio/control_interface/ci_thymio_ground_sensor.h>
#include <argos3/core/utility/math/range.h>
#include <argos3/core/utility/math/rng.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/sensor.h>

namespace argos {

   class CThymioGroundRotZOnlySensor : public CCI_ThymioGroundSensor,
                                          public CSimulatedSensor {

   public:

      CThymioGroundRotZOnlySensor();

      virtual ~CThymioGroundRotZOnlySensor() {}

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();

      virtual void Reset();

   protected:

      /** Reference to embodied entity associated to this sensor */
      CEmbodiedEntity* m_pcEmbodiedEntity;

      /** Reference to floor entity */
      CFloorEntity* m_pcFloorEntity;

      /** Reference to ground sensor equipped entity associated to this sensor */
      CGroundSensorEquippedEntity* m_pcGroundSensorEntity;

      /** Random number generator */
      CRandom::CRNG* m_pcRNG;

      /** Whether to add noise or not */
      bool m_bAddNoise;

      /** Noise range */
      CRange<Real> m_cNoiseRange;

      /** Reference to the space */
      CSpace& m_cSpace;
   };

}

#endif
