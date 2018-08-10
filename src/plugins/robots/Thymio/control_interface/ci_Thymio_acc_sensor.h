#ifndef CCI_THYMIO_ACC_SENSOR_H
#define CCI_THYMIO_ACC_SENSOR_H

#include <argos3/core/control_interface/ci_sensor.h>

namespace argos {
   class CCI_Thymio_acc_sensor;
}

namespace argos {

class CCI_Thymio_acc_sensor : virtual public CCI_Sensor{

    public:
        struct AccValues{
            short x;
            short y;
        }accValues;

    public:
//        CCI_Thymio_acc_sensor();

        virtual ~CCI_Thymio_acc_sensor();

        virtual AccValues& getAccValues();


    #ifdef ARGOS_WITH_LUA
          virtual void CreateLuaState(lua_State* pt_lua_state);

          virtual void ReadingsToLuaState(lua_State* pt_lua_state);
    #endif

    };
}
#endif // CCI_THYMIO_ACC_SENSOR_H
