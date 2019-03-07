#ifndef ID_QTUSER_FUNCTIONS_H
#define ID_QTUSER_FUNCTIONS_H

#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <argos3/plugins/robots/thymio/simulator/thymio_entity.h>

using namespace argos;

class CIDQTUserFunctions : public CQTOpenGLUserFunctions {

public:

   CIDQTUserFunctions();

   virtual ~CIDQTUserFunctions() {}

   void Draw(CThymioEntity& c_entity);
   
};

#endif
