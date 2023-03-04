/***********************************************************************
 * Header File:
 *    Test Velocity : Test the Velocity class
 * Author:
 *    Jenna Scholl & Neil Reed
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
      // constructor test
      test_constructor();

      // getDX tests
      test_getDX_noVelocity();
      test_getDX_positiveVelocity();
      test_getDX_negativeLowVelocity();

      // getDY tests
      test_getDY_noVelocity();
      test_getDY_positiveVelocity();
      test_getDY_negativeLowVelocity();

      // getSpeed tests
      test_getSpeed_noSpeed();
      test_getSpeed_dxNody();
      test_getSpeed_positiveDxAndDy();
      test_getSpeed_negativeDxPositiveDy();
      test_getSpeed_positiveDxNegativeDy();
      test_getSpeed_negativeDxAndDy();

      // addA tests
      test_add_noAccelerationNoTime();
      test_add_noAcceleration();
      test_add_lowAcceleration();

      // reverse test
      test_reverse();

      // addVelocity tests
      test_addVelocity_positiveDXnegativeDY();
      test_addVelocity_negativeDXpositiveDY();

      // addDX tests
      test_add_dx_pos();
      test_add_dx_neg();

      // addDY tests
      test_add_dy_pos();
      test_add_dy_neg();

   }

private:
   // utility function because floating point numbers are approximations
   bool closeEnough(double value, double test, double tolerence)
   {
      double difference = value - test;
      return (difference >= -tolerence) && (difference <= tolerence);
   }

   /********************************
   * CONSTRUCTOR
   ********************************/
   // Test default constructor values
   void test_constructor()
   {
      // setup
      
      // exercise
      Velocity v;
      // verify
      assert(v.dx == 0.0);
      assert(v.dy == 0.0);
      // teardown
   }

   /********************************
   * GET DX
   ********************************/
   // No velocity
   void test_getDX_noVelocity()
   {
      // setup
      Velocity v;
      v.dx = (0.0);
      // exercise
      double veloX = v.getDX();
      // verify
      assert(0.0 == veloX);
      // teardown

   }
   // Positive Velocity
   void test_getDX_positiveVelocity()
   {
      // setup
      Velocity v;
      v.dx = (17.0);
      // exercise
      double veloX = v.getDX();
      // verify
      assert(17.0 == veloX);
      // teardown

   }
   // Negative low velocity
   void test_getDX_negativeLowVelocity()
   {
      // setup
      Velocity v;
      v.dx = (-22.0);
      // exercise
      double veloX = v.getDX();
      // verify
      assert(-22.0 == veloX);
      // teardown

   }

   /********************************
   * GET DY
   ********************************/
   // No velocity
   void test_getDY_noVelocity()
   {
      // setup
      Velocity v;
      v.dy = (0.0);
      // exercise
      double veloY = v.getDY();
      // verify
      assert(0.0 == veloY);
      // teardown

   }
   // Positive Velocity
   void test_getDY_positiveVelocity()
   {
      // setup
      Velocity v;
      v.dy = (17.0);
      // exercise
      double veloY = v.getDY();
      // verify
      assert(17.0 == veloY);
      // teardown

   }
   //Negative low velocity
   void test_getDY_negativeLowVelocity()
   {
      // setup
      Velocity v;
      v.dy = (-22.0);
      // exercise
      double veloY = v.getDY();
      // verify
      assert(-22.0 == veloY);
      // teardown

   }

   /********************************
   * GET SPEED
   ********************************/
   // No speed
   void test_getSpeed_noSpeed()
   {
      // setup
      Velocity v;
      v.dx = 0.0;
      v.dy = 0.0;
      // exercise
      double speedTest = v.getSpeed();
      // verify
      assert(0.0 == speedTest);
      assert(0.0 == v.dx);
      assert(0.0 == v.dy);
      // teardown
   }

   // Positive dx, no dy
   void test_getSpeed_dxNody()
   {
      // setup
      Velocity v;
      v.dx = 10.0;
      v.dy = 0.0;
      // exercise
      double speedTest = v.getSpeed();
      // verify
      assert(10.0 == speedTest);
      assert(10.0 == v.dx);
      assert(0.0 == v.dy);
      // teardown
   }

   // Positive dy, no dx
   void test_getSpeed_dyNodx()
   {
      // setup
      Velocity v;
      v.dx = 0.0;
      v.dy = 10.0;
      // exercise
      double speedTest = v.getSpeed();
      // verify
      assert(10.0 == speedTest);
      assert(0.0 == v.dx);
      assert(10.0 == v.dy);
      // teardown
   }

   // Positive dx, positive dy
   void test_getSpeed_positiveDxAndDy()
   {
      // setup
      Velocity v;
      v.dx = 20.0;
      v.dy = 10.0;
      // exercise
      double speedTest = v.getSpeed();
      // verify
      assert(closeEnough( 22.36, speedTest, (22.36 * 0.001))); //Within %0.1
      assert(20.0 == v.dx);
      assert(10.0 == v.dy);
      // teardown
   }

   // Negative dx, positive dy
   void test_getSpeed_negativeDxPositiveDy()
   {
      // setup
      Velocity v;
      v.dx = -20.0;
      v.dy = 10.0;
      // exercise
      double speedTest = v.getSpeed();
      // verify
      assert(closeEnough(22.36, speedTest, (22.36 * 0.001))); //Within %0.1
      assert(-20.0 == v.dx);
      assert(10.0 == v.dy);
      // teardown
   }

   // Positive dx, negative dy
   void test_getSpeed_positiveDxNegativeDy()
   {
      // setup
      Velocity v;
      v.dx = 20.0;
      v.dy = -10.0;
      // exercise
      double speedTest = v.getSpeed();
      // verify
      assert(closeEnough(22.36, speedTest, (22.36 * 0.001))); //Within %0.1
      assert(20.0 == v.dx);
      assert(-10.0 == v.dy);
      // teardown
   }

   // Negative dx, negative dy
   void test_getSpeed_negativeDxAndDy()
   {
      // setup
      Velocity v;
      v.dx = -20.0;
      v.dy = -10.0;
      // exercise
      double speedTest = v.getSpeed();
      // verify
      assert(closeEnough(22.36, speedTest, (22.36 * 0.001))); //Within %0.1
      assert(-20.0 == v.dx);
      assert(-10.0 == v.dy);
      // teardown
   }

   /********************************
   * ADD
   ********************************/
   // No acceleration, no time
   void test_add_noAccelerationNoTime()
   {
      // setup
      Velocity v;
      v.dx = 5.0;
      v.dy = 5.0;
      Acceleration a;
      a.ddx = 0.0;
      a.ddy = 0.0;
      // exercise
      v.addA(a, 0.0);
      // verify
      assert(5.0 == v.dx);
      assert(5.0 == v.dy);
      // teardown
   }

   // No acceleration, 1 sec
   void test_add_noAcceleration()
   {
      // setup
      Velocity v;
      v.dx = 5.0;
      v.dy = 5.0;
      Acceleration a;
      a.ddx = 0.0;
      a.ddy = 0.0;
      // exercise
      v.addA(a, 1.0);
      // verify
      assert(5.0 == v.dx);
      assert(5.0 == v.dy);
      // teardown
   }

   // Low acceleration, 1 sec
   void test_add_lowAcceleration()
   {
      // setup
      Velocity v;
      v.dx = 5.0;
      v.dy = 5.0;
      Acceleration a;
      a.ddx = 2.0;
      a.ddy = 3.0;
      // exercise
      v.addA(a, 1.0);
      // verify
      assert(7.0 == v.dx);
      assert(8.0 == v.dy);
      // teardown
   }

   /********************************
   * REVERSE
   ********************************/
   //Reverse dx and dy
   void test_reverse()
   {
      // setup
      Velocity v;
      v.dx = 10.0;
      v.dy = -8.0;
      // exercise
      v.reverse();
      // verify
      assert(-10.0 == v.dx);
      assert(8.0 == v.dy);
      // teardown
   }

   /********************************
   * ADD VELOCITY
   ********************************/
   // add positive dx and negative dy
   void test_addVelocity_positiveDXnegativeDY()
   {
      // setup
      Velocity v1;
      v1.dx = 10.0;
      v1.dy = 10.0;
      Velocity v2;
      v2.dx = -2.0;
      v2.dy = 3.0;
      // exercise
      v1.addVelocity(v2);
      // verify
      assert(8.0 == v1.dx);
      assert(13.0 == v1.dy);
      // teardown
   }

   // add negative dx and positive dy
   void test_addVelocity_negativeDXpositiveDY()
   {
      // setup
      Velocity v1;
      v1.dx = 10.0;
      v1.dy = 10.0;
      Velocity v2;
      v2.dx = 2.0;
      v2.dy = -3.0;
      // exercise
      v1.addVelocity(v2);
      // verify
      assert(12.0 == v1.dx);
      assert(7.0 == v1.dy);
      // teardown
   }

   // add positive dx
   void test_add_dx_pos()
   {
      // setup
      Velocity v;
      v.dx = 0.0;
      v.dy = 0.0;
      // exercise
      v.addDX(10.0);
      // verify
      assert(10.0 == v.dx);
      assert(0.0 == v.dy);
      // teardown
   }

   // add negative dx
   void test_add_dx_neg()
   {
      // setup
      Velocity v;
      v.dx = 0.0;
      v.dy = 0.0;
      // exercise
      v.addDX(-10.0);
      // verify
      assert(-10.0 == v.dx);
      assert(0.0 == v.dy);
      // teardown
   }

   // add positive dy
   void test_add_dy_pos()
   {
      // setup
      Velocity v;
      v.dx = 0.0;
      v.dy = 0.0;
      // exercise
      v.addDY(10.0);
      // verify
      assert(0.0 == v.dx);
      assert(10.0 == v.dy);
      // teardown
   }

   // add negative dy
   void test_add_dy_neg()
   {
      // setup
      Velocity v;
      v.dx = 0.0;
      v.dy = 0.0;
      // exercise
      v.addDY(-10.0);
      // verify
      assert(0.0 == v.dx);
      assert(-10.0 == v.dy);
      // teardown
   }
};
