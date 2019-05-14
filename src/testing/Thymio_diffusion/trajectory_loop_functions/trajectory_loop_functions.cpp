#include "trajectory_loop_functions.h"

/****************************************/
/****************************************/

/*
 * To reduce the number of waypoints stored in memory,
 * consider two robot positions distinct if they are
 * at least MIN_DISTANCE away from each other
 * This constant is expressed in meters
 */
static const Real MIN_DISTANCE = 0.05f;
/* Convenience constant to avoid calculating the square root in PostStep() */
static const Real MIN_DISTANCE_SQUARED = MIN_DISTANCE * MIN_DISTANCE;

/****************************************/
/****************************************/

void CTrajectoryLoopFunctions::Init(TConfigurationNode& t_tree)
{
    /*
    * Go through all the robots in the environment
    * and create an entry in the waypoint map for each of them
    */
    /* Get the map of all Thymios from the space */
    CSpace::TMapPerType& tFBMap = GetSpace().GetEntitiesByType("Thymio");
    try
    {
        robots.open("s");
    } catch (std::exception e)
    {
        e.what();
    }

    /* Go through them */
    for(CSpace::TMapPerType::iterator it = tFBMap.begin();
        it != tFBMap.end();
        ++it)
    {
        /* Create a pointer to the current Thymio */
        CThymioEntity* pcFB = any_cast<CThymioEntity*>(it->second);
        /* Create a waypoint vector */
        m_tWaypoints[pcFB] = std::vector<CVector3>();
        /* Add the initial position of the robot */
        m_tWaypoints[pcFB].push_back(pcFB->GetEmbodiedEntity().GetOriginAnchor().Position);
        robots << pcFB->GetId() <<","<<
                  pcFB->GetEmbodiedEntity().GetOriginAnchor().Position.GetX()<<","<<
                  pcFB->GetEmbodiedEntity().GetOriginAnchor().Position.GetY()<<"\n";

    }
}

/****************************************/
/****************************************/

void CTrajectoryLoopFunctions::Reset()
{
    /*
    * Clear all the waypoint vectors
    */
    /* Get the map of all Thymios from the space */
    CSpace::TMapPerType& tFBMap = GetSpace().GetEntitiesByType("Thymio");
    /* Go through them */
    for(CSpace::TMapPerType::iterator it = tFBMap.begin();
        it != tFBMap.end();
        ++it) {
        /* Create a pointer to the current Thymio */
        CThymioEntity* pcFB = any_cast<CThymioEntity*>(it->second);
        /* Clear the waypoint vector */
        m_tWaypoints[pcFB].clear();
        /* Add the initial position of the Thymio */
        m_tWaypoints[pcFB].push_back(pcFB->GetEmbodiedEntity().GetOriginAnchor().Position);

    }
    robots.close();
}

/****************************************/
/****************************************/

void CTrajectoryLoopFunctions::PostStep()
{
    /* Get the map of all foot-bots from the space */
    CSpace::TMapPerType& tFBMap = GetSpace().GetEntitiesByType("Thymio");
    /* Go through them */
    for(CSpace::TMapPerType::iterator it = tFBMap.begin();
        it != tFBMap.end();
        ++it) {
        /* Create a pointer to the current Thymio */
        CThymioEntity* pcFB = any_cast<CThymioEntity*>(it->second);
        /* Add the current position of the Thymio if it's sufficiently far from the last */
        if(SquareDistance(pcFB->GetEmbodiedEntity().GetOriginAnchor().Position,
                          m_tWaypoints[pcFB].back()) > MIN_DISTANCE_SQUARED)
        {
            m_tWaypoints[pcFB].push_back(pcFB->GetEmbodiedEntity().GetOriginAnchor().Position);

            robots << pcFB->GetId() <<","<<
                      pcFB->GetEmbodiedEntity().GetOriginAnchor().Position.GetX() <<","<<
                      pcFB->GetEmbodiedEntity().GetOriginAnchor().Position.GetY() <<"\n";
        }
        /*if(pcFB->GetEmbodiedEntity().IsCollidingWithSomething())
        {
            std::cout<<"Is colliding"<<std::endl;
        }
        else{
            std::cout<<"Is NOT colliding"<<std::endl;
        }*/
    }
}

/****************************************/
/****************************************/

REGISTER_LOOP_FUNCTIONS(CTrajectoryLoopFunctions, "trajectory_loop_functions")
