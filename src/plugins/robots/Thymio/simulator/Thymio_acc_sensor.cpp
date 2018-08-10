/**
 * @file <argos3/plugins/robots/Thymio/simulator/Thymio__ground_rotzonly_sensor.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/floor_entity.h>
#include <argos3/plugins/simulator/entities/ground_sensor_equipped_entity.h>

#include "Thymio_acc_sensor.h"

namespace argos {

   /****************************************/
   /****************************************/

   static CRange<Real> UNIT(0.0f, 1.0f);

   /****************************************/
   /****************************************/

   CThymioAccSensor::CThymioAccSensor(CComposableEntity* pc_parent,
                                      const std::string& str_id) :
      CComposableEntity(pc_parent, str_id),
      m_pcEmbodiedEntity(NULL),
      m_cWheeledEntity(NULL),
      m_pcRNG(NULL),
      m_bAddNoise(false) {

   }

   /****************************************/
   /****************************************/

   void CThymioAccSensor::SetRobot(CComposableEntity& c_entity) {
      m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
      m_pcThymioAccSensor = &(c_entity.GetComponent<CThymioAccSensor>("accelerometer"));
      m_cWheeledEntity = &(c_entity.GetComponent<CWheeledEntity>("wheels_0"));
   }

   /****************************************/
   /****************************************/

   void CThymioAccSensor::Init(TConfigurationNode& t_tree) {
      try {
         CCI_Thymio_acc_sensor::Init(t_tree);
         /* Parse noise level */
         Real fNoiseLevel = 0.0f;
         GetNodeAttributeOrDefault(t_tree, "noise_level", fNoiseLevel, fNoiseLevel);
         if(fNoiseLevel < 0.0f) {
            THROW_ARGOSEXCEPTION("Can't specify a negative value for the noise level of the Thymio ground sensor");
         }
         else if(fNoiseLevel > 0.0f) {
            m_bAddNoise = true;
            m_cNoiseRange.Set(-fNoiseLevel, fNoiseLevel);
            m_pcRNG = CRandom::CreateRNG("argos");
         }
         this->accValues = {0,0};
         this->acceleration = {0,0,0,0};
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in Thymio rotzonly ground sensor", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CThymioAccSensor::Update() {

       this->acceleration.vx_1 = this->acceleration.vx_2;
       this->acceleration.vx_2 = m_cWheeledEntity->GetWheelVelocity(0);
       this->acceleration.vy_1 = this->acceleration.vy_1;
       this->acceleration.vy_2 = m_cWheeledEntity->GetWheelVelocity(1);

       accValues.x = (short)this->acceleration.getAcceleration()[0];
       accValues.y = (short)this->acceleration.getAcceleration()[1];

         /* Apply noise to the sensor */
         if(m_bAddNoise) {
             this->accValues.x += m_pcRNG->Uniform(m_cNoiseRange);
             this->accValues.y += m_pcRNG->Uniform(m_cNoiseRange);
         }
         /* Clamp the reading between 0 and 1 */
         //UNIT.TruncValue(m_tReadings[i].Value);
      }


   /****************************************/
   /****************************************/

   void CThymioAccSensor::Reset() {
        this->acceleration = {0,0,0,0};
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CThymioAccSensor,
                   "accelerometer", "accelerometer",
                   "sina.sarparast@gmail.com",
                   "1.0",
                   "The Thymio accelerometer.",
                   "This sensor accesses the Thymio  ground sensor. For a complete description\n"
                   "of its usage, refer to the ci_Thymio_ground_sensor.h interface. For the XML\n"
                   "configuration, refer to the default ground sensor.\n",
                   "Usable"
		  );

}

