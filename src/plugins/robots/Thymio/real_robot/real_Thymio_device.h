#ifndef REAL_Thymio_DEVICE_H
#define REAL_Thymio_DEVICE_H

// #include <Thymio/Thymio.h>
#include "dbusinterface.h"

class CRealThymioDevice {

public:

   CRealThymioDevice(Aseba::DBusInterface* ThymioInterface);
   virtual ~CRealThymioDevice() {}

   virtual void Do() = 0;

   inline Aseba::DBusInterface* GetInterface() const {
      return ThymioInterface;
   }

   // inline char* GetBuffer() {
   //    return m_pchBuffer;
   // }

private:

   Aseba::DBusInterface* ThymioInterface;
   // static char m_pchBuffer[100];
   
};

#endif // REAL_Thymio_DEVICE_H
