/***********************************************************************
 * Header File:
 *    PHYSICS : All the physics stuff
 * Author:
 *    Jenna Scholl
 * Summary:
 *    Laws of motion, effects of gravity, wind resistance, etc.
 ************************************************************************/

#pragma once

#include <iostream>
#include "acceleration.h"
#include "direction.h"
#include "velocity.h"
#include "position.h"

#define _USE_MATH_DEFINES    // For M_PI
#include "math.h"
#include <cassert>

 /*********************************
 * AREA FROM RADIANS
 * Compute the area of a circle from a radius
 *    area = pi * radius ^ 2
 **********************************/
inline double areaFromRadius(double radius)
{
   return M_PI * radius * radius;
}

/*********************************
* ANGLE FROM VELOCITY
* Given dx and dy, returns an angle
* in radians
********************************/
long double angleFromVelocity(long double dx, long double dy)
{
   return atan2(dx, dy);
}

/*********************************
* FORCE FROM DRAG
* Determine the drag on a shell based on:
*     density  : the density of the air
*     drag     : the drag coefficient of the air
*     radius   : the radius of the shell (m)
*     velocity : the velocity of the shell (m/s)
* Equation:
*     force = 1/2 * density * drag * area * velocity ^ 2
********************************/
inline double forceFromDrag(double density, double drag, double radius, double velocity)
{
   // compute the area
   double area = areaFromRadius(radius);

   // compute the drag
   return 0.5 * density * drag * area * velocity * velocity;
}

/*********************************
* ACCELERATION FROM FORCE
* How much acceleration to expect from a given force:
*     force        : N
*     mass         : kg
*     acceleration : m / s ^ 2
* Equation:
*     force = mass * acceleration
********************************/
inline double accelerationFromForce(double force, double mass)
{
   assert(mass != 0);
   return force / mass;
}

/*********************************
* VELOCITY FROM ACCELERATION
* How much velocity will result from a given acceleration
*     acceleration : m / s ^ 2
*     time         : s
* Equation:
*     velocity = acceleration * time
********************************/
inline double velocityFromAcceleration(double acceleration, double time)
{
   return acceleration * time;
}

/*********************************
* MAPPING
* A simple structure to represent domain and range
* for linear interpolation
********************************/
struct Mapping
{
   double domain;
   double range;
};


/*********************************
* LINEAR INTERPOLATION
* Takes two points and the domain of a point in between them,
* and finds the range
* (r1 - r0) / (d1 - d0)  =  (r - r0) / (d - d0)
* Solving for 'r' (range)
********************************/
inline double linearInterpolation(double d0, double r0, 
                                  double d1, double r1, 
                                  double d)
{
   if (d1 - d0 != 0)
      return r0 + (r1 - r0) * (d - d0) / (d1 - d0);
   else
      return r0;
}

/*********************************
* LINEAR INTERPOLATION
* Takes two mapping values and a domain and finds
* the missing range
* (r1 - r0) / (d1 - d0)  =  (r - r0) / (d - d0)
* Solving for 'r' (range)
********************************/
inline double linearInterpolation(const Mapping & zero,
                                  const Mapping & one, 
                                  double d) 
{
   return linearInterpolation(zero.domain, zero.range,
                              one.domain, one.range,
                              d);
}

/*********************************
* LINEAR INTERPOLATION
* From a list of domains and ranges, linear interpolate
*********************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain)
{
   // if the domain is less than the smallest value, just return the smallest range
   if (domain < mapping[0].domain)
      return mapping[0].range;

   // otherwise, iterate through the table to see where our value falls
   for (int i = 0; i < numMapping - 1; i++)
   {
      if (mapping[i + 0].domain <= domain && domain <= mapping[i + 1].domain)
         return linearInterpolation(mapping[i + 0], mapping[i + 1], domain);
   }

   return mapping[numMapping - 1].range;
}

/*********************************
* GRAVITY FROM ALTITUDE
* Determine gravity coefficient based on altitude
*********************************/
double gravityFromAltitude(double altitude)
{
   const Mapping gravityMapping[] =
   {
     // altitude, gravity
      { 0.0	  ,   9.807},
      { 1000.0,   9.804},
      { 2000.0,   9.801},
      { 4000.0,   9.794},
      { 5000.0,   9.791},
      { 6000.0,   9.788},
      { 7000.0,   9.785},
      { 8000.0,   9.782},
      { 9000.0,   9.779},
      {10000.0,	9.776},
      {15000.0,   9.761},
      {20000.0,	9.745},
      {25000.0,   9.730}
   };

   // look up the value
   double gravity = linearInterpolation(gravityMapping, 
      sizeof(gravityMapping) / sizeof(gravityMapping[0]), altitude);

   return gravity;
}

/*********************************
* SPEED OF SOUND FROM ALTITUDE
* Determine the speed of sound based on altitude
*********************************/
double speedOfSoundFromAltitude(double altitude)
{
   const Mapping speedMapping[] =
   {
     // altitude, speed of sound
      {0,	   340},
      {1000,   336},
      {2000,	332},
      {3000,	328},
      {5000,	320},
      {6000,	316},
      {7000,	312},
      {8000,	308},
      {9000,	303},
      {10000,	299},
      {15000,	295},
      {20000,	295},
      {25000,	295},
      {30000,	305},
      {40000,	324}
   };

   // look up the value
   double mach = linearInterpolation(speedMapping, sizeof(speedMapping) / sizeof(speedMapping[0]), altitude);

   return mach;
}

