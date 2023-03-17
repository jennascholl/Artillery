/***********************************************************************
 * Source File:
 *    Direction
 * Author:
 *    Jenna Scholl & Neil Reed
 * Summary:
 *    Everything we need to know about the direction of an object
 ************************************************************************/

#include "direction.h"

/******************************************
 * DIRECTION :  CONVERT TO DEGREES
 * Convert radians to degrees:
 *     radians / 2pi = degrees / 360
 *****************************************/
double Direction::convertToDegrees(double radians) const
{
   return radians / (2.0 * M_PI) * 360.0;
}

/******************************************
 * DIRECTION : CONVERT TO RADIANS
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 *****************************************/
double Direction::convertToRadians(double degrees) const
{
   return (degrees / 360.0) * 2.0 * M_PI;
}

/******************************************
 * DIRECTION : NORMALIZE
 * Adjust the angle to between -pi/2 and pi/2 
 * in radians
 *****************************************/
void Direction::normalize()
{
   while (radians > M_PI * 2)
      setRadians(radians - (M_PI * 2.0));
   while (radians < -(M_PI * 2))
      setRadians(radians + (M_PI * 2.0));
}

/******************************************
 * DIRECTION : SET DEGREES
 * Set the angle with a given number of
 * degrees
 *****************************************/
void Direction::setDegrees(double degrees)
{
   setRadians(convertToRadians(degrees));
}

/******************************************
 * ANGLE : SET RADIANS
 * Set the angle with a given number of
 * radians
 *****************************************/
void Direction::setRadians(double radians)
{
   this->radians = radians;
   normalize();
}

/******************************************
 * DIRECTION : ADD RADIANS
 * Add to the angle with a given number of
 * radians
 *****************************************/
void Direction::addRadians(double radians)
{
   this->radians += radians;
   normalize();
}

/******************************************
 * DIRECTION : ADD DEGREES
 * Add to the angle with a given number of
 * degrees
 *****************************************/
void Direction::addDegrees(double degrees)
{
   addRadians(convertToRadians(degrees));
}

/******************************************
 * DIRECTION : REVERSE
 * Reverse a direction
 *****************************************/
void Direction::reverse()
{
   setRadians(radians + M_PI);
}