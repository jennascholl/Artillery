/*************************************************************
 * 1. Name:
 *      Jenna Scholl and Neil Reed
 * 2. Assignment Name:
 *      Lab 07: Artillery Prorotype
 * 3. Assignment Description:
 *      Simulate an artillery shot
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was getting the physics to reflect
 *      the example in the instructions. While it is accurate
 *      for small distances, it seems to get off slightly
 *      over long distances.
 * 5. How long did it take for you to complete the assignment?
 *      6 hours
 *****************************************************************/

#include <iostream>
#include "acceleration.h"
#include "direction.h"
#include "velocity.h"
#include "position.h"

#define _USE_MATH_DEFINES    // For M_PI
#include <map>               // For linearInterpolation()

using namespace std;

const double INITIAL_V = 827.00;     // Initial velocity in m/s
const double TIME = 0.01;            // The rate at which time passes
const double DIAMETER = 0.15489;     // The diameter of the projectile in m
const double MASS = 46.7;            // The mass of the shot in kg

/*********************************
* LINEAR INTERPOLATION
* Takes two points and the first part of a point in between them,
* and finds the missing component 
* (x1 - x0) / (y1 - Y0)  =  (x - x0) / (y - y0)
* Solving for 'y'
********************************/
long double linearInterpolation(long double x0, long double y0, 
   long double x1, long double y1, long double x)
{
   return y0 + ((x - x0) * (y1 - y0)) / (x1 - x0);
}

/*********************************
* LOOKUP VALUE
* Searches for a value using a given table,
* using linear interpolation when the value
* is not found
********************************/
long double lookupValue(const std::map<long double, long double> & table, 
   const long double & value)
{
   // If the value is outside our table's range, return the closest value to it
   if (value < table.begin()->first)
      return table.begin()->second;
   else if (value > table.rbegin()->first)
      return table.rbegin()->second;

   // Otherwise, iterate through the table to see where our value falls
   for (auto it = table.begin(); it != table.end(); it++)
   {
      // If our value is in the table, return the corresponding value
      if (it->first == value)
         return it->second;
      // Otherwise, interpolate between the two closest values
      else if (it->first > value)
         return linearInterpolation(it->first, it->second, it--->first, it->second, value);
   }
}

/*********************************
* CALCULATE DRAG COEFFICIENT
* Determine the drag coefficient at 
* a given speed in Mach
********************************/
long double calculateDragC(long const double & mach)    
{
   // A lookup table for drag coefficient (second) according to Mach (first)
   std::map<long double, long double> const dragTable 
   {
         {0.300, 0.1629}, {0.500, 0.1659}, {0.700, 0.2031}, {0.890, 0.2597}, 
         {0.920, 0.3010}, {0.960, 0.3287}, {0.980, 0.4002}, {1.000, 0.4258},
         {1.020, 0.4335}, {1.060, 0.4483}, {1.240, 0.4064}, {1.530, 0.3663}, 
         {1.990, 0.2897}, {2.870, 0.2297}, {2.890, 0.2306}, {5.000, 0.2656} 
   };

   return lookupValue(dragTable, mach);
}

/*********************************
* CALCULATE DENSITY
* Determine the air density at a given altitude
********************************/
long double calculateDensity(const long double & altitude)
{
   // A lookup table for air density (second) according to altitude (first)
   std::map<long double, long double> const densityTable
   {
         {    0.0, 1.2250000}, { 1000.0, 1.1120000}, { 2000.0, 1.0070000}, { 3000.0, 0.9093000},
         { 4000.0, 0.8194000}, { 5000.0, 0.7364000}, { 6000.0, 0.6601000}, { 7000.0, 0.5900000},
         { 8000.0, 0.5258000}, { 9000.0, 0.4671000}, {10000.0, 0.4135000}, {15000.0, 0.1948000},
         {20000.0, 0.0889100}, {25000.0, 0.0400800}, {30000.0, 0.0184100}, {40000.0, 0.0039960},
         {50000.0, 0.0010270}, {60000.0, 0.0003097}, {70000.0, 0.0000828}, {80000.0, 0.0000185}
   };

   return lookupValue(densityTable, altitude);
}

/*********************************
* CALCULATE SPEED OF SOUND
* Determine the speed of sound at a given altitude
********************************/
long double calculateSpeedOfSound(const long double & altitude)
{
   // A lookup table for speed of sound (second) according to altitude (first)
   std::map<long double, long double> const soundTable
   {
         {    0.0, 340.0}, { 1000.0, 336.0}, { 2000.0, 332.0}, { 3000.0, 328.0},
         { 4000.0, 324.0}, { 5000.0, 320.0}, { 6000.0, 316.0}, { 7000.0, 312.0},
         { 8000.0, 308.0}, { 9000.0, 303.0}, {10000.0, 299.0}, {15000.0, 295.0},
         {20000.0, 295.0}, {25000.0, 295.0}, {30000.0, 305.0}, {40000.0, 324.0}
   };

   return lookupValue(soundTable, altitude);
}

