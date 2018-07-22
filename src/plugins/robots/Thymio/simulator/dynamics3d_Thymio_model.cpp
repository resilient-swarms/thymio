/**
 * @file <argos3/plugins/simulator/physics_engines/dynamics3d/dynamics3d_box_model.cpp>
 *
 * @author Michael Allwright - <allsey87@gmail.com>
 */

#include "dynamics3d_Thymio_model.h"
#include "Thymio_measures.h"
#include <argos3/plugins/simulator/entities/box_entity.h>
#include <argos3/plugins/simulator/physics_engines/dynamics3d/dynamics3d_engine.h>
#include <argos3/plugins/simulator/physics_engines/dynamics3d/dynamics3d_single_body_object_model.h>
#include <argos3/plugins/simulator/physics_engines/dynamics3d/dynamics3d_shape_manager.h>

static const Real Thymio_MASS                = 0.270f; //THYMIO is 270 grams
static const Real Thymio_MAX_FORCE           = 1.5f;
static const Real Thymio_MAX_TORQUE          = 1.5f;
static const int  NUMBER_OF_VERTICIES        = 4;

namespace argos {

   /****************************************/
   /****************************************/

   CDynamics3DThymio::CDynamics3DThymio(CDynamics3DEngine& c_engine, CThymioEntity& c_thymio) :
      CDynamics3DSingleBodyObjectModel(c_engine, c_thymio),
      m_pcBody(nullptr) {
      /* Fetch a collision shape for this model */
      std::shared_ptr<btCollisionShape> ptrShape = 
         CDynamics3DShapeManager::RequestBox(
            btVector3(THYMIO_WIDTH * 0.5f,
                      THYMIO_HEIGHT * 0.5f,
                      THYMIO_LENGHT * 0.5f));
      /* Get the origin anchor */
      SAnchor& sAnchor = c_thymio.GetEmbodiedEntity().GetOriginAnchor();
      const CQuaternion& cOrientation = sAnchor.Orientation;
      const CVector3& cPosition = sAnchor.Position;
      /* Calculate the start transform */
      const btTransform& cStartTransform = btTransform(
         btQuaternion(cOrientation.GetX(),
                      cOrientation.GetZ(),
                     -cOrientation.GetY(),
                      cOrientation.GetW()),
         btVector3(cPosition.GetX(),
                   cPosition.GetZ(),
                  -cPosition.GetY()));
      /* Calculate the center of mass offset */
      const btTransform& cCenterOfMassOffset = btTransform(
         btQuaternion(0.0f, 0.0f, 0.0f, 1.0f),
         btVector3(0.0f, -THYMIO_HEIGHT * 0.5f, 0.0f));
      /* Initialize mass and inertia to zero (static object) */
      Real fMass = 0.0f;
      btVector3 cInertia(0.0f, 0.0f, 0.0f);
      /* If the box is movable calculate its mass and inertia */
      if(c_thymio.GetEmbodiedEntity().IsMovable()) {
         ptrShape -> calculateLocalInertia(Thymio_MASS, cInertia);
      }
      /* Use the default friction */
      btScalar fFriction = GetEngine().GetDefaultFriction();
      /* Set up the body */
      CBody* m_pcBody = new CBody(*this,
                                  sAnchor,
                                  ptrShape,
                                  CBody::SData(cStartTransform,
                                               cCenterOfMassOffset,
                                               cInertia,
                                               fMass,
                                               fFriction));
      /* Transfer the body to the base class */
      m_vecBodies.push_back(m_pcBody);
      /* Synchronize with the entity in the space */
      UpdateEntityStatus();
   }
   
   /****************************************/
   /****************************************/
   
   CDynamics3DThymio::~CDynamics3DThymio() {
      /* Delete the body */
      delete m_pcBody;
   }
   
   /****************************************/
   /****************************************/

   REGISTER_STANDARD_DYNAMICS3D_OPERATIONS_ON_ENTITY(CBoxEntity, CDynamics3DThymio);

   /****************************************/
   /****************************************/

}
