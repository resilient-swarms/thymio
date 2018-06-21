#include "real_Thymio_proximity_sensor.h"

/****************************************/
/****************************************/

CRealThymioProximitySensor::CRealThymioProximitySensor(knet_dev_t* pt_dspic) :
   CRealThymioDevice(pt_dspic) {
}
   
/****************************************/
/****************************************/

CRealThymioProximitySensor::~CRealThymioProximitySensor() {
}

/****************************************/
/****************************************/

#define SETREADING(ARGOSIDX, KH4IDX)                                    \
   m_tReadings[ARGOSIDX].Value = (GetBuffer()[KH4IDX*2] | GetBuffer()[KH4IDX*2+1] << 8) / 65536.0;

void CRealThymioProximitySensor::Do() {
   kh4_proximity_ir(GetBuffer(), GetDSPic());
   SETREADING(0, 3);
   SETREADING(1, 2);
   SETREADING(2, 1);
   SETREADING(3, 0);
   SETREADING(4, 7);
   SETREADING(5, 6);
   SETREADING(6, 5);
   SETREADING(7, 4);
}

/****************************************/
/****************************************/
