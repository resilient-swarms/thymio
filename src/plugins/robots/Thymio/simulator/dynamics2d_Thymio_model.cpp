/**
 * @file <argos3/plugins/robots/Thymio/simulator/dynamics2d_Thymio_model.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "dynamics2d_Thymio_model.h"
#include "Thymio_measures.h"

#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_gripping.h>
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_engine.h>

namespace argos {

   /****************************************/
   /****************************************/

   static const Real Thymio_MASS                = 0.270f; //THYMIO is 270 grams
   static const Real Thymio_MAX_FORCE           = 1.5f;
   static const Real Thymio_MAX_TORQUE          = 1.5f;
   static const int  NUMBER_OF_VERTICIES        = 9;

   enum Thymio_WHEELS {
      Thymio_LEFT_WHEEL   = 0,
      Thymio_RIGHT_WHEEL  = 1
   };

   /****************************************/
   /****************************************/

   CDynamics2DThymioModel::CDynamics2DThymioModel(CDynamics2DEngine& c_engine,CThymioEntity& c_entity) :
      CDynamics2DSingleBodyObjectModel(c_engine, c_entity),
      m_cThymioEntity(c_entity),
      m_cWheeledEntity(m_cThymioEntity.GetWheeledEntity()),
      m_cDiffSteering(c_engine,
                      Thymio_MAX_FORCE,
                      Thymio_MAX_TORQUE,
                      Thymio_WHEEL_DISTANCE,
                      c_entity.GetConfigurationNode()),
      m_fCurrentWheelVelocity(m_cWheeledEntity.GetWheelVelocities()) 
      {
        /* Create the body with initial position and orientation */

        /* Get the size of the entity */
        CVector3 cHalfSize = CVector3( THYMIO_WIDTH, THYMIO_LENGHT, THYMIO_HEIGHT) * 0.5f;
        /* Create a polygonal object in the physics space */
        /* Start defining the vertices
           NOTE: points must be defined in a clockwise winding
        */

        cpVect* tVertices = new cpVect[NUMBER_OF_VERTICIES];

        int i = 0;
        tVertices[i++] = cpv(-0.055, -0.053);
        tVertices[i++] = cpv(-0.055,  0.033);

        tVertices[i++] = cpv(-0.0500, 0.040);
        tVertices[i++] = cpv(-0.0255, 0.050);
        tVertices[i++] = cpv( 0.0000, 0.056);
        tVertices[i++] = cpv( 0.0255, 0.050);
        tVertices[i++] = cpv( 0.0500, 0.040);

       tVertices[i++] = cpv( 0.055,  0.033);
       tVertices[i]   = cpv( 0.055, -0.053);


       /*Box physical model*/
       /*
        cpVect* tVertices = new cpVect[NUMBER_OF_VERTICIES];
        int i = 0;
        tVertices[i++] = cpv(-cHalfSize.GetX(), -cHalfSize.GetY());
        // std::cout<<i<<") x:"<<-cHalfSize.GetX()<<"\ty:"<<-cHalfSize.GetY()<<"\n";

        tVertices[i++] = cpv(-cHalfSize.GetX(),  cHalfSize.GetY());
        // std::cout<<i<<") x:"<<-cHalfSize.GetX()<<"\ty:"<<cHalfSize.GetY()<<"\n";

       tVertices[i++] = cpv( cHalfSize.GetX(),  cHalfSize.GetY());
       // std::cout<<i<<") x:"<<cHalfSize.GetX()<<"\ty:"<<cHalfSize.GetY()<<"\n";

       tVertices[i] = cpv( cHalfSize.GetX(), -cHalfSize.GetY());
       // std::cout<<i<<") x:"<<cHalfSize.GetX()<<"\ty:"<<-cHalfSize.GetY()<<"\n";
       */
       
        cpBody* ptBody =
              cpSpaceAddBody(GetDynamics2DEngine().GetPhysicsSpace(),
                             cpBodyNew(Thymio_MASS,
                                       cpMomentForPoly(Thymio_MASS,
                                                       NUMBER_OF_VERTICIES,
                                                       tVertices,
                                                       cpvzero)));


        const CVector3& cPosition = GetEmbodiedEntity().GetOriginAnchor().Position;

        ptBody->p = cpv(cPosition.GetX(), cPosition.GetY());
        CRadians cXAngle, cYAngle, cZAngle;
        
        GetEmbodiedEntity().GetOriginAnchor().Orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
        cpBodySetAngle(ptBody, cZAngle.GetValue());

        /* Create the body shape */
        cpShape* ptShape =
            cpSpaceAddShape(GetDynamics2DEngine().GetPhysicsSpace(),
                            cpPolyShapeNew(ptBody,
                                           NUMBER_OF_VERTICIES,
                                           tVertices,
                                           cpvzero));


        ptShape->e = 0.0; // No elasticity
        ptShape->u = 0.7; // Lots of friction
        /* Constrain the actual base body to follow the diff steering control */
        m_cDiffSteering.AttachTo(ptBody);
        /* Set the body so that the default methods work as expected */
        SetBody(ptBody, THYMIO_BASE_TOP);
      }

   /****************************************/
   /****************************************/

   CDynamics2DThymioModel::~CDynamics2DThymioModel() {
      m_cDiffSteering.Detach();
   }

   /****************************************/
   /****************************************/

   void CDynamics2DThymioModel::Reset() {
      CDynamics2DSingleBodyObjectModel::Reset();
      m_cDiffSteering.Reset();
   }

   /****************************************/
   /****************************************/

   void CDynamics2DThymioModel::UpdateFromEntityStatus() {
      /* Do we want to move? */
      if((m_fCurrentWheelVelocity[Thymio_LEFT_WHEEL] != 0.0f) ||
         (m_fCurrentWheelVelocity[Thymio_RIGHT_WHEEL] != 0.0f)) {
         m_cDiffSteering.SetWheelVelocity(m_fCurrentWheelVelocity[Thymio_LEFT_WHEEL],
                                          m_fCurrentWheelVelocity[Thymio_RIGHT_WHEEL]);
      }
      else {
         /* No, we don't want to move - zero all speeds */
         m_cDiffSteering.Reset();
      }

   }

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_DYNAMICS2D_OPERATIONS_ON_ENTITY(CThymioEntity, CDynamics2DThymioModel);

   /****************************************/
   /****************************************/

}
