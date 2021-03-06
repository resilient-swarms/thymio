/**
 * @file <argos3/plugins/robots/thymio/simulator/thymio__ground_rotzonly_sensor.h>
 */

#ifndef Thymio_ACC_SENSOR_H
#define Thymio_ACC_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CThymioAccSensor;
}

#include <argos3/plugins/robots/thymio/control_interface/ci_thymio_acc_sensor.h>
#include <argos3/core/utility/math/range.h>
#include <argos3/core/utility/math/rng.h>
#include <argos3/core/simulator/sensor.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/plugins/robots/thymio/simulator/dynamics2d_thymio_model.h>
#include <argos3/plugins/simulator/entities/wheeled_entity.h>

namespace argos {

   class CThymioAccSensor : public CCI_Thymio_acc_sensor,
                            public CSimulatedSensor{

   public:
       struct Acceleration{
           Real vx_1,vx_2;
           Real vy_1,vy_2;
           Real DeltaT;

           std::vector<Real> getAcceleration(){
               return {(vx_1 - vx_2)/DeltaT,(vy_1 - vy_2)/DeltaT};
           }
       } acceleration;

   public:

      CThymioAccSensor();

      virtual ~CThymioAccSensor() {}

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();

      virtual void Reset();

   protected:

      CThymioAccSensor* m_pcThymioAccSensor;

      /** Reference to embodied entity associated to this sensor */
      CEmbodiedEntity* m_pcEmbodiedEntity;

      /** Random number generator */
      CRandom::CRNG* m_pcRNG;

      /** Whether to add noise or not */
      bool m_bAddNoise;

      /** Noise range */
      CRange<Real> m_cNoiseRange;

      /** wheel **/
      CWheeledEntity* m_cWheeledEntity;


   };

}

#endif
