#ifndef REAL_Thymio_DEVICE_H
#define REAL_Thymio_DEVICE_H

#include <Thymio/Thymio.h>

class CRealThymioDevice {

public:

   CRealThymioDevice(knet_dev_t* pt_dspic);
   virtual ~CRealThymioDevice() {}

   virtual void Do() = 0;

   inline knet_dev_t* GetDSPic() const {
      return m_ptDSPic;
   }

   inline char* GetBuffer() {
      return m_pchBuffer;
   }

private:

   knet_dev_t* m_ptDSPic;
   static char m_pchBuffer[100];
   
};

#endif // REAL_Thymio_DEVICE_H
