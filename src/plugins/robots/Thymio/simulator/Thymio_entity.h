/**
 * @file <argos3/plugins/robots/Thymio/simulator/Thymio_entity.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef Thymio_ENTITY_H
#define Thymio_ENTITY_H

namespace argos {
   class CBatteryEquippedEntity;
   class CControllableEntity;
   class CEmbodiedEntity;
   class CThymioEntity;
   class CGroundSensorEquippedEntity;
   class CLEDEquippedEntity;
   class CProximitySensorEquippedEntity;
}

#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/plugins/simulator/entities/wheeled_entity.h>
#include <argos3/plugins/simulator/entities/box_entity.h>

namespace argos {

   class CThymioEntity : public CComposableEntity {

   public:

      ENABLE_VTABLE();

   public:

      CThymioEntity();

      CThymioEntity(const std::string& str_id,
                       const std::string& str_controller_id,
                       const CVector3& c_position = CVector3(),
                       const CQuaternion& c_orientation = CQuaternion(),
                       const std::string& str_bat_model = ""
                       );
      
      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();
      virtual void Destroy();

      virtual void UpdateComponents();

      
      inline CControllableEntity& GetControllableEntity() {
         return *m_pcControllableEntity;
      }

      inline CEmbodiedEntity& GetEmbodiedEntity() {
         return *m_pcEmbodiedEntity;
      }

      inline CGroundSensorEquippedEntity& GetGroundSensorEquippedEntity() {
         return *m_pcGroundSensorEquippedEntity;
      }

      inline CLEDEquippedEntity& GetLEDEquippedEntity() {
         return *m_pcLEDEquippedEntity;
      }

      inline CProximitySensorEquippedEntity& GetProximitySensorEquippedEntity() {
         return *m_pcProximitySensorEquippedEntity;
      }

      inline CWheeledEntity& GetWheeledEntity() {
         return *m_pcWheeledEntity;
      }

      inline CBatteryEquippedEntity& GetBatterySensorEquippedEntity() {
          return *m_pcBatteryEquippedEntity;
      }

      virtual std::string GetTypeDescription() const {
         return "Thymio";
      }

   private:

      void SetLEDPosition();

   private:
      CControllableEntity*            m_pcControllableEntity;
      CEmbodiedEntity*                m_pcEmbodiedEntity;
      CGroundSensorEquippedEntity*    m_pcGroundSensorEquippedEntity;
      CLEDEquippedEntity*             m_pcLEDEquippedEntity;
      CProximitySensorEquippedEntity* m_pcProximitySensorEquippedEntity;
      CWheeledEntity*                 m_pcWheeledEntity;
      CBatteryEquippedEntity*         m_pcBatteryEquippedEntity;
   };

}

#endif
