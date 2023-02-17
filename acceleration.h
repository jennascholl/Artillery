/***********************************************************************
 * Header File:
 *    Acceleration
 * Author:
 *    Jenna Scholl & Neil Reed
 * Summary:
 *    Everything we need to know about the lander's acceleration
 ************************************************************************/

#pragma once

#include "Angle.h"

#include <math.h> // for sqrt()

/*********************************************
 * ACCELERATION
 * Change in velocity
 *********************************************/
class Acceleration
{
private:
   // member variables
   double ddx;
   double ddy;
   double gravity = -1.625;

   // private functions
   double computeDDX(double total, Angle angle);
   double computeDDY(double total, Angle angle);

public:
   // constructors
   Acceleration() : ddx(0.0), ddy(0.0) {}
   Acceleration(double a, Angle angle);
   Acceleration(double ddx, double ddy);

   // getters
   double getDDX()          const { return ddx; }
   double getDDY()          const { return ddy; }
   double getAcceleration() const; 

   // setters
   void setDDX(const double &ddx) { this->ddx = ddx; }
   void setDDY(const double &ddy) { this->ddy = ddy; }

};