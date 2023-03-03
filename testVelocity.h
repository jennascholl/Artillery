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
class TestVelocity
{
public:
   void run()
   {
      //Constructor test
      test_constructor();
      //getDX tests
      test_getDX_noVelocity();
      test_getDX_positiveVelocity();
      test_getDX_negativeLowVelocity();
      //getDY tests
      test_getDY_noVelocity();
      test_getDY_positiveVelocity();
      test_getDY_negativeLowVelocity();
      //getSpeed tests
      test_getSpeed_noSpeed();
      test_getSpeed_dxNody();
      test_getSpeed_positiveDxAndDy();
      test_getSpeed_negativeDxPositiveDy();
      test_getSpeed_positiveDxNegativeDy();
      test_getSpeed_negativeDxAndDy();

   }

private:
   // utility function because floating point numbers are approximations
   bool closeEnough(double value, double test, double tolerence)
   {
      double difference = value - test;
      return (difference >= -tolerence) && (difference <= tolerence);
   }

   /********************************
   *CONSTRUCTOR
   ********************************/
   //Test default constructor values
   void test_constructor()
   {
      //Setup
      
      //Exercise
      Velocity v;
      //Validate
      assert(v.dx == 0.0);
      assert(v.dy == 0.0);
      //Teardown

   }

   /********************************
   *GET DX
   ********************************/
   //No velocity
   void test_getDX_noVelocity()
   {
      //Setup
      Velocity v;
      v.dx = (0.0);
      //Exercise
      double veloX = v.getDX();
      //Validate
      assert(0.0 == veloX);
      //Teardown

   }
   //Positive Velocity
   void test_getDX_positiveVelocity()
   {
      //Setup
      Velocity v;
      v.dx = (17.0);
      //Exercise
      double veloX = v.getDX();
      //Validate
      assert(17.0 == veloX);
      //Teardown

   }
   //Negative low velocity
   void test_getDX_negativeLowVelocity()
   {
      //Setup
      Velocity v;
      v.dx = (-22.0);
      //Exercise
      double veloX = v.getDX();
      //Validate
      assert(-22.0 == veloX);
      //Teardown

   }

   /********************************
   *GET DY
   ********************************/
   //No velocity
   void test_getDY_noVelocity()
   {
      //Setup
      Velocity v;
      v.dy = (0.0);
      //Exercise
      double veloY = v.getDY();
      //Validate
      assert(0.0 == veloY);
      //Teardown

   }
   //Positive Velocity
   void test_getDY_positiveVelocity()
   {
      //Setup
      Velocity v;
      v.dy = (17.0);
      //Exercise
      double veloY = v.getDY();
      //Validate
      assert(17.0 == veloY);
      //Teardown

   }
   //Negative low velocity
   void test_getDY_negativeLowVelocity()
   {
      //Setup
      Velocity v;
      v.dy = (-22.0);
      //Exercise
      double veloY = v.getDY();
      //Validate
      assert(-22.0 == veloY);
      //Teardown

   }

   /********************************
   *GET SPEED
   ********************************/
   //No speed
   void test_getSpeed_noSpeed()
   {
      //Setup
      Velocity v(0.0, 0.0);
      //Exersize
      double speedTest = v.getSpeed();
      //Validate
      assert(0.0 == speedTest);
      assert(0.0 == v.dx);
      assert(0.0 == v.dy);
      //Teardown
   }

   //Positive dx, no dy
   void test_getSpeed_dxNody()
   {
      //Setup
      Velocity v(10.0, 0.0);
      //Exersize
      double speedTest = v.getSpeed();
      //Validate
      assert(10.0 == speedTest);
      assert(10.0 == v.dx);
      assert(0.0 == v.dy);
      //Teardown
   }

   //Positive dy, no dx
   void test_getSpeed_dyNodx()
   {
      //Setup
      Velocity v(0.0, 10.0);
      //Exersize
      double speedTest = v.getSpeed();
      //Validate
      assert(10.0 == speedTest);
      assert(0.0 == v.dx);
      assert(10.0 == v.dy);
      //Teardown
   }

   //Positive dx, positive dy
   void test_getSpeed_positiveDxAndDy()
   {
      //Setup
      Velocity v(20.0, 10.0);
      //Exersize
      double speedTest = v.getSpeed();
      //Validate
      assert(closeEnough( 22.36, speedTest, (22.36 * 0.001))); //Within %0.1
      assert(20.0 == v.dx);
      assert(10.0 == v.dy);
      //Teardown
   }

   //Negative dx, positive dy
   void test_getSpeed_negativeDxPositiveDy()
   {
      //Setup
      Velocity v(-20.0, 10.0);
      //Exersize
      double speedTest = v.getSpeed();
      //Validate
      assert(closeEnough(22.36, speedTest, (22.36 * 0.001))); //Within %0.1
      assert(-20.0 == v.dx);
      assert(10.0 == v.dy);
      //Teardown
   }

   //Positive dx, negative dy
   void test_getSpeed_positiveDxNegativeDy()
   {
      //Setup
      Velocity v(20.0, -10.0);
      //Exersize
      double speedTest = v.getSpeed();
      //Validate
      assert(closeEnough(22.36, speedTest, (22.36 * 0.001))); //Within %0.1
      assert(20.0 == v.dx);
      assert(-10.0 == v.dy);
      //Teardown
   }

   //Negative dx, negative dy
   void test_getSpeed_negativeDxAndDy()
   {
      //Setup
      Velocity v(-20.0, -10.0);
      //Exersize
      double speedTest = v.getSpeed();
      //Validate
      assert(closeEnough(22.36, speedTest, (22.36 * 0.001))); //Within %0.1
      assert(-20.0 == v.dx);
      assert(-10.0 == v.dy);
      //Teardown
   }

   /********************************
   *ADD
   ********************************/
   //No acceleration, 1 sec
   //void test_add_noAcceleration()
   //{
   //   //Setup
   //   Velocity v(5.0, 5.0);
   //   //Exersize
   //   v.add( , 1.0);
   //   //Validate
   //   assert(5.0 == v.dx);
   //   assert(5.0 == v.dy);
   //   //Teardown
   //}

};