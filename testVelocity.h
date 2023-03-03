/***********************************************************************
 * Header File:
 *    Test Velocity : Test the Velocity class
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the unit tests for Velocity
 ************************************************************************/

#pragma once

#include <iostream>
#include "velocity.h"
#include <cassert>

using namespace std;

/*******************************
 * TEST VELOCITY
 * A friend class for Velocity which contains the Velocity unit tests
 ********************************/
class testVelocity
{
public:
   void run()
   {

   }

private:
   // utility function because floating point numbers are approximations
   bool closeEnough(double value, double test, double tolerence)
   {
      double difference = value - test;
      return (difference >= -tolerence) && (difference <= tolerence);
   }
};