/***********************************************************************
 * Header File:
 *    Acceleration
 * Author:
 *    Jenna Scholl & Neil Reed
 * Summary:
 *    Everything we need to know about the lander's acceleration
 ************************************************************************/

#pragma once

#include <math.h> // for sqrt()

class TestVelocity;

/*********************************************
 * ACCELERATION
 * Change in velocity
 *********************************************/
class Acceleration
{
   friend TestVelocity;
private:
   // member variables
   double ddx;
   double ddy;

public:
   // constructors
   Acceleration() : ddx(0.0), ddy(0.0) {}
   Acceleration(long double ddx, long double ddy);

   // getters
   long double getDDX()          const { return ddx; }
   long double getDDY()          const { return ddy; }
   long double getAcceleration() const; 

   // setters
   void setDDX(const long double &ddx) { this->ddx = ddx; }
   void setDDY(const long double &ddy) { this->ddy = ddy; }

};