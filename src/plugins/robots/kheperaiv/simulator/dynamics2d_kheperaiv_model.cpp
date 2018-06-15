/**
 * @file <argos3/plugins/robots/kheperaiv/simulator/dynamics2d_kheperaiv_model.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "dynamics2d_kheperaiv_model.h"
#include "kheperaiv_measures.h"

#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_gripping.h>
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_engine.h>

namespace argos {

   /****************************************/
   /****************************************/

   static const Real KHEPERAIV_MASS                = 0.5f;
   static const Real KHEPERAIV_MAX_FORCE           = 1.5f;
   static const Real KHEPERAIV_MAX_TORQUE          = 1.5f;

   enum KHEPERAIV_WHEELS {
      KHEPERAIV_LEFT_WHEEL = 0,
      KHEPERAIV_RIGHT_WHEEL = 1
   };

   /****************************************/
   /****************************************/

   CDynamics2DKheperaIVModel::CDynamics2DKheperaIVModel(CDynamics2DEngine& c_engine,CKheperaIVEntity& c_entity) :
      CDynamics2DSingleBodyObjectModel(c_engine, c_entity),
      m_cKheperaIVEntity(c_entity),
      m_cWheeledEntity(m_cKheperaIVEntity.GetWheeledEntity()),
      m_cDiffSteering(c_engine,
                      KHEPERAIV_MAX_FORCE,
                      KHEPERAIV_MAX_TORQUE,
                      KHEPERAIV_WHEEL_DISTANCE,
                      c_entity.GetConfigurationNode()),
      m_fCurrentWheelVelocity(m_cWheeledEntity.GetWheelVelocities()) 
      {
        /* Create the body with initial position and orientation */

        /* Get the size of the entity */
        CVector3 cHalfSize = CVector3( THYMIO_LENGHT, THYMIO_WIDTH, THYMIO_HEIGHT) * 0.5f;
        /* Create a polygonal object in the physics space */
        /* Start defining the vertices
           NOTE: points must be defined in a clockwise winding
        */
        cpVect tVertices[] = {
           cpv(-cHalfSize.GetX(), -cHalfSize.GetY()),
           cpv(-cHalfSize.GetX(),  cHalfSize.GetY()),
           cpv( cHalfSize.GetX(),  cHalfSize.GetY()),
           cpv( cHalfSize.GetX(), -cHalfSize.GetY())
        };

        cpBody* ptBody =
              cpSpaceAddBody(GetDynamics2DEngine().GetPhysicsSpace(),
                             cpBodyNew(KHEPERAIV_MASS,
                                       cpMomentForPoly(KHEPERAIV_MASS,
                                                       4,
                                                       tVertices,
                                                       cpvzero)));

        // cpBody* ptBody =
        //    cpSpaceAddBody(GetDynamics2DEngine().GetPhysicsSpace(),
        //                   cpBodyNew(KHEPERAIV_MASS,
        //                             cpMomentForCircle(KHEPERAIV_MASS,
        //                                               0.0f,
        //                                               KHEPERAIV_BASE_RADIUS + KHEPERAIV_BASE_RADIUS,
        //                                               cpvzero)));

        const CVector3& cPosition = GetEmbodiedEntity().GetOriginAnchor().Position;

        ptBody->p = cpv(cPosition.GetX(), cPosition.GetY());
        CRadians cXAngle, cYAngle, cZAngle;
        
        GetEmbodiedEntity().GetOriginAnchor().Orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
        cpBodySetAngle(ptBody, cZAngle.GetValue());

        /* Create the body shape */
        cpShape* ptShape =
            cpSpaceAddShape(GetDynamics2DEngine().GetPhysicsSpace(),
                            cpPolyShapeNew(ptBody,
                                           4,
                                           tVertices,
                                           cpvzero));

        ptShape->e = 0.0; // No elasticity
        ptShape->u = 0.7; // Lots of friction
        /* Constrain the actual base body to follow the diff steering control */
        m_cDiffSteering.AttachTo(ptBody);
        /* Set the body so that the default methods work as expected */
        SetBody(ptBody, KHEPERAIV_BASE_TOP);
      }

   /****************************************/
   /****************************************/

   CDynamics2DKheperaIVModel::~CDynamics2DKheperaIVModel() {
      m_cDiffSteering.Detach();
   }

   /****************************************/
   /****************************************/

   void CDynamics2DKheperaIVModel::Reset() {
      CDynamics2DSingleBodyObjectModel::Reset();
      m_cDiffSteering.Reset();
   }

   /****************************************/
   /****************************************/

   void CDynamics2DKheperaIVModel::UpdateFromEntityStatus() {
      /* Do we want to move? */
      if((m_fCurrentWheelVelocity[KHEPERAIV_LEFT_WHEEL] != 0.0f) ||
         (m_fCurrentWheelVelocity[KHEPERAIV_RIGHT_WHEEL] != 0.0f)) {
         m_cDiffSteering.SetWheelVelocity(m_fCurrentWheelVelocity[KHEPERAIV_LEFT_WHEEL],
                                          m_fCurrentWheelVelocity[KHEPERAIV_RIGHT_WHEEL]);
      }
      else {
         /* No, we don't want to move - zero all speeds */
         m_cDiffSteering.Reset();
      }
   }

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_DYNAMICS2D_OPERATIONS_ON_ENTITY(CKheperaIVEntity, CDynamics2DKheperaIVModel);

   /****************************************/
   /****************************************/

}
