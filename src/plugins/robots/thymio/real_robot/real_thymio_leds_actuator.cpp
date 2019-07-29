#include "real_thymio_leds_actuator.h"

/****************************************/
/****************************************/

CRealThymioLEDsActuator::CRealThymioLEDsActuator(Aseba::ThymioInterface* ThymioInterface) :
   CRealThymioDevice(ThymioInterface) {
}
   
/****************************************/
/****************************************/

CRealThymioLEDsActuator::~CRealThymioLEDsActuator() {
    Aseba::ThymioInterface* Interface = this->GetInterface();
    Interface->setVariable("Thymio-II","leds.prox.h",{0});
}
   
/****************************************/
/****************************************/


void CRealThymioLEDsActuator::Do() {

}

/****************************************/
/****************************************/

void CRealThymioLEDsActuator::SetColor(CColor led_color){
}

/****************************************/
/****************************************/

void CRealThymioLEDsActuator::SetColors(std::vector<CColor> led_colors){
}

/****************************************/
/****************************************/

void CRealThymioLEDsActuator::SetProxHIntensity(std::vector<short> intensity){
    Aseba::ThymioInterface* Interface = this->GetInterface();
     Interface->sendEventName("ProxHLeds",{intensity[0],
                                           intensity[1],
                                           intensity[2],intensity[2],
                                           intensity[3],
                                           intensity[4],
                                           intensity[5],
                                           intensity[7]});
}

/****************************************/
/****************************************/

void CRealThymioLEDsActuator::SetProxVIntensity(std::vector<short> intensity){
    Aseba::ThymioInterface* Interface = this->GetInterface();
     Interface->sendEventName("ProxVLeds",{intensity[0],intensity[1]});
}

/****************************************/
/****************************************/

void CRealThymioLEDsActuator::SetProxHIntensity(const CCI_ThymioProximitySensor::TReadings intensity){
    Aseba::ThymioInterface* Interface = this->GetInterface();
     Interface->sendEventName("ProxHLeds",{(short) intensity[0].Value,
                                           (short) intensity[1].Value,
                                           (short) intensity[2].Value,(short) intensity[2].Value,
                                           (short) intensity[3].Value,
                                           (short) intensity[4].Value,
                                           (short) intensity[5].Value,
                                           (short) intensity[6].Value});
}

/****************************************/
/****************************************/

void CRealThymioLEDsActuator::SetProxVIntensity(const CCI_ThymioProximitySensor::TReadings intensity){
    Aseba::ThymioInterface* Interface = this->GetInterface();
     Interface->sendEventName("ProxVLeds",{(short)intensity[0].Value,
                                           (short)intensity[1].Value});
}

/****************************************/
/****************************************/
