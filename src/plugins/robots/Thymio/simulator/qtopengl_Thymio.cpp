/**
 * @file <argos3/plugins/robots/Thymio/simulator/qtopengl_Thymio.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "qtopengl_Thymio.h"
#include "Thymio_entity.h"
#include "Thymio_measures.h"

#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/plugins/simulator/entities/led_equipped_entity.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_widget.h>
#include <argos3/core/utility/datatypes/datatypes.h>
#include <argos3/core/utility/math/vector2.h>
#include <QImage>

#include <QOpenGLBuffer>
#include <QOpenGLContext>

namespace argos {

  static const Real HALF_CHASSIS_LENGHT = 0.055f;
  static const Real HALF_CHASSIS_WIDTH  = 0.055f;
  static const Real BODY_HEIGHT         = 0.053f;
  static const int  NUMBER_OF_VERTICIES = 46;

   /****************************************/
   /****************************************/

   // static QOpenGLTexture* MakeTexture(const QString& str_fname) {
   //    QString strPath =
   //       QString(ARGOS_INSTALL_PREFIX) +
   //       "/include/argos3/plugins/simulator/visualizations/qt-opengl/textures/" +
   //       str_fname;
   //    return new QOpenGLTexture(QImage(strPath));
   // }

   /****************************************/
   /****************************************/


   CQTOpenGLThymio::CQTOpenGLThymio() :
      m_unVertices(40) {
      /* Reserve the needed textures */
      // m_pcTextures[0] = MakeTexture("Thymio_texture_top.png");
      // m_pcTextures[1] = MakeTexture("Thymio_texture_bottom.png");
      // m_pcTextures[2] = MakeTexture("Thymio_texture_side.png");
      /* Reserve the needed display lists */
      m_unLists = glGenLists(3);
      /* Assign indices for better referencing (later) */

      m_unWheelList = m_unLists;
      m_unBaseList  = m_unLists + 1;
      m_unLEDList   = m_unLists + 2;

      /* Create the body display list */
      glNewList(m_unBaseList, GL_COMPILE);
      RenderBody();
      glEndList();


      /* Create the LED display list */
       glNewList(m_unLEDList, GL_COMPILE);
       RenderLED();
       glEndList();
      /* Create the wheel display list */
      glNewList(m_unWheelList, GL_COMPILE);
      RenderWheel();
      glEndList();
   }

   /****************************************/
   /****************************************/

   CQTOpenGLThymio::~CQTOpenGLThymio() {
      glDeleteLists(m_unLists, 2);
      // delete m_pcTextures[0];
      // delete m_pcTextures[1];
      // delete m_pcTextures[2];
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLThymio::Draw(CThymioEntity& c_entity) {
      /* Draw the body */
      glPushMatrix();
      // glScalef(THYMIO_LENGHT, THYMIO_WIDTH, THYMIO_HEIGHT);
      /* Place the body */
      glCallList(m_unBaseList);
      glPopMatrix();
            
      /* Place the LEDs */
      CLEDEquippedEntity& cLEDEquippedEntity = c_entity.GetLEDEquippedEntity();
      for(UInt32 i = 0; i < 8; i++) {
         const CColor&     cColor      = cLEDEquippedEntity.GetLED(i).GetColor();
         const CVector3&   cOffset     = cLEDEquippedEntity.GetLEDOffset(i);
         SetLEDMaterial(cColor.GetRed(), cColor.GetGreen(), cColor.GetBlue());
         glPushMatrix();
         glTranslatef(cOffset.GetX(), cOffset.GetY(), cOffset.GetZ());
         if(i==7 || i==6){
             glRotatef(-90,0,1,0);
         }
         else{
             glRotatef(90,0,1,0);
             glRotatef(PROXIMITY_SENSOR_ANGLES[i].GetValue(),1,0,0); //proximity sensors' angles are similar to LEDs'
         }
         glCallList(m_unLEDList);
         glPopMatrix();
      }

      // m_pcEmbodiedEntity& cEmbodiedEntity = c_entity.GetEmbodiedEntity();
      

      /* Place the wheels */
      glPushMatrix();
      glTranslatef(-THYMIO_XOFFSET, INTERWHEEL_DISTANCE*0.5f   , 0.0f);
      glCallList(m_unWheelList);
      glPopMatrix();
      glPushMatrix();
      glTranslatef(-THYMIO_XOFFSET, -INTERWHEEL_DISTANCE*0.5f  , 0.0f);
      glCallList(m_unWheelList);
      glPopMatrix();
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLThymio::SetLEDMaterial(GLfloat f_red, GLfloat f_green, GLfloat f_blue) {
      const GLfloat pfColor[]     = { f_red, f_green, f_blue, 1.0f };
      const GLfloat pfSpecular[]  = {  0.0f,    0.0f,   0.0f, 1.0f };
      const GLfloat pfShininess[] = {  0.0f                        };
      const GLfloat pfEmission[]  = { f_red, f_green, f_blue, 1.0f };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
   }

   /****************************************/
   /****************************************/
   void CQTOpenGLThymio::SetWhitePlasticMaterial() {
      const GLfloat pfColor[]     = {   1.0f, 1.0f, 1.0f, 1.0f };
      const GLfloat pfSpecular[]  = {   0.9f, 0.9f, 0.9f, 1.0f };
      const GLfloat pfShininess[] = { 100.0f                   };
      const GLfloat pfEmission[]  = {   0.0f, 0.0f, 0.0f, 1.0f };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pfColor);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            pfSpecular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           pfShininess);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,            pfEmission);
   }


   void CQTOpenGLThymio::RenderBody() {
    CQTOpenGLUserFunctions* qlfunc = new CQTOpenGLUserFunctions();

//      qlfunc->DrawBox(
//            CVector3(0,0,BODY_HEIGHT/2+THYMIO_BASE_ELEVATION), //position
//            CQuaternion( ),
//            CVector3(0.085,0.11,THYMIO_HEIGHT),//size
//            CColor::WHITE
//            );


//     CQTOpenGLUserFunctions::DrawBox(
//       CVector3(0,0,0), //position
//       CQuaternion( CVector3(0,0,0),CVector3(0,0,0)), //orientation
//       CVector3(THYMIO_LENGHT,THYMIO_WIDTH,THYMIO_HEIGHT),//size
//       CColor::WHITE
//       )

//       SetWhitePlasticMaterial();


       glBegin(GL_POLYGON);
         /* top face */
         glVertex3f(-0.055 ,-0.055  , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f( 0.033 ,-0.055  , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f( 0.04  ,-0.05   , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f( 0.05  ,-0.0255 , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f( 0.056 , 0.000  , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f( 0.05  , 0.0255 , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f( 0.04  , 0.05   , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f( 0.033 , 0.055  , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f(-0.055 , 0.055  , BODY_HEIGHT+THYMIO_BASE_ELEVATION);

         glEnd();
        

/*The Curve*/
       glBegin(GL_QUADS);
         glVertex3f(0.033  , -0.055 ,    BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f(0.033  , -0.055 ,    THYMIO_BASE_ELEVATION);
         glVertex3f(0.04   , -0.05  ,    THYMIO_BASE_ELEVATION);
         glVertex3f(0.04   , -0.05  ,    BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glEnd();

         glBegin(GL_QUADS);
         glVertex3f( 0.04  ,-0.05   , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f( 0.04  ,-0.05   , THYMIO_BASE_ELEVATION);
         glVertex3f( 0.05  ,-0.0255 , THYMIO_BASE_ELEVATION);
         glVertex3f( 0.05  ,-0.0255 , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glEnd();

         glBegin(GL_QUADS);
         glVertex3f( 0.05  ,-0.0255, BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f( 0.05  ,-0.0255, THYMIO_BASE_ELEVATION);
         glVertex3f( 0.056 , 0.0   , THYMIO_BASE_ELEVATION);
         glVertex3f( 0.056 , 0.0   , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glEnd();

         glBegin(GL_QUADS);
         glVertex3f( 0.056 , 0.000  , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f( 0.056 , 0.000  , THYMIO_BASE_ELEVATION);
         glVertex3f( 0.050 , 0.0255 , THYMIO_BASE_ELEVATION);
         glVertex3f( 0.050 , 0.0255 , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glEnd();

         glBegin(GL_QUADS);
         glVertex3f( 0.05  , 0.0255 , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f( 0.05  , 0.0255 , THYMIO_BASE_ELEVATION);
         glVertex3f( 0.04  , 0.05   , THYMIO_BASE_ELEVATION);
         glVertex3f( 0.04  , 0.05   , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glEnd();

         glBegin(GL_QUADS);
         glVertex3f( 0.04  , 0.05   , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f( 0.04  , 0.05   , THYMIO_BASE_ELEVATION);
         glVertex3f( 0.033 , 0.055  , THYMIO_BASE_ELEVATION);
         glVertex3f( 0.033 , 0.055  , BODY_HEIGHT+THYMIO_BASE_ELEVATION);
       glEnd();

/*end of curve*/

         //sides
         glBegin(GL_QUADS);
         glVertex3f(-0.055 ,-0.055 ,  BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f(-0.055 ,-0.055 ,  THYMIO_BASE_ELEVATION);
         glVertex3f( 0.033 ,-0.055 ,  THYMIO_BASE_ELEVATION);
         glVertex3f( 0.033 ,-0.055 ,  BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glEnd();

         glBegin(GL_QUADS);
         glVertex3f( 0.033 , 0.055 ,  BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f( 0.033 , 0.055 ,  THYMIO_BASE_ELEVATION);
         glVertex3f(-0.055 , 0.055 ,  THYMIO_BASE_ELEVATION);
         glVertex3f(-0.055 , 0.055 ,  BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glEnd();

         //back
         glBegin(GL_QUADS);
         glVertex3f(-0.055 , 0.055 ,  BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glVertex3f(-0.055 , 0.055 ,  THYMIO_BASE_ELEVATION);
         glVertex3f(-0.055 ,-0.055 ,  THYMIO_BASE_ELEVATION);
         glVertex3f(-0.055 ,-0.055 ,  BODY_HEIGHT+THYMIO_BASE_ELEVATION);
         glEnd();

       glDisable(GL_TEXTURE_2D);
   }

   /****************************************/
   /****************************************/

   void CQTOpenGLThymio::RenderLED() {
      /* Draw it as a tiny pyramid pointing to Z upwards
         (with no base, cause it's not visible anyway) */
      glBegin(GL_TRIANGLES);
      /* North */
      glVertex3f( 0.000,  0.000, 0.005);
      glVertex3f( 0.005, -0.005, 0.000);
      glVertex3f( 0.005,  0.005, 0.000);
      /* South */
      glVertex3f( 0.000,  0.000, 0.005);
      glVertex3f(-0.005,  0.005, 0.000);
      glVertex3f(-0.005, -0.005, 0.000);
      /* West */
      glVertex3f( 0.000,  0.000, 0.005);
      glVertex3f( 0.005,  0.005, 0.000);
      glVertex3f(-0.005,  0.005, 0.000);
      /* East */
      glVertex3f( 0.000,  0.000, 0.005);
      glVertex3f(-0.005, -0.005, 0.000);
      glVertex3f( 0.005, -0.005, 0.000);
      glEnd();
   }

   /****************************************/
   /****************************************/

   class CQTOpenGLOperationDrawThymioNormal : public CQTOpenGLOperationDrawNormal {
   public:
      void ApplyTo(CQTOpenGLWidget& c_visualization,
                   CThymioEntity& c_entity) {
         static CQTOpenGLThymio m_cModel;
         c_visualization.DrawRays(c_entity.GetControllableEntity());
         c_visualization.DrawEntity(c_entity.GetEmbodiedEntity());
         m_cModel.Draw(c_entity);
      }
   };

   class CQTOpenGLOperationDrawThymioSelected : public CQTOpenGLOperationDrawSelected {
   public:
      void ApplyTo(CQTOpenGLWidget& c_visualization,
                   CThymioEntity& c_entity) {
         c_visualization.DrawBoundingBox(c_entity.GetEmbodiedEntity());
      }
   };

   void CQTOpenGLThymio::RenderWheel() {
      /* Set material */
      SetWhitePlasticMaterial();
      /* Right side */
      CVector2 cVertex(WHEEL_RADIUS, 0.0f);
      CRadians cAngle(CRadians::TWO_PI / m_unVertices);
      CVector3 cNormal(-1.0f, -1.0f, 0.0f);
      cNormal.Normalize();
      glBegin(GL_POLYGON);
      for(GLuint i = 0; i <= m_unVertices; i++) {
         glNormal3f(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
         glVertex3f(cVertex.GetX(), -WHEEL_WIDTH*0.5, WHEEL_RADIUS + cVertex.GetY());
         cVertex.Rotate(cAngle);
         cNormal.RotateY(cAngle);
      }
      glEnd();

      /* Left side */
      cVertex.Set(WHEEL_RADIUS, 0.0f);
      cNormal.Set(-1.0f, 1.0f, 0.0f);
      cNormal.Normalize();
      cAngle = -cAngle;
      glBegin(GL_POLYGON);
      for(GLuint i = 0; i <= m_unVertices; i++) {
         glNormal3f(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
         glVertex3f(cVertex.GetX(), WHEEL_WIDTH*0.5f, WHEEL_RADIUS + cVertex.GetY());
         cVertex.Rotate(cAngle);
         cNormal.RotateY(cAngle);
      }
      glEnd();

      /* Tire */
      cNormal.Set(1.0f, 0.0f, 0.0f);
      cVertex.Set(WHEEL_RADIUS, 0.0f);
      cAngle = -cAngle;
      glBegin(GL_QUAD_STRIP);
      for(GLuint i = 0; i <= m_unVertices; i++) {
         glNormal3f(cNormal.GetX(), cNormal.GetY(), cNormal.GetZ());
         glVertex3f(cVertex.GetX(), -WHEEL_WIDTH*0.5f, WHEEL_RADIUS + cVertex.GetY());
         glVertex3f(cVertex.GetX(),  WHEEL_WIDTH*0.5f, WHEEL_RADIUS + cVertex.GetY());
         cVertex.Rotate(cAngle);
         cNormal.RotateY(cAngle);
      }
      glEnd();
   }

   REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawNormal, CQTOpenGLOperationDrawThymioNormal, CThymioEntity);

   REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawSelected, CQTOpenGLOperationDrawThymioSelected, CThymioEntity);

   /****************************************/
   /****************************************/

}
