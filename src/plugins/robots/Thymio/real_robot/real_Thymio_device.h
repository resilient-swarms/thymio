#ifndef REAL_Thymio_DEVICE_H
#define REAL_Thymio_DEVICE_H

//#include <argos3/plugins/robots/Thymio/real_robot/real_Thymio_device.h>
//#include <argos3/core/utility/logging/argos_log.h>

#include <aseba/switches/asebacppapi/thymio_interface.h>

class CRealThymioDevice {

public:

   CRealThymioDevice(Aseba::ThymioInterface* ThymioInterface);
   virtual ~CRealThymioDevice();

   virtual void Do() = 0;

   inline Aseba::ThymioInterface* GetInterface() const {
      return ThymioInterface;
   }

private:

   Aseba::ThymioInterface* ThymioInterface;
   
};

#endif // REAL_Thymio_DEVICE_H
