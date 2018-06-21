#include "real_Thymio_ground_sensor.h"

/****************************************/
/****************************************/

CRealThymioGroundSensor::CRealThymioGroundSensor(knet_dev_t* pt_dspic) :
   CRealThymioDevice(pt_dspic) {
}
   
/****************************************/
/****************************************/

CRealThymioGroundSensor::~CRealThymioGroundSensor() {
}

/****************************************/
/****************************************/

#define SETREADING(ARGOSIDX, KH4IDX)                                    \
   m_tReadings[ARGOSIDX].Value = (GetBuffer()[KH4IDX*2] | GetBuffer()[KH4IDX*2+1] << 8) / 65536.0;

void CRealThymioGroundSensor::Do() {
   kh4_proximity_ir(GetBuffer(), GetDSPic());
   SETREADING(0, 9);
   SETREADING(1, 8);
   SETREADING(2, 11);
   SETREADING(3, 10);
}

/****************************************/
/****************************************/
