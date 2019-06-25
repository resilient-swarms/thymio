/**
 * @file <argos3/plugins/robots/Thymio/simulator/qtopengl_Thymio.h>
 */

#ifndef QTOPENGL_Thymio_H
#define QTOPENGL_Thymio_H

namespace argos {
   class CQTOpenGLThymio;
   class CThymioEntity;
}

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

#include <QOpenGLTexture>
#include <argos3/core/utility/datatypes/color.h>


namespace argos {

   class CQTOpenGLThymio {

   public:

      CQTOpenGLThymio();

      virtual ~CQTOpenGLThymio();

      virtual void Draw(CThymioEntity& c_entity);

   protected:

      /** Sets a white plastic material */
      void SetWhitePlasticMaterial();
      /** Sets a blue plastic material */
      void SetBluePlasticMaterial();
      /** Sets a colored LED material */
      void SetLEDMaterial(GLfloat f_red,
                          GLfloat f_green,
                          GLfloat f_blue);

      /** Renders the base */
      void RenderBody();
      /** A single LED of the ring */
      void RenderLED();
      /** Renders a wheel */
      void RenderWheel();

   private:

      /** Start of the texture index
       * Order: top, bottom, side
       */
      QOpenGLTexture* m_pcTextures[3];

      /** Start of the display list index */
      GLuint m_unLists;

      /** Base display list */
      GLuint m_unBaseList;

      /** LED display list */
      GLuint m_unLEDList;

      /* Wheel display list*/
      GLuint m_unWheelList;

      /** Number of vertices to display the round parts
          (wheels, chassis, etc.) */
      GLuint m_unVertices;


      /** Color of the top of the robot -- takes the color of the LEDs.
       * Used for visual debugging as LEDs too small */
      CColor top_color;

   };

}

#endif
