/**
 * @file <argos3/plugins/robots/Thymio/simulator/Thymio_measures.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "Thymio_measures.h"

/****************************************/
/****************************************/

const Real THYMIO_LENGHT 	        = 0.11;		  //measured from Thymio CAD files
const Real THYMIO_WIDTH 	        = 0.085;		  //measured from Thymio CAD files (Without the curve in the front)
const Real THYMIO_HEIGHT 	        = 0.04;		  //measured from Thymio CAD files from base to top (elevation ignored)
const Real INTERWHEEL_DISTANCE     = 0.09;		  //measured from Thymio CAD files (interwheel center to center distance)	
const Real WHEEL_RADIUS		        = 0.022;		  //measured from Thymio CAD files
const Real WHEEL_WIDTH		        = 0.0195;		  //measured from Thymio CAD files
const Real THYMIO_BASE_ELEVATION   = 0.011; 		  //measured from Thymio CAD files
const Real THYMIO_SENSORS_RING_RADIUS     = 0.11;	
const Real THYMIO_PROXIMITY_SENSOR_RANGE  = 0.1; //10cm
const Real THYMIO_PROXIMITY_SENSOR_HEIGHT = 0.03 ; //measured from Thymio CAD files
const Real THYMIO_XOFFSET				= (THYMIO_WIDTH/2)- 0.0285; //measured from Thymio CAD files (wheels distance from rear is 2.85cm)

const Real THYMIO_BASE_TOP       	= THYMIO_BASE_ELEVATION + THYMIO_HEIGHT;

const Real Thymio_WHEEL_RADIUS        = 0.021;
const Real Thymio_WHEEL_DISTANCE      = 0.1054;
const Real Thymio_HALF_WHEEL_DISTANCE = Thymio_WHEEL_DISTANCE * 0.5;

const CVector2 THYMIO_IR_SENSORS_GROUND_OFFSET[2] = {
   CVector2(   0.072, 0.0115),
   CVector2(  -0.072,-0.0115),
};

const CRadians PROXIMITY_SENSOR_ANGLES[7] = {
   CRadians(0.69813),
   CRadians(0.34906),
   CRadians::ZERO,
   CRadians(-0.34906),
   CRadians(-0.69813),
   -CRadians::PI,
   -CRadians::PI
};

//measurements from https://github.com/enki-community/enki/blob/master/enki/robots/thymio2/Thymio2.cpp
const CVector3 PROXIMITY_SENSOR_OFFSET[7] = {
   CVector3(  0.062   , 0.0485  ,THYMIO_PROXIMITY_SENSOR_HEIGHT),
   CVector3(  0.075   , 0.0255  ,THYMIO_PROXIMITY_SENSOR_HEIGHT),
   CVector3(  0.0795  , 0       ,THYMIO_PROXIMITY_SENSOR_HEIGHT),
   CVector3(  0.075   ,-0.0255  ,THYMIO_PROXIMITY_SENSOR_HEIGHT),
   CVector3(  0.062   ,-0.0485  ,THYMIO_PROXIMITY_SENSOR_HEIGHT),
   CVector3( -THYMIO_WIDTH/2  , 0.0295  ,THYMIO_PROXIMITY_SENSOR_HEIGHT),
   CVector3( -THYMIO_WIDTH/2  ,-0.0295  ,THYMIO_PROXIMITY_SENSOR_HEIGHT),
};

const CVector3 Thymio_LEDS_OFFSET[8] = {
	//missing
   // CVector3( 0.04,  0.025, THYMIO_BASE_TOP),
   // CVector3(-0.05,  0.000, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   //circular ring leds 
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),

   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   //RGB top led
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // //RGB botom right led
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // //RGB botom left led
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // //buttons leds
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   //horizontal proximity leds
   //may need to swap x and ys -> swapped them for horizontal LEDs
   CVector3( 0.078, 0.015, THYMIO_BASE_TOP),
   CVector3( 0.043, 0.054, THYMIO_BASE_TOP),
   CVector3( 0.026, 0.104, THYMIO_BASE_TOP),
   CVector3( 0.023, 0.040, THYMIO_BASE_TOP),

   CVector3(-0.043, 0.020, THYMIO_BASE_TOP),
   CVector3(-0.078, 0.024, THYMIO_BASE_TOP),
   CVector3(-0.026,-0.015, THYMIO_BASE_TOP),
   CVector3(-0.023, 0.021, THYMIO_BASE_TOP),
   //vertical proximity LEDs
//   CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
//   CVector3( 0.04, -0.025, THYMIO_BASE_TOP)
   //RC LED
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   //sound
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   //temperature
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP),
   // CVector3( 0.04, -0.025, THYMIO_BASE_TOP)
};

/****************************************/
/****************************************/
