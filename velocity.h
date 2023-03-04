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
#include "direction.h"        // for computeDX() and computeDY()

#include <math.h>         // for sqrt()

class TestVelocity;       //so they can be friends

 /*********************************************
  * VELOCITY
  * The speed at which something travels
  *********************************************/
class Velocity
{
   friend TestVelocity; //Allow testVelocity access to privates, cuz that's what friends do
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
   void addA(Acceleration a, long double t);

   void addVelocity(Velocity v);

   void reverse() { setDX(-dx); setDY(-dy); }

};
