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
* INTERPOLATE DRAG
* Interpolate the drag from mach with the values from the chart we are given
********************************/
double interpolateDrag(double mach)    
{
   if (0.3 < mach < 0.5)
   {
      return linearInterpolation(0.3, 0.1659, 0.5, 0.1659, mach);
   }
   else if (0.5 < mach < 0.7)
   {
      return linearInterpolation(0.5, 0.1659, 0.7, 0.2031, mach);
   }
   else if (0.7 < mach < 0.89)
   {
      return linearInterpolation(0.7, 0.2031, 0.89, 0.2597, mach);
   }
   else if (0.89 < mach < 0.92)
   {
      return linearInterpolation(0.89, 0.2597, 0.92, 0.3010, mach);
   }
   else if (0.92 < mach < 0.96)
   {
      return linearInterpolation(0.92, 0.3010, 0.96, 0.3287, mach);
   }
   else if (0.96 < mach < 0.98)
   {
      return linearInterpolation(0.96, 0.3287, 0.98, 0.4002, mach);
   }
   else if (0.98 < mach < 1.0)
   {
      return linearInterpolation(0.98, 0.4002, 1.0, 0.4258, mach);
   }
   else if (1.0 < mach < 1.02)
   {
      return linearInterpolation(1.0, 0.4258, 1.02, 0.4335, mach);
   }
   else if (1.02 < mach < 1.06)
   {
      return linearInterpolation(1.02, 0.4335, 1.06, 0.4483, mach);
   }
   else if (1.06 < mach < 1.24)
   {
      return linearInterpolation(1.06, 0.4483, 1.24, 0.4064, mach);
   }
   else if (1.24 < mach < 1.53)
   {
      return linearInterpolation(1.24, 0.4064, 1.53, 0.3663, mach);
   }
   else if (1.53 < mach < 1.99)
   {
      return linearInterpolation(1.53, 0.3663, 1.99, 0.2897, mach);
   }
   else if (1.99 < mach < 2.87)
   {
      return linearInterpolation(1.99, 0.2897, 2.87, 0.2297, mach);
   }
   else if (2.87 < mach < 2.89)
   {
      return linearInterpolation(2.87, 0.2297, 2.89, 0.2306, mach);
   }
   else if (2.89 < mach < 5.0)
   {
      return linearInterpolation(2.89, 0.2306, 5.0, 0.2656, mach);
   }
}

/*********************************
* INTERPOLATE DENSITY
* Inrerpolates the density for a given altitude from the chart we are given
********************************/
double interpolateDensity(double altitude)
{
   if (0.0 < altitude < 1000.0)
   {
      return linearInterpolation(0.0, 1.2250000, 1000.0, 1.1120000, altitude);
   }
   else if (1000 < altitude < 2000)
   {
      return linearInterpolation(1000, 1.1120000, 2000, 1.0070000, altitude);
   }
   else if (2000 < altitude < 3000)
   {
      return linearInterpolation(2000, 1.0070000, 3000, 0.9093000, altitude);
   }
   else if (3000 < altitude < 4000)
   {
      return linearInterpolation(3000, 0.9093000, 4000, 0.8194000, altitude);
   }
   else if (4000 < altitude < 5000)
   {
      return linearInterpolation(4000, 0.8194000, 5000, 0.7364000
         , altitude);
   }
   else if (5000 < altitude < 6000)
   {
      return linearInterpolation(5000, 0.7364000
         , 6000, 0.6601000, altitude);
   }
   else if (6000 < altitude < 7000)
   {
      return linearInterpolation(6000, 0.6601000, 7000, 0.5900000, altitude);
   }
   else if (7000 < altitude < 8000)
   {
      return linearInterpolation(7000, 0.5900000, 8000, 0.5258000, altitude);
   }
   else if (8000 < altitude < 9000)
   {
      return linearInterpolation(8000, 0.5258000, 9000, 0.4671000, altitude);
   }
   else if (9000 < altitude < 10000)
   {
      return linearInterpolation(9000, 0.4671000, 10000, 0.4135000, altitude);
   }
   else if (10000 < altitude < 15000)
   {
      return linearInterpolation(10000, 0.4135000, 15000, 0.1948000
         , altitude);
   }
   else if (15000 < altitude < 20000)
   {
      return linearInterpolation(15000, 0.1948000
         , 20000, 0.0889100, altitude);
   }
   else if (20000 < altitude < 25000)
   {
      return linearInterpolation(20000, 0.0889100, 25000, 0.0400800, altitude);
   }
   else if (25000 < altitude < 30000)
   {
      return linearInterpolation(25000, 0.0400800, 30000, 0.0184100, altitude);
   }
   else if (30000 < altitude < 40000)
   {
      return linearInterpolation(30000, 0.0184100, 40000, 0.0039960, altitude);
   }
   else if (40000 < altitude < 50000)
   {
      return linearInterpolation(40000, 0.0039960, 50000, 0.0010270, altitude);
   }
   else if (50000 < altitude < 60000)
   {
      return linearInterpolation(50000, 0.0010270, 60000, 0.0003097, altitude);
   }
   else if (60000 < altitude < 70000)
   {
      return linearInterpolation(60000, 0.0003097, 70000, 0.0000828, altitude);
   }
   else if (70000 < altitude < 80000)
   {
      return linearInterpolation(70000, 0.0000828, 80000, 0.0000185, altitude);
   }
}

