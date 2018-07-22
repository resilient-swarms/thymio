#ifndef REAL_Thymio_DEVICE_H
#define REAL_Thymio_DEVICE_H

#include "dbusinterface.h"

class CRealThymioDevice {

public:

   CRealThymioDevice(Aseba::DBusInterface* ThymioInterface);
   virtual ~CRealThymioDevice() {}

   virtual void Do() = 0;

   inline Aseba::DBusInterface* GetInterface() const {
      return ThymioInterface;
   }

private:

   Aseba::DBusInterface* ThymioInterface;
   
};

#endif // REAL_Thymio_DEVICE_H
