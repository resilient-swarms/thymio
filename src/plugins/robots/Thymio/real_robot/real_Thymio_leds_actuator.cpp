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

//its a good idea to devise a good conversion plan for values
void CRealThymioLEDsActuator::SetLed(Real brightness){
    Aseba::DBusInterface* Interface = this->GetInterface();
    Interface->setVariable("Thymio-II","leds.prox.h",{(short)brightness});
}

/****************************************/
/****************************************/
