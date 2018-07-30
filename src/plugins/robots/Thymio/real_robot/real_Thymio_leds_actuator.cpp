#include "real_Thymio_leds_actuator.h"

/****************************************/
/****************************************/

CRealThymioLEDsActuator::CRealThymioLEDsActuator(Aseba::DBusInterface* ThymioInterface) :
   CRealThymioDevice(ThymioInterface) {
}
   
/****************************************/
/****************************************/

CRealThymioLEDsActuator::~CRealThymioLEDsActuator() {
    Aseba::DBusInterface* Interface = this->GetInterface();
    Interface->setVariable("Thymio-II","leds.prox.h",{0});
}
   
/****************************************/
/****************************************/


void CRealThymioLEDsActuator::Do() {

}

/****************************************/
/****************************************/

void CRealThymioLEDsActuator::SetProxHIntensity(std::vector<short> intensity){
    Aseba::DBusInterface* Interface = this->GetInterface();
     Interface->sendEventName("ProxHLeds",{intensity[0],
                                           intensity[1],
                                           intensity[2],
                                           intensity[3],
                                           intensity[4],
                                           intensity[5],
                                           intensity[6],
                                           intensity[7]});
}

/****************************************/
/****************************************/

void CRealThymioLEDsActuator::SetProxVIntensity(std::vector<short> intensity){
    Aseba::DBusInterface* Interface = this->GetInterface();
     Interface->sendEventName("ProxVLeds",{intensity[0],intensity[1]});
}

/****************************************/
/****************************************/

void CRealThymioLEDsActuator::SetProxHIntensity(const CCI_ThymioProximitySensor::TReadings intensity){
    Aseba::DBusInterface* Interface = this->GetInterface();
     Interface->sendEventName("ProxHLeds",{(short) intensity[0].Value,
                                           (short) intensity[1].Value,
                                           (short) intensity[2].Value,
                                           (short) intensity[3].Value,
                                           (short) intensity[4].Value,
                                           (short) intensity[5].Value,
                                           (short) intensity[6].Value,
                                           (short) intensity[7].Value});
}

/****************************************/
/****************************************/

void CRealThymioLEDsActuator::SetProxVIntensity(const CCI_ThymioProximitySensor::TReadings intensity){
    Aseba::DBusInterface* Interface = this->GetInterface();
     Interface->sendEventName("ProxVLeds",{(short)intensity[0].Value,
                                           (short)intensity[1].Value});
}

/****************************************/
/****************************************/
