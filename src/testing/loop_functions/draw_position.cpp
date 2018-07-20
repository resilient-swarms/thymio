#include "draw_position.h"

/****************************************/
/****************************************/

CIDQTUserFunctions::CIDQTUserFunctions() {
   RegisterUserFunction<CIDQTUserFunctions,CThymioEntity>(&CIDQTUserFunctions::Draw);
}

/****************************************/
/****************************************/

void CIDQTUserFunctions::Draw(CThymioEntity& c_entity) {

   DrawText(CVector3(0.0, 0.0, 0.2),   // position
            c_entity.GetId().c_str()); // text

   DrawText(CVector3(0.0, 0.0, 0.15),   
            "X:"+std::to_string(c_entity.GetEmbodiedEntity().GetOriginAnchor().Position.GetX()) );

   DrawText(CVector3(0.0, 0.0, 0.1),   
            "Y:"+std::to_string(c_entity.GetEmbodiedEntity().GetOriginAnchor().Position.GetY()) ); 
}

/****************************************/
/****************************************/

REGISTER_QTOPENGL_USER_FUNCTIONS(CIDQTUserFunctions, "draw_position")
