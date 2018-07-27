#include "real_Thymio_ground_sensor.h"

/****************************************/
/****************************************/

CRealThymioGroundSensor::CRealThymioGroundSensor(Aseba::DBusInterface* ThymioInterface) :
   CRealThymioDevice(ThymioInterface) {
}
   
/****************************************/
/****************************************/

CRealThymioGroundSensor::~CRealThymioGroundSensor() {
}

/****************************************/
/****************************************/

void CRealThymioGroundSensor::Do() {
    Aseba::DBusInterface* Interface = this->GetInterface();
    QList<qint16> list = Interface->getVariable("thymio-II", "prox.ground.delta");
    for( int i=0; i<list.count(); ++i )
    {
        m_tReadings[i].Value = (short)list[i];
         std::cout<<"*ground sensor value:"<<std::to_string( m_tReadings[i].Value) <<"\n";
    }
}

/****************************************/
/****************************************/
