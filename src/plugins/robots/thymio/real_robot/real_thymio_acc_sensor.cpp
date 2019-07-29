#include "real_thymio_acc_sensor.h"

/****************************************/
/****************************************/

CRealThymioAccSensor::CRealThymioAccSensor(Aseba::ThymioInterface* ThymioInterface) :
   CRealThymioDevice(ThymioInterface) {
}
   
/****************************************/
/****************************************/

CRealThymioAccSensor::~CRealThymioAccSensor() {
}

/****************************************/
/****************************************/

void CRealThymioAccSensor::Do() {
    Aseba::ThymioInterface* Interface = this->GetInterface();
    std::vector<uint16_t> list = (std::vector<uint16_t>) Interface->getVariable("thymio-II", "acc");
    accValues = {(short)list[0],(short)list[1],(short)list[2]};
}

/****************************************/
/****************************************/
