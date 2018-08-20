#include "real_Thymio.h"
#include "real_Thymio_differential_steering_actuator.h"
#include "real_Thymio_leds_actuator.h"
#include "real_Thymio_ground_sensor.h"
#include "real_Thymio_proximity_sensor.h"

/****************************************/
/****************************************/

CRealThymio::CRealThymio()
{
}

/****************************************/
/****************************************/

CRealThymio::~CRealThymio() {
}

/****************************************/
/****************************************/

void CRealThymio::InitRobot() {
   /* Initialize Thymio */

    /*
     * get connection to Thymio
     */
    const std::string& target = "ser:name=Thymio-II";

    try{
       this->ThymioInterface = new Aseba::ThymioInterface(target);
    }
    catch(CARGoSException& e)
    {
       THROW_ARGOSEXCEPTION("Error initializing communication with Thymio Interface");
    }

    this->ThymioInterface->pingNetwork();
    this->ThymioInterface->wait(100);
    this->ThymioInterface->pingNetwork();

    /* Open and pass the events file*/
    try {
        ThymioInterface->load("../../../ScriptDBusThymio.aesl");
    } catch (std::exception ex) {
        THROW_ARGOSEXCEPTION("Can't Open File!!! \"");
    }

   /* Make sure to start from a clean state */
   /* It's weird to call Destroy() here, but all it does is making
    * sure that at this stage the robot has everything switched off */
   //Destroy();
}

/****************************************/
/****************************************/

void CRealThymio::Destroy() {
   /* Stop wheels */
   // kh4_set_speed(0, 0, m_ptDSPic);
   // kh4_SetMode(kh4RegIdle, m_ptDSPic );
   // /* Switch LEDs off */
   // kh4_SetRGBLeds(0,0,0,0,0,0,0,0,0, m_ptDSPic);
   // /* Switch ultrasound sensor off */
   // kh4_activate_us(0, m_ptDSPic);
    ThymioInterface->setVariable("thymio-II", "motor.left.target",  {0} );
    ThymioInterface->setVariable("thymio-II", "motor.right.target", {0} );
}

/****************************************/
/****************************************/

#define MAKE_ACTUATOR(CLASSNAME, TAG)                            \
   if(str_name == TAG) {                                         \
      CLASSNAME* pcAct =                                         \
         new CLASSNAME(GetInterface());                              \
      m_vecActuators.push_back(pcAct);                           \
      m_pcController->AddActuator(TAG, pcAct);                   \
      LOG << "[INFO] Initialized actuator " << TAG << std::endl; \
      return pcAct;                                              \
   }

CCI_Actuator* CRealThymio::MakeActuator(const std::string& str_name) {
   MAKE_ACTUATOR(CRealThymioDifferentialSteeringActuator,
                 "differential_steering");
    MAKE_ACTUATOR(CRealThymioLEDsActuator,
                  "thymio_led");
   return NULL;
}

/****************************************/
/****************************************/

#define MAKE_SENSOR(CLASSNAME, TAG)                             \
   if(str_name == TAG) {                                        \
      CLASSNAME* pcSens =                                       \
         new CLASSNAME(GetInterface());                             \
      m_vecSensors.push_back(pcSens);                           \
      m_pcController->AddSensor(TAG, pcSens);                   \
      LOG << "[INFO] Initialized sensor " << TAG << std::endl;  \
      return pcSens;                                            \
   }

CCI_Sensor* CRealThymio::MakeSensor(const std::string& str_name) {
   // MAKE_SENSOR(CRealThymioBatterySensor,
   //             "Thymio_battery");
   MAKE_SENSOR(CRealThymioGroundSensor,
                "Thymio_ground");
   // MAKE_SENSOR(CRealThymioLIDARSensor,
   //             "Thymio_lidar");
   MAKE_SENSOR(CRealThymioProximitySensor,
               "Thymio_proximity");
   // MAKE_SENSOR(CRealThymioUltrasoundSensor,
   //             "Thymio_ultrasound");
   return NULL;
}

/****************************************/
/****************************************/

void CRealThymio::Sense() {
   for(size_t i = 0; i < m_vecSensors.size(); ++i) {
      m_vecSensors[i]->Do();
   }
}

/****************************************/
/****************************************/

void CRealThymio::Act() {
   for(size_t i = 0; i < m_vecActuators.size(); ++i) {
      m_vecActuators[i]->Do();
   }
}

/****************************************/
/****************************************/
