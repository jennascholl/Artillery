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