/*********************************
* INTERPOLATE SPEED OF SOUND
* Interpolate the speed of sound from altitude from the chart that we are given
********************************/
double interpolateSpeedOfSound(double altitude)
{
   if (0.0 < altitude < 1000)
   {
      return linearInterpolation(0.0, 340, 1000, 336, altitude);
   }
   else if (1000 < altitude < 2000)
   {
      return linearInterpolation(1000, 336, 2000, 332, altitude);
   }
   else if (2000 < altitude < 3000)
   {
      return linearInterpolation(2000, 332, 3000, 328, altitude);
   }
   else if (3000 < altitude < 4000)
   {
      return linearInterpolation(3000, 328, 4000, 324, altitude);
   }
   else if (4000 < altitude < 5000)
   {
      return linearInterpolation(4000, 324, 5000, 320, altitude);
   }
   else if (5000 < altitude < 6000)
   {
      return linearInterpolation(5000, 320, 6000, 316, altitude);
   }
   else if (6000 < altitude < 7000)
   {
      return linearInterpolation(6000, 316, 7000, 312, altitude);
   }
   else if (7000 < altitude < 8000)
   {
      return linearInterpolation(7000, 312, 8000, 308, altitude);
   }
   else if (8000 < altitude < 9000)
   {
      return linearInterpolation(8000, 308, 9000, 303, altitude);
   }
   else if (9000 < altitude < 10000)
   {
      return linearInterpolation(9000, 303, 10000, 299, altitude);
   }
   else if (10000 < altitude < 15000)
   {
      return linearInterpolation(10000, 299, 15000, 295, altitude);
   }
   else if (15000 < altitude < 20000)
   {
      return linearInterpolation(15000, 295, 20000, 295, altitude);
   }
   else if (20000 < altitude < 25000)
   {
      return linearInterpolation(20000, 295, 25000, 295, altitude);
   }
   else if (25000 < altitude < 30000)
   {
      return linearInterpolation(25000, 295, 30000, 305, altitude);
   }
   else if (30000 < altitude < 40000)
   {
      return linearInterpolation(30000, 305, 40000, 324, altitude);
   }
}

/*********************************
* INTERPOLATE GRAVITY
* Interpolate gravity in m/(s^2) from altitude from the chart that we are given
********************************/
double interpolateSpeedOfSound(double altitude)
{
   if (0.0 < altitude < 1000)
   {
      return linearInterpolation(0.0, 9.807, 1000, 9.804, altitude);
   }
   else if (1000 < altitude < 2000)
   {
      return linearInterpolation(1000, 9.804, 2000, 9.801, altitude);
   }
   else if (2000 < altitude < 3000)
   {
      return linearInterpolation(2000, 9.801, 3000, 9.797, altitude);
   }
   else if (3000 < altitude < 4000)
   {
      return linearInterpolation(3000, 9.797, 4000, 9.794, altitude);
   }
   else if (4000 < altitude < 5000)
   {
      return linearInterpolation(4000, 9.794, 5000, 9.791, altitude);
   }
   else if (5000 < altitude < 6000)
   {
      return linearInterpolation(5000, 9.791, 6000, 9.788, altitude);
   }
   else if (6000 < altitude < 7000)
   {
      return linearInterpolation(6000, 9.788, 7000, 9.785, altitude);
   }
   else if (7000 < altitude < 8000)
   {
      return linearInterpolation(7000, 9.785, 8000, 9.782, altitude);
   }
   else if (8000 < altitude < 9000)
   {
      return linearInterpolation(8000, 9.782, 9000, 9.779, altitude);
   }
   else if (9000 < altitude < 10000)
   {
      return linearInterpolation(9000, 9.779, 10000, 9.776, altitude);
   }
   else if (10000 < altitude < 15000)
   {
      return linearInterpolation(10000, 9.776, 15000, 9.761, altitude);
   }
   else if (15000 < altitude < 20000)
   {
      return linearInterpolation(15000, 9.761, 20000, 9.745, altitude);
   }
   else if (20000 < altitude < 25000)
   {
      return linearInterpolation(20000, 9.745, 25000, 9.730, altitude);
   }
}

/*********************************
* CALCULATE DRAG FORCE
* Calculates the drag force from a drag coefficient,
* dendity of the air, velocity, and surface area
********************************/
double calculateDrag(double drag_c, double density, double velocity, double area)
{
   return (0.5 * drag_c * density * (velocity * velocity) * area); 
}

/*********************************
* CALCULATE SURFACE AREA
* Calculates the surface area of the shot given a radius
**********************************/
double calculateSurfaceArea(double radius)
{
   return 3.14159265358979 * (radius * radius);
}

/*********************************
* CALCULATE FORCE
* Calculates force from mass in kg times acceleration in m/(s^2)
********************************/
double calculateForce(double mass, double acceleration)
{
   return mass * acceleration;
}

/*********************************
* SIMULATE
* Simulate the artillery shot untill it hits the ground
********************************/
void simulate(double angle)
{
   double velocity = 827;  //Initial velocity is 827 m/s
   double surface_area = calculateSurfaceArea(0.15489 / 2); //Diameter of shot is 0.15489m
   double density = 1.225; //Initial air density at 0m altitude is 1.225 kg/(m^2)
   double mass = 46.7;     //The mass of the shot is 46.7kg
   double altitude = 0.0; //Initial altitude is 0

   while (altitude >= 0.0)
   {
      Position position;

   }


}

/*********************************
* MAIN
********************************/
int main()
{
   float user_angle;

   cout << "What is the angle of the Howizter, where 0 is up?: ";
   cin >> user_angle;

   simulate(user_angle);

}

