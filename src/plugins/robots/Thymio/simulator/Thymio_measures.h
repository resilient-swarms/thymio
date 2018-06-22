/**
 * @file <argos3/plugins/robots/Thymio/simulator/Thymio_measures.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef Thymio_MEASURES_H
#define Thymio_MEASURES_H

#include <argos3/core/utility/datatypes/datatypes.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/math/vector3.h>

using namespace argos;

extern const Real THYMIO_HEIGHT;
extern const Real THYMIO_WIDTH;
extern const Real THYMIO_LENGHT;
extern const Real INTERWHEEL_DISTANCE;
extern const Real WHEEL_RADIUS;
extern const Real WHEEL_WIDTH;
extern const Real THYMIO_BASE_ELEVATION;
extern const Real THYMIO_SENSORS_RING_RADIUS;
extern const Real THYMIO_PROXIMITY_SENSOR_RANGE;
extern const Real THYMIO_PROXIMITY_SENSOR_HEIGHT;
extern const Real THYMIO_XOFFSET;

// extern const Real Thymio_BASE_RADIUS;
// extern const Real Thymio_BASE_ELEVATION;
// extern const Real Thymio_BASE_HEIGHT;
// extern const Real Thymio_BASE_TOP;
extern const Real THYMIO_BASE_TOP;

extern const Real Thymio_WHEEL_RADIUS;
extern const Real Thymio_WHEEL_DISTANCE;
extern const Real Thymio_HALF_WHEEL_DISTANCE;

// extern const Real Thymio_IR_SENSORS_RING_ELEVATION;
// extern const Real Thymio_IR_SENSORS_RING_RADIUS;
// extern const Real Thymio_IR_SENSORS_RING_RANGE;

// extern const Real Thymio_ULTRASOUND_SENSORS_RING_ELEVATION;
// extern const Real Thymio_ULTRASOUND_SENSORS_RING_RADIUS;
// extern const CRange<Real> Thymio_ULTRASOUND_SENSORS_RING_RANGE;

extern const CVector2 THYMIO_IR_SENSORS_GROUND_OFFSET[2];

extern const CVector3 Thymio_LEDS_OFFSET[3];

// extern const Real Thymio_LIDAR_ELEVATION;
// extern const Real Thymio_LIDAR_SENSORS_FAN_RADIUS;
// extern const CRadians Thymio_LIDAR_ANGLE_SPAN;
// extern const CRange<Real> Thymio_LIDAR_SENSORS_RING_RANGE;

#endif
