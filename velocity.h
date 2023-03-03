/***********************************************************************
 * Header File:
 *    VELOCITY
 * Author:
 *    Jenna Scholl & Neil Reed
 * Summary:
 *    Everything we need to know about the lander's velocity
 ************************************************************************/


#pragma once

#include "acceleration.h" // for add()
#include "angle.h"        // for computeDX() and computeDY()

#include <math.h>         // for sqrt()

 /*********************************************
  * VELOCITY
  * The speed at which something travels
  *********************************************/
class Velocity
{
private:
   // member variables
   long double dx;
   long double dy;

public:
   // constructors
   Velocity() : dx(0.0), dy(0.0)   {}
   Velocity(long double dx, long double dy);

   // getters
   long double getDX()    const { return dx; }
   long double getDY()    const { return dy; }
   long double getSpeed() const;

   // setters
   void setDX(const long double &dx) { this->dx = dx; }
   void setDY(const long double &dy) { this->dy = dy; }

   // special functions
   void add(Acceleration a, long double t);

};