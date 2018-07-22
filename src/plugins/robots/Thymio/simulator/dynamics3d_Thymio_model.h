/**
 * @file <argos3/plugins/simulator/physics_engines/dynamics3d/dynamics3d_box_model.h>
 *
 * @author Michael Allwright - <allsey87@gmail.com>
 */

#ifndef DYNAMICS3D_BOX_MODEL_H
#define DYNAMICS3D_BOX_MODEL_H

namespace argos {
   class CDynamics3DSingleBodyObjectModel;
   class CDynamics3DThymio;
   class CBoxEntity;
}

#include <argos3/plugins/simulator/physics_engines/dynamics3d/dynamics3d_single_body_object_model.h>
#include "Thymio_entity.h"

namespace argos {

   class CDynamics3DThymio : public CDynamics3DSingleBodyObjectModel {

   public:     

      CDynamics3DThymio(CDynamics3DEngine& c_engine,
                          CThymioEntity& c_thymio);

      virtual ~CDynamics3DThymio();

   private:

      CBody* m_pcBody;

   };
}

#endif
