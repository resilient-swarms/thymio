#include "real_Thymio_battery_sensor.h"

/****************************************/
/****************************************/

CRealThymioBatterySensor::CRealThymioBatterySensor(knet_dev_t* pt_dspic) :
   CRealThymioDevice(pt_dspic) {
}
   
/****************************************/
/****************************************/

CRealThymioBatterySensor::~CRealThymioBatterySensor() {
}

/****************************************/
/****************************************/

void CRealThymioBatterySensor::Do() {
   kh4_battery_status(GetBuffer(), GetDSPic());
   m_sReading.AvailableCharge = GetBuffer()[3] / 100.0;
   m_sReading.TimeLeft = -1.0; // TODO
}

/****************************************/
/****************************************/
