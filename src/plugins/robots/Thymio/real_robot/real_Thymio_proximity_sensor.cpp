#include "real_Thymio_proximity_sensor.h"

/****************************************/
/****************************************/

CRealThymioProximitySensor::CRealThymioProximitySensor(Aseba::DBusInterface* ThymioInterface) :
   CRealThymioDevice(ThymioInterface) {
}
   
/****************************************/
/****************************************/

CRealThymioProximitySensor::~CRealThymioProximitySensor() {
}

/****************************************/
/****************************************/

void CRealThymioProximitySensor::Do() {

   Aseba::DBusInterface* Interface = this->GetInterface();
   QList<qint16> list = Interface->getVariable("thymio-II", "prox.horizontal");
   for( int i=0; i<list.count(); ++i )
   { 
       m_tReadings[i].Value = (short)list[i];
        std::cout<<"Proximity sensro value:"<<std::to_string( m_tReadings[i].Value) <<"\n";
   }

}

/****************************************/
/****************************************/
