#include "real_Thymio_device.h"


/****************************************/
/****************************************/

CRealThymioDevice::CRealThymioDevice(Aseba::ThymioInterface* ThymioInterface) :
   ThymioInterface(ThymioInterface) {
}

/****************************************/
/****************************************/

CRealThymioDevice::~CRealThymioDevice(){}

/****************************************/
/****************************************/


void CRealThymioDevice::Do(){
    ThymioInterface->pingNetwork();
}

/****************************************/
/****************************************/
