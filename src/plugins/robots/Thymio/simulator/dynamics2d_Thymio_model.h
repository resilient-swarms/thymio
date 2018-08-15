/**
 * @file <argos3/plugins/robots/Thymio/simulator/dynamics2d_Thymio_model.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef DYNAMICS2D_Thymio_MODEL_H
#define DYNAMICS2D_Thymio_MODEL_H

namespace argos {
   class CDynamics2DDifferentialSteeringControl;
   class CDynamics2DGripper;     //I think we don't need this remove
   class CDynamics2DGrippable;   //I think we don't need this remove
   class CDynamics2DThymioModel;
}

#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_single_body_object_model.h>
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_differentialsteering_control.h>
#include <argos3/plugins/robots/Thymio/simulator/Thymio_entity.h>

namespace argos {

   class CDynamics2DThymioModel : public CDynamics2DSingleBodyObjectModel {


   public:

      CDynamics2DThymioModel(CDynamics2DEngine& c_engine,
                              CThymioEntity& c_entity);
      virtual ~CDynamics2DThymioModel();

      virtual void Reset();

      virtual void UpdateFromEntityStatus();
      
   private:

      CThymioEntity& m_cThymioEntity;

      CWheeledEntity& m_cWheeledEntity;

      CDynamics2DDifferentialSteeringControl m_cDiffSteering;

      const Real* m_fCurrentWheelVelocity;

   };

}

#endif
