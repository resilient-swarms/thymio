#include "ci_Thymio_acc_sensor.h"

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#endif

namespace argos {

    CCI_Thymio_acc_sensor::AccValues& CCI_Thymio_acc_sensor::getAccValues(){
        return accValues;
    }
}

