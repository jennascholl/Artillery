/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Jenna Scholl & Neil Reed
 * Summary:
 *    Everything we need to know about the lander's velocity
 ************************************************************************/

#include "velocity.h"

 /******************************************
  * VELOCITY : CONSTRUCTOR WITH TOTAL SPEED
  * Initialize velocity to the passed speed
  * in m/s^2 and angle
  *****************************************/
Velocity::Velocity(double v, Angle angle)
{
   setDX(computeDX(v, angle));
   setDY(computeDY(v, angle));
}

/******************************************
 * VELOCITY : CONSTRUCTOR WITH DX,DY
 * Initialize velocity to the passed dx
 * and dy
 *****************************************/
Velocity::Velocity(double dx, double dy) : dx(0.0), dy(0.0)
{
   setDX(dx);
   setDY(dy);
}

/*********************************************
 * VELOCITY : GET VELOCITY
 * Return the total current velocity
 *    x^2 + y^2 = t^2
 *********************************************/
double Velocity::getSpeed() const
{
   return sqrt((dx * dx) + (dy * dy));
}

/*********************************************
 * VELOCITY : ADD
 * Given an existing velocity, update it
 * with added acceleration and time
 *********************************************/
void Velocity::add(Acceleration a, double t)
{
   dx += a.getDDX() * t;
   dy += a.getDDY() * t;
}

/*********************************************
 * VELOCITY : COMPUTE DX
 * Given a speed in m/s^2 and an angle,
 * compute dx
 *********************************************/
double Velocity::computeDX(double total, Angle a)
{
   return sin(a.getRadians()) * total;
}

/*********************************************
 * VELOCITY : COMPUTE DY
 * Given a speed in m/s^2 and an angle,
 * compute dy
 *********************************************/
double Velocity::computeDY(double total, Angle a)
{
   return cos(a.getRadians()) * total;
}