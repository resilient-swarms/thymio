#include "real_thymio_ground_sensor.h"

/****************************************/
/****************************************/

CRealThymioGroundSensor::CRealThymioGroundSensor(Aseba::ThymioInterface* ThymioInterface) :
   CRealThymioDevice(ThymioInterface) {
}
   
/****************************************/
/****************************************/

CRealThymioGroundSensor::~CRealThymioGroundSensor() {
}

/****************************************/
/****************************************/

void CRealThymioGroundSensor::Do() {
    Aseba::ThymioInterface* Interface = this->GetInterface();
    std::vector<uint16_t> list = (std::vector<uint16_t>) Interface->getVariable("thymio-II", "prox.ground.delta");
    for(std::vector<short>::size_type i=0; i<list.size(); ++i )
    {
        m_tReadings[i].Value = (short)list[i];
//         std::cout<<"*ground sensor value:"<<std::to_string( m_tReadings[i].Value) <<"\n";
    }
}

/****************************************/
/****************************************/
