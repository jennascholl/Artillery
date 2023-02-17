/***********************************************************************
 * Source File:
 *    Acceleration
 * Author:
 *    Jenna Scholl & Neil Reed
 * Summary:
 *    Everything we need to know about the lander's acceleration
 ************************************************************************/

#include "acceleration.h"

 /******************************************
  * ACCELERATION : CONSTRUCTOR WITH TOTAL
  * Initialize acceleration to the passed value
  * in m/s^2 and angle
  *****************************************/
Acceleration::Acceleration(double a, Angle angle)
{
   setDDX(computeDDX(a, angle));
   setDDY(computeDDY(a, angle));
}

/******************************************
 * ACCELERATION : CONSTRUCTOR WITH DDX,DDY
 * Initialize acceleration to the passed
 * ddx and ddy
 *****************************************/
Acceleration::Acceleration(double ddx, double ddy) : ddx(0.0), ddy(0.0)
{
   setDDX(ddx);
   setDDY(ddy);
}

/*********************************************
 * ACCELERATION : GET ACCELERATION
 * Return the total current acceleration
 *    x^2 + y^2 = t^2
 *********************************************/
double Acceleration::getAcceleration() const
{ 
   return sqrt((ddx * ddx) + (ddy * ddy)); 
}

/*********************************************
 * ACCELERATION : COMPUTE DDX
 * Given the total in m/s^2 and an angle,
 * compute ddx
 *********************************************/
double Acceleration::computeDDX(double total, Angle a)
{
   return -sin(a.getRadians()) * total;
}

/*********************************************
 * ACCELERATION : COMPUTE DDY
 * Given the total in m/s^2 and an angle,
 * compute ddy
 *********************************************/
double Acceleration::computeDDY(double total, Angle a)
{
   return -cos(a.getRadians()) * total;
}