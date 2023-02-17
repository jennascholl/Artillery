/*************************************************************
 * 1. Name:
 *      Jenna Scholl and Neil Reed
 * 2. Assignment Name:
 *      Lab 07: Artillery Prorotype
 * 3. Assignment Description:
 *      Simulate an artillery shot
 * 4. What was the hardest part? Be as specific as possible.
 *      
 * 5. How long did it take for you to complete the assignment?
 *      
 *****************************************************************/

#include <iostream>
#include "acceleration.h"
#include "angle.h"
#include "velocity.h"
#include "position.h"

#define _USE_MATH_DEFINES    // for M_PI
#include <math.h>            // for sin and cos
#include <map>

#define INITIAL_VELOCITY 827.0  //Initial velocity is 827 m/s

using namespace std;

/*********************************
* LINEAR INTERPOLATION
* Takes two points and the first part of a point in between them,
* and finds the missing component 
* (x1 - x0) / (y1 - Y0)  =  (x - x0) / (y - y0)
* Solving for 'y'
********************************/
double linearInterpolation(double x0, double y0, double x1, double y1, double x)
{
   return y0 + ((x - x0) * (y1 - y0)) / (x1 - x0);
}

/*********************************
* CALCULATE DRAG COEFFICIENT
* Determine the drag coefficient at 
* a given speed in Mach
********************************/
double calculateDragC(double mach)    
{
   // a lookup table for drag coefficient (second) according to Mach (first)
   std::map<double, double> const dragTable 
   {
         {0.300, 0.1629}, {0.500, 0.1659}, {0.700, 0.2031}, {0.890, 0.2597}, 
         {0.920, 0.3010}, {0.960, 0.3287}, {0.980, 0.4002}, {1.000, 0.4259},
         {1.020, 0.4335}, {1.060, 0.4483}, {1.240, 0.4064}, {1.530, 0.3663}, 
         {1.990, 0.2897}, {2.870, 0.2297}, {2.890, 0.2306}, {5.000, 0.2656} 
   };

   // iterate through the drag table to see where our mach falls
   for (auto it = dragTable.begin(); it != dragTable.end(); it++)
   {
      // if our mach is in the table, return the corresponding value
      if (it->first == mach)
         return it->second;
      // otherwise, interpolate between the two closest values
      else if (it->first > mach)
         return linearInterpolation(it->first, it->second, it--->first, it->second, mach);
   }
}

/*********************************
* CALCULATE DENSITY
* Determine the air density at a given altitude
********************************/
double calculateDensity(double altitude)
{
   // a lookup table for air density (second) according to altitude (first)
   std::map<double, double> const densityTable
   {
         {    0.0, 1.2250000}, { 1000.0, 1.1120000}, { 2000.0, 1.0070000}, { 3000.0, 0.9093000},
         { 4000.0, 0.8194000}, { 5000.0, 0.7364000}, { 6000.0, 0.6601000}, { 7000.0, 0.5900000},
         { 8000.0, 0.5258000}, { 9000.0, 0.4671000}, {10000.0, 0.4135000}, {15000.0, 0.1948000},
         {20000.0, 0.0889100}, {25000.0, 0.0400800}, {30000.0, 0.0184100}, {40000.0, 0.0039960},
         {50000.0, 0.0010270}, {60000.0, 0.0003097}, {70000.0, 0.0000828}, {80000.0, 0.0000185}
   };

   // iterate through the density table to see where our altitude falls
   for (auto it = densityTable.begin(); it != densityTable.end(); it++)
   {
      // if our altitude is in the table, return the corresponding value
      if (it->first == altitude)
         return it->second;
      // otherwise, interpolate between the two closest values
      else if (it->first > altitude)
         return linearInterpolation(it->first, it->second, it--->first, it->second, altitude);
   }
}

