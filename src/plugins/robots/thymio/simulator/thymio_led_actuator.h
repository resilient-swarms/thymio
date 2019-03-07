#ifndef THYMIO_LED_ACTUATOR_H
#define THYMIO_LED_ACTUATOR_H

namespace argos{
    class ThymioLedActuator;
}

#include <argos3/core/simulator/actuator.h>
#include <argos3/plugins/robots/thymio/control_interface/ci_thymio_leds_actuator.h>
#include <argos3/plugins/simulator/entities/led_equipped_entity.h>

namespace argos {
    class ThymioLedActuator : public CSimulatedActuator,
                              public CCI_ThymioLedsActuator{
    public:
        ThymioLedActuator();

        virtual ~ThymioLedActuator() {}

        virtual void SetRobot(CComposableEntity& c_entity);

        virtual void SetProxHIntensity(std::vector<short> intensity);

        virtual void SetProxVIntensity(std::vector<short> intensity);

        virtual void SetProxHIntensity(const CCI_ThymioProximitySensor::TReadings intensity);

        virtual void SetProxVIntensity(const CCI_ThymioProximitySensor::TReadings intensity);

        virtual void Init(TConfigurationNode& t_tree);
        virtual void Update();
        virtual void Reset();
        virtual void Destroy();

    private:

          CLEDEquippedEntity* m_pcLEDEquippedEntity;

    };
}

#endif // THYMIO_LED_ACTUATOR_H
