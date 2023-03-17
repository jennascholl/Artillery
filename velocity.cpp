/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Jenna Scholl & Neil Reed
 * Summary:
 *    Everything we need to know about the lander's velocity
 ************************************************************************/

#include "velocity.h"

#include <math.h>            // for sin and cos

/******************************************
 * VELOCITY : CONSTRUCTOR WITH DX,DY
 * Initialize velocity to the passed dx
 * and dy
 *****************************************/
Velocity::Velocity(long double dx, long double dy) : dx(0.0), dy(0.0)
{
   setDX(dx);
   setDY(dy);
}

/*********************************************
 * VELOCITY : GET SPEED
 * Return the total current velocity
 *    x^2 + y^2 = t^2
 *********************************************/
long double Velocity::getSpeed() const
{
   return sqrt((dx * dx) + (dy * dy));
}

/*********************************************
 * VELOCITY : ADD VELOCITY
 * vector addition
 *********************************************/
void Velocity::addVelocity(const Velocity & v)
{
   dx += v.getDX();
   dy += v.getDY();
}

/*********************************************
 * VELOCITY : ADD
 * Given an existing velocity, update it
 * with added acceleration and time
 *********************************************/
void Velocity::addA(const Acceleration & a, long double t)
{
   dx += a.getDDX() * t;
   dy += a.getDDY() * t;
}

/*********************************************
 * VELOCITY : ADD DX
 * Given an existing velocity, update it
 * with added horizontal velocity
 *********************************************/
void Velocity::addDX(double dx)
{
   this->dx += dx;
}

/*********************************************
 * VELOCITY : ADD DY
 * Given an existing vel ocity, update it
 * with added vertical velocity
 *********************************************/
void Velocity::addDY(double dy)
{
   this->dy += dy;
}