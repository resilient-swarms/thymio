/**
 * @file <argos3/plugins/robots/Thymio/simulator/Thymio_measures.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "Thymio_measures.h"

/****************************************/
/****************************************/

const Real THYMIO_LENGHT 	= 0.11;				//measured from Thymio CAD files
const Real THYMIO_WIDTH 	= 0.085;			//measured from Thymio CAD files (Without the curve in the front)
const Real THYMIO_HEIGHT 	= 0.04;				//measured from Thymio CAD files from base to top (elevation ignored)
const Real INTERWHEEL_DISTANCE = 0.09;			//measured from Thymio CAD files (interwheel center to center distance)	
const Real WHEEL_RADIUS		= 0.022;			//measured from Thymio CAD files
const Real WHEEL_WIDTH		= 0.0195;			//measured from Thymio CAD files
const Real THYMIO_BASE_ELEVATION = 0.011; 		//measured from Thymio CAD files
const Real THYMIO_SENSORS_RING_RADIUS = 0.11;	
const Real THYMIO_PROXIMITY_SENSOR_RANGE = 0.1; //10cm
const Real THYMIO_PROXIMITY_SENSOR_HEIGHT = 0.06 ; //measured from Thymio CAD files
const Real THYMIO_XOFFSET				= (THYMIO_WIDTH/2)- 0.0285; //measured from Thymio CAD files (wheels distance from rear is 2.85cm)

// const Real Thymio_BASE_RADIUS    = 0.0704;
// const Real Thymio_BASE_ELEVATION = 0.0047;
// const Real Thymio_BASE_HEIGHT    = 0.053;
// const Real Thymio_BASE_TOP       = Thymio_BASE_ELEVATION + Thymio_BASE_HEIGHT;
const Real THYMIO_BASE_TOP       	= THYMIO_BASE_ELEVATION + THYMIO_HEIGHT;

const Real Thymio_WHEEL_RADIUS        = 0.021;
const Real Thymio_WHEEL_DISTANCE      = 0.1054;
const Real Thymio_HALF_WHEEL_DISTANCE = Thymio_WHEEL_DISTANCE * 0.5;

// const Real Thymio_IR_SENSORS_RING_ELEVATION = 0.0145;
// const Real Thymio_IR_SENSORS_RING_RADIUS    = Thymio_BASE_RADIUS;
// const Real Thymio_IR_SENSORS_RING_RANGE     = 0.12;

// const Real Thymio_ULTRASOUND_SENSORS_RING_ELEVATION = 0.0145;
// const Real Thymio_ULTRASOUND_SENSORS_RING_RADIUS    = Thymio_BASE_RADIUS;
// const CRange<Real> Thymio_ULTRASOUND_SENSORS_RING_RANGE(0.25, 2.0);

const CVector2 THYMIO_IR_SENSORS_GROUND_OFFSET[2] = {
   CVector2(0.0115,  0.072),
   CVector2(0.0115,  0.072),
};

const CVector3 Thymio_LEDS_OFFSET[3] = {
   CVector3( 0.04,  0.025, THYMIO_BASE_TOP),
   CVector3(-0.05,  0.000, THYMIO_BASE_TOP),
   CVector3( 0.04, -0.025, THYMIO_BASE_TOP)
};

// const Real Thymio_LIDAR_ELEVATION          = Thymio_BASE_TOP;
// const Real Thymio_LIDAR_SENSORS_FAN_RADIUS = Thymio_BASE_RADIUS;
// const CRadians 		Thymio_LIDAR_ANGLE_SPAN(ToRadians(CDegrees(210.0)));
// const CRange<Real> 	Thymio_LIDAR_SENSORS_RING_RANGE(0.02, 4.0);

/****************************************/
/****************************************/