/*********************************
* CALCULATE GRAVITY
* Determine the gravity at a given altitude
********************************/
long double calculateGravity(const long double & altitude)
{
   // A lookup table for gravity (second) according to altitude (first)
   std::map<long double, long double> const gravityTable
   {
         {    0.0, 9.807}, { 1000.0, 9.804}, { 2000.0, 9.801}, { 3000.0, 9.797},
         { 4000.0, 9.794}, { 5000.0, 9.791}, { 6000.0, 9.788}, { 7000.0, 9.785},
         { 8000.0, 9.782}, { 9000.0, 9.779}, {10000.0, 9.776}, {15000.0, 9.761},
         {20000.0, 9.745}, {25000.0, 9.730}
   };

   return lookupValue(gravityTable, altitude);
}

/*********************************
* CALCULATE DRAG FORCE
* Calculates the drag force from a drag coefficient,
* density of the air, velocity, and surface area
* d = 1/2 c p v^2 a
********************************/
long double calculateDragForce(const long double & dragC, const long double & density, 
   const long double & velocity, const long double & area)
{
   return (0.5 * dragC * density * (velocity * velocity) * area); 
}

/*********************************
* CALCULATE SURFACE AREA
* Calculates the area of a circle given a radius
* a = pi r^2
**********************************/
long double calculateCircleArea(const long double & radius)
{
   return M_PI * (radius * radius);
}

/*********************************
* CALCULATE ACCELERATION
* Calculates force from mass in kg times acceleration in m/(s^2)
* f = m a
********************************/
long double calculateAcceleration(const long double & force, const long double & mass)
{
   return force / mass;
}

/*********************************
* CALCULATE ANGLE
* Given dx and dy, returns an angle
* in radians
********************************/
long double calculateAngle(long double dx, long double dy)
{
   return atan2(dx, dy);
}

/********************************
 * PROMPT
 * A generic function to prompt the user for a double
 *******************************/
double prompt(const string & message)
{
   double value = 0.0;
   cout << message;
   cin >> value;
   return value;
}

/********************************
 * DISPLAY
 * A function to display the results
 * of the simulation
 *******************************/
void display(const double & distance, const long double & time)
{
   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(1);
   cout << "Distance:\t" << distance << "m \tHang Time:\t" << time << "s" << endl << endl;
}

/*********************************
* SIMULATE
* Simulate the artillery shot untill it hits the ground
********************************/
void simulate(Direction & angle, double & airTime, double & distance)
{
   Position pt = Position(0.0, 0.0);                        // The projectile's current position
   Position lastPt = Position();                            // The projectile's last known position
   Velocity v(sin(angle.getRadians()) * INITIAL_V, 
      cos(angle.getRadians()) * INITIAL_V);                 // The projectile's velocity
   long double area = calculateCircleArea(DIAMETER / 2.0);  // Surface area of the front of the missile
   double total = 0.00;                                     // Total time passed since launch

   do
   {
      // Update the environmental factors
      long double vSound = calculateSpeedOfSound(pt.getMetersY());
      long double vMach = v.getSpeed() / vSound;
      long double dragC = calculateDragC(vMach);
      long double dragForce = calculateDragForce(dragC, calculateDensity(pt.getMetersY()),
         v.getSpeed(), area);
      long double gravity = calculateGravity(pt.getMetersY());

      // Update the projectile's states
      angle.setRadians(calculateAngle(v.getDX(), v.getDY()));

      long double acc = calculateAcceleration(dragForce, MASS);
      Acceleration acceleration(-sin(angle.getRadians()) * acc,
         -cos(angle.getRadians()) * acc - gravity);

      v.add(acceleration, TIME);

      lastPt = pt;       // Update the projectile's last known position
      pt.addMetersX(v.getDX() * TIME + 0.5 * acceleration.getDDX() * TIME * TIME);
      pt.addMetersY(v.getDY() * TIME + 0.5 * acceleration.getDDY() * TIME * TIME);

      // Update the time passed
      total += TIME;

   } while (pt.getMetersY() > 0.0); // Stop when we hit the ground

   // Find the distance traveled and time in the air
   if (pt.getMetersY() != 0)
   {
      distance = linearInterpolation(pt.getMetersY(), pt.getMetersX(),
         lastPt.getMetersY(), lastPt.getMetersX(), 0.0);
      airTime = linearInterpolation(pt.getMetersY(), total,
         lastPt.getMetersY(), total - TIME, 0.0);
   }
   else
   {
      distance = pt.getMetersX();
      airTime = total;
   }
}

/********************************
* MAIN
********************************/
//int main()
//{
//   while (true)
//   {
//      // Set the variables
//      Angle angle = Angle(prompt("What is the angle of the Howizter, where 0 is up?: "));
//      double airTime = 0.0;
//      double distance = 0.0;
//
//      // Run the simulator
//      simulate(angle, airTime, distance);
//      display(distance, airTime);
//   }
//}

