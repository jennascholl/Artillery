/***********************************************************************
 * Header File:
 *    Direction
 * Author:
 *    Jenna Scholl & Neil Reed
 * Summary:
 *    Everything we need to know about the direction of an object
 ************************************************************************/

#pragma once

#include <iostream>
using namespace std;
#define _USE_MATH_DEFINES    // for M_PI
#include <math.h>

class TestDirection;

/*********************************************
 * DIRECTION
 * A measurement of orientation
 *********************************************/
class Direction
{
   friend TestDirection;
private:
   // the member variable
   double radians;

   // special functions
   double convertToDegrees(double radians) const;
   double convertToRadians(double degrees) const;
   void normalize();

public:
   // constructors
   Direction() : radians(0.0) {}
   Direction(const Direction& rhs) { radians = rhs.radians; }

   // getters
   double getDegrees() const { return convertToDegrees(radians); }
   double getRadians() const { return radians; }

   // setters
   void setDegrees(double degrees);
   void setRadians(double radians);
   void addDegrees(double degrees);
   void addRadians(double radians);
   void assign(Direction rhs) { setRadians(rhs.getRadians()); }
   void setDown()             { setRadians(M_PI); }
   void setUp()               { setRadians(0.0); }
   void setLeft()             { setRadians(-M_PI / 2); }
   void setRight()            { setRadians(M_PI / 2); }
   void reverse();

   void display() const;
};

