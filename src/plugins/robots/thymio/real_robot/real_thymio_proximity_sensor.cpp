#include "real_Thymio_proximity_sensor.h"

/****************************************/
/****************************************/

CRealThymioProximitySensor::CRealThymioProximitySensor(Aseba::ThymioInterface* ThymioInterface) :
   CRealThymioDevice(ThymioInterface) {
}
   
/****************************************/
/****************************************/

CRealThymioProximitySensor::~CRealThymioProximitySensor() {
}

/****************************************/
/****************************************/

void CRealThymioProximitySensor::Do() {

   Aseba::ThymioInterface* Interface = this->GetInterface();
   std::vector<uint16_t> list = (std::vector<uint16_t>)Interface->getVariable("thymio-II", "prox.horizontal");
   for (std::vector<short>::size_type i = 0; i!= list.size(); i++)
   { 
       m_tReadings[i].Value = (short) list[i];
       m_tReadings[i].Value = m_tReadings[i].Value;///4300; //scaling robot's sensor reading to [0,1]
   }

}

/****************************************/
/****************************************/
