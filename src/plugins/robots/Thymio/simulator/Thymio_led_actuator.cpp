#include "Thymio_led_actuator.h"
#include <argos3/plugins/simulator/entities/led_equipped_entity.h>

namespace argos{

   /****************************************/
   /****************************************/

   ThymioLedActuator::ThymioLedActuator() :
      m_pcLEDEquippedEntity(NULL) {}

   /****************************************/
   /****************************************/

   void ThymioLedActuator::SetRobot(CComposableEntity& c_entity) {
      m_pcLEDEquippedEntity = &(c_entity.GetComponent<CLEDEquippedEntity>("leds"));
   }

   /****************************************/
   /****************************************/

    void ThymioLedActuator::Init(TConfigurationNode& t_tree) {
         try {
            CCI_ThymioLedsActuator::Init(t_tree);
            m_pcLEDEquippedEntity->Enable();
         }
         catch(CARGoSException& ex) {
            THROW_ARGOSEXCEPTION_NESTED("Error initializing the LEDs default actuator", ex);
         }
    }

    /****************************************/
    /****************************************/

      void ThymioLedActuator::Update() {

      }

      /****************************************/
      /****************************************/

      void ThymioLedActuator::Reset() {

      }

      /****************************************/
      /****************************************/

      void ThymioLedActuator::Destroy() {
         m_pcLEDEquippedEntity->Disable();
      }

      /****************************************/
      /****************************************/

      void ThymioLedActuator::SetProxHIntensity(std::vector<short> intensity){
        for(size_t i=0; i < intensity.size(); ++i)
            m_pcLEDEquippedEntity->SetLEDColor(i,CColor(intensity[i],0,0,255));
      }

      /****************************************/
      /****************************************/

      void ThymioLedActuator::SetProxVIntensity(std::vector<short> intensity){
          for(size_t i=0; i < intensity.size(); ++i)
              m_pcLEDEquippedEntity->SetLEDColor(i,CColor(intensity[i],0,0,255));
      }

      /****************************************/
      /****************************************/

      void ThymioLedActuator::SetProxHIntensity(const CCI_ThymioProximitySensor::TReadings intensity){
          m_pcLEDEquippedEntity->SetLEDColor(0,CColor((short)(intensity[0].Value*4300/32),0,0,255));
          m_pcLEDEquippedEntity->SetLEDColor(1,CColor((short)(intensity[1].Value*4300/32),0,0,255));
          m_pcLEDEquippedEntity->SetLEDColor(2,CColor((short)(intensity[2].Value*4300/32),0,0,255));
          m_pcLEDEquippedEntity->SetLEDColor(3,CColor((short)(intensity[2].Value*4300/32),0,0,255));
          m_pcLEDEquippedEntity->SetLEDColor(4,CColor((short)(intensity[3].Value*4300/32),0,0,255));
          m_pcLEDEquippedEntity->SetLEDColor(5,CColor((short)(intensity[4].Value*4300/32),0,0,255));
          m_pcLEDEquippedEntity->SetLEDColor(6,CColor((short)(intensity[5].Value*4300/32),0,0,255));
          m_pcLEDEquippedEntity->SetLEDColor(7,CColor((short)(intensity[6].Value*4300/32),0,0,255));
      }

      /****************************************/
      /****************************************/

      void ThymioLedActuator::SetProxVIntensity(const CCI_ThymioProximitySensor::TReadings intensity){
          for(size_t i=0; i < intensity.size(); ++i)
              m_pcLEDEquippedEntity->SetLEDColor(i,CColor(intensity[i].Value*100,0,0,255));
      }

      /****************************************/
      /****************************************/

   }

   REGISTER_ACTUATOR(ThymioLedActuator,
                     "thymio_led", "default",
                     "Sina Sarparast [sina.sarparast@gmail.com]",
                     "1.0",
                     "The Thymio LED actuator.",
                     "This actuator controls the LED of the thymio. For a complete description of its\n"
                     "usage, refer to the ci_thymio_led_actuator.h file.\n\n"
                     "REQUIRED XML CONFIGURATION\n\n"
                     "  <controllers>\n"
                     "    ...\n"
                     "    <my_controller ...>\n"
                     "      ...\n"
                     "      <actuators>\n"
                     "        ...\n"
                     "        <thymio_led implementation=\"default\" />\n"
                     "        ...\n"
                     "      </actuators>\n"
                     "      ...\n"
                     "    </my_controller>\n"
                     "    ...\n"
                     "  </controllers>\n\n"
                     "OPTIONAL XML CONFIGURATION\n\n"
                     "None.\n",
                     "Usable"
      );
