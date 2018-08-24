#ifndef CCI_THYMIO_ACC_SENSOR_H
#define CCI_THYMIO_ACC_SENSOR_H

#include <argos3/core/control_interface/ci_sensor.h>

namespace argos {
   class CCI_Thymio_acc_sensor;
}

namespace argos {

class CCI_Thymio_acc_sensor : virtual public CCI_Sensor{

    public:
        struct SReading{
            short x;
            short y;
            short z;

//            AccValues(short x,short y,short z)
//            {
//                this->x = x;
//                this->y = y;
//                this->z = z;
//            }
        }accValues;

    public:
        CCI_Thymio_acc_sensor();

        virtual ~CCI_Thymio_acc_sensor(){}

        virtual SReading& getAccValues();


    #ifdef ARGOS_WITH_LUA
        virtual void CreateLuaState(lua_State* pt_lua_state){}

        virtual void ReadingsToLuaState(lua_State* pt_lua_state){}
    #endif
    };
//    std::ostream& operator<<(std::ostream& c_os,
//                             const CCI_Thymio_acc_sensor::SReading& accValues);


}
#endif // CCI_THYMIO_ACC_SENSOR_H