/*********************************
* MACH FROM SPEED
* Determine the mach for a given speed and altitude
* Equation:
*     mach = speed / speed of sound
*********************************/
double machFromSpeed(double speed, double altitude)
{
   // compute the speed of sound at this altitude
   double speedOfSound = speedOfSoundFromAltitude(altitude);

   return speed / speedOfSound;
}

/*********************************
* DRAG FROM SPEED
* Determine the drag coefficient for a given speed and altitude
*********************************/
double dragFromSpeed(double speed, double altitude)
{
   const Mapping dragSpeed[] =
   {
      // mach, drag
       {0.300,	0.1629},
       {0.500, 0.1659},
       {0.700,	0.2031},
       {0.890,	0.2597},
       {0.920,	0.3010},
       {0.960,	0.3287},
       {0.980,	0.4002},
       {1.000,	0.4258},
       {1.020,	0.4335},
       {1.060,	0.4483},
       {1.240,	0.4064},
       {1.530,	0.3663},
       {1.990,	0.2897},
       {2.870,	0.2297},
       {2.890,	0.2306},
       {5.000,	0.2656}
   };

   // compute mach at this altitude
   double mach = machFromSpeed(speed, altitude);

   // look up the value
   double drag = linearInterpolation(dragSpeed, sizeof(dragSpeed) / sizeof(dragSpeed[0]), mach);

   return drag;
}

/*********************************
* DENSITY FROM ALTITUDE
* Determine the air density at a given altitude
********************************/
double densityFromAltitude(double altitude)
{
   const Mapping densityMapping[] = 
   {
    // altitude, density
    {    0.0, 1.2250000}, 
    { 1000.0, 1.1120000}, 
    { 2000.0, 1.0070000}, 
    { 3000.0, 0.9093000},
    { 4000.0, 0.8194000}, 
    { 5000.0, 0.7364000}, 
    { 6000.0, 0.6601000}, 
    { 7000.0, 0.5900000},
    { 8000.0, 0.5258000}, 
    { 9000.0, 0.4671000}, 
    {10000.0, 0.4135000}, 
    {15000.0, 0.1948000},
    {20000.0, 0.0889100}, 
    {25000.0, 0.0400800}, 
    {30000.0, 0.0184100}, 
    {40000.0, 0.0039960},
    {50000.0, 0.0010270}, 
    {60000.0, 0.0003097}, 
    {70000.0, 0.0000828}, 
    {80000.0, 0.0000185}
   };

   // look up the value
   double density = linearInterpolation(densityMapping, sizeof(densityMapping) / sizeof(densityMapping[0]), altitude);

   return density;
}



/*********************************
* CALCULATE DRAG COEFFICIENT
* Determine the drag coefficient at
* a given speed in Mach
********************************/
//long double calculateDragC(long const double& mach)
//{
//   // A lookup table for drag coefficient (second) according to Mach (first)
//   std::map<long double, long double> const dragTable
//   {
//         {0.300, 0.1629}, {0.500, 0.1659}, {0.700, 0.2031}, {0.890, 0.2597},
//         {0.920, 0.3010}, {0.960, 0.3287}, {0.980, 0.4002}, {1.000, 0.4258},
//         {1.020, 0.4335}, {1.060, 0.4483}, {1.240, 0.4064}, {1.530, 0.3663},
//         {1.990, 0.2897}, {2.870, 0.2297}, {2.890, 0.2306}, {5.000, 0.2656}
//   };
//
//   return lookupValue(dragTable, mach);
//}

/*********************************
* CALCULATE SPEED OF SOUND
* Determine the speed of sound at a given altitude
********************************/
//long double calculateSpeedOfSound(const long double& altitude)
//{
//   // A lookup table for speed of sound (second) according to altitude (first)
//   std::map<long double, long double> const soundTable
//   {
//         {    0.0, 340.0}, { 1000.0, 336.0}, { 2000.0, 332.0}, { 3000.0, 328.0},
//         { 4000.0, 324.0}, { 5000.0, 320.0}, { 6000.0, 316.0}, { 7000.0, 312.0},
//         { 8000.0, 308.0}, { 9000.0, 303.0}, {10000.0, 299.0}, {15000.0, 295.0},
//         {20000.0, 295.0}, {25000.0, 295.0}, {30000.0, 305.0}, {40000.0, 324.0}
//   };
//
//   return lookupValue(soundTable, altitude);
//}

/*********************************
* CALCULATE GRAVITY
* Determine the gravity at a given altitude
********************************/
//long double calculateGravity(const long double& altitude)
//{
//   // A lookup table for gravity (second) according to altitude (first)
//   std::map<long double, long double> const gravityTable
//   {
//         {    0.0, 9.807}, { 1000.0, 9.804}, { 2000.0, 9.801}, { 3000.0, 9.797},
//         { 4000.0, 9.794}, { 5000.0, 9.791}, { 6000.0, 9.788}, { 7000.0, 9.785},
//         { 8000.0, 9.782}, { 9000.0, 9.779}, {10000.0, 9.776}, {15000.0, 9.761},
//         {20000.0, 9.745}, {25000.0, 9.730}
//   };
//
//   return lookupValue(gravityTable, altitude);
//}

/*********************************
* CALCULATE ACCELERATION
* Calculates force from mass in kg times acceleration in m/(s^2)
* f = m a
********************************/
//long double calculateAcceleration(const long double& force, const long double& mass)
//{
//   return force / mass;
//}

/*********************************
* CALCULATE ANGLE
* Given dx and dy, returns an angle
* in radians
********************************/
//long double calculateAngle(long double dx, long double dy)
//{
//   return atan2(dx, dy);
//}