/*********************************
* CALCULATE SPEED OF SOUND
* Determine the speed of sound at a given altitude
********************************/
double interpolateSpeedOfSound(double altitude)
{
   // a lookup table for speed of sound (second) according to altitude (first)
   std::map<double, double> const soundTable
   {
         {    0.0, 340.0}, { 1000.0, 336.0}, { 2000.0, 332.0}, { 3000.0, 328.0},
         { 4000.0, 324.0}, { 5000.0, 320.0}, { 6000.0, 316.0}, { 7000.0, 312.0},
         { 8000.0, 308.0}, { 9000.0, 303.0}, {10000.0, 299.0}, {15000.0, 295.0},
         {20000.0, 295.0}, {25000.0, 295.0}, {30000.0, 305.0}, {40000.0, 324.0}
   };

   // iterate through the sound table to see where our altitude falls
   for (auto it = soundTable.begin(); it != soundTable.end(); it++)
   {
      // if our altitude is in the table, return the corresponding value
      if (it->first == altitude)
         return it->second;
      // otherwise, interpolate between the two closest values
      else if (it->first > altitude)
         return linearInterpolation(it->first, it->second, it--->first, it->second, altitude);
   }
}

/*********************************
* CALCULATE GRAVITY
* Determine the gravity at a given altitude
********************************/
double calculateGravity(double altitude)
{
   // a lookup table for gravity (second) according to altitude (first)
   std::map<double, double> const gravityTable
   {
         {    0.0, 9.807}, { 1000.0, 9.804}, { 2000.0, 9.801}, { 3000.0, 9.797},
         { 4000.0, 9.794}, { 5000.0, 9.791}, { 6000.0, 9.788}, { 7000.0, 9.785},
         { 8000.0, 9.782}, { 9000.0, 9.779}, {10000.0, 9.776}, {15000.0, 9.761},
         {20000.0, 9.745}, {25000.0, 9.730}
   };

   // iterate through the gravity table to see where our altitude falls
   for (auto it = gravityTable.begin(); it != gravityTable.end(); it++)
   {
      // if our altitude is in the table, return the corresponding value
      if (it->first == altitude)
         return it->second;
      // otherwise, interpolate between the two closest values
      else if (it->first > altitude)
         return linearInterpolation(it->first, it->second, it--->first, it->second, altitude);
   }
}

/*********************************
* CALCULATE DRAG FORCE
* Calculates the drag force from a drag coefficient,
* dendity of the air, velocity, and surface area
* d = 1/2 c p v^2 a
********************************/
double calculateDragForce(double dragC, double density, double velocity, double area)
{
   return (0.5 * dragC * density * (velocity * velocity) * area); 
}

/*********************************
* CALCULATE SURFACE AREA
* Calculates the area of a circle given a radius
* a = pi r^2
**********************************/
double calculateCircleArea(double radius)
{
   return M_PI * (radius * radius);
}

/*********************************
* CALCULATE FORCE
* Calculates force from mass in kg times acceleration in m/(s^2)
* f = m a
********************************/
double calculateForce(double mass, double acceleration)
{
   return mass * acceleration;
}

/********************************
 * PROMPT
 * A generic function to prompt the user for a double
 *******************************/
double prompt(string message)
{
   double value = 0.0;
   cout << message;
   cin >> value;
   return value;
}


/*********************************
* SIMULATE
* Simulate the artillery shot untill it hits the ground
********************************/
void simulate(Angle angle)
{
   Velocity velocity = Velocity(INITIAL_VELOCITY, angle);                               
   double surface_area = calculateCircleArea(0.15489 / 2.0); //Diameter of shot is 0.15489m
   double density = 1.225;                                   //Initial air density at 0m altitude is 1.225 kg/(m^2)
   double mass = 46.7;                                       //The mass of the shot is 46.7kg
   double altitude = 0.0;                                    //Initial altitude is 0

   do
   {

   } while (altitude > 0.0);
}

/*********************************
* MAIN
********************************/
int main()
{
   Angle angle = Angle(prompt("What is the angle of the Howizter, where 0 is up?: "));
   Velocity v = Velocity(0.0, angle);

   simulate(angle);
}

