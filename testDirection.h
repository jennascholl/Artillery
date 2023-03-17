/***********************************************************************
 * Header File:
 *    Test Direction : Test the Direction class
 * Author:
 *    Jenna Scholl & Neil Reed
 * Summary:
 *    All the unit tests for Direction
 ************************************************************************/

#pragma once

#include <iostream>
#include "direction.h"
#include <cassert>

using namespace std;

/*******************************
 * TEST DIRECTION
 * A friend class for Direction which contains the Direction unit tests
 ********************************/
class TestDirection
{
public:
   void run()
   {
      test_constructor();
      test_normalize_high();
      test_normalize_low();
      test_convert_to_radians();
      test_convert_to_degrees();
      test_assign();
      test_set_radians_normal();
      test_set_radians_high();
      test_set_radians_low();
      test_set_degrees_normal();
      test_set_degrees_high();
      test_set_degrees_low();
      test_set_down();
      test_set_up();
      test_set_left();
      test_set_right();
      test_reverse_positive();
      test_reverse_negative();
      test_get_radians();
      test_get_degrees();
      test_add_radians_normal();
      test_add_radians_high();
      test_add_radians_low();
      test_add_degrees_normal();
      test_add_degrees_high();
      test_add_degrees_low();
   }

private:
   /********************************
   * CONSTRUCTOR
   ********************************/
   void test_constructor()
   {
      // setup
      
      // exercise
      Direction dir;
      // verify
      assert(dir.radians == 0.0);
      // teardown
   }

   /********************************
   * NORMALIZE
   ********************************/
   // normalize greater than 2pi radians
   void test_normalize_high()
   {
      // setup
      Direction dir;
      dir.radians = M_PI * 3.0;
      // exercise
      dir.normalize();
      // verify
      assert(dir.radians == M_PI);
      // teardown
   }

   // normalize less than -2pi radians
   void test_normalize_low()
   {
      // setup
      Direction dir;
      dir.radians = -M_PI * 3.0;
      // exercise
      dir.normalize();
      // verify
      assert(dir.radians == -M_PI);
      // teardown
   }

   /********************************
   * CONVERT
   ********************************/
   // convert to radians
   void test_convert_to_radians()
   {
      // setup
      Direction dir;
      // exercise
      double r = dir.convertToRadians(180.0);
      // verify
      assert(r == M_PI);
      // teardown
   }

   // convert to degrees
   void test_convert_to_degrees()
   {
      // setup
      Direction dir;
      // exercise
      double d = dir.convertToDegrees(M_PI);
      // verify
      assert(d == 180.0);
      // teardown
   }

   /********************************
   * ASSIGN
   ********************************/
   void test_assign()
   {
      // setup
      Direction rhs;
      rhs.radians = M_PI;
      Direction lhs;
      // exercise
      lhs.assign(rhs);
      // verify
      assert(lhs.radians == rhs.radians);
      // teardown
   }

   /********************************
   * SET RADIANS
   ********************************/
   // set radians normal
   void test_set_radians_normal()
   {
      // setup
      Direction dir;
      // exercise
      dir.setRadians(M_PI);
      // verify
      assert(dir.radians == M_PI);
      // teardown
   }

   // set radians to more than 2pi
   void test_set_radians_high()
   {
      // setup
      Direction dir;
      // exercise
      dir.setRadians(M_PI * 3.0);
      // verify
      assert(dir.radians == M_PI);
      // teardown
   }

   // set radians to less than -2pi
   void test_set_radians_low()
   {
      // setup
      Direction dir;
      // exercise
      dir.setRadians(-M_PI * 3.0);
      // verify
      assert(dir.radians == -M_PI);
      // teardown
   }

   /********************************
   * SET DEGREES
   ********************************/
   // set degrees normal
   void test_set_degrees_normal()
   {
      // setup
      Direction dir;
      // exercise
      dir.setDegrees(180.0);
      // verify
      assert(dir.radians == M_PI);
      // teardown
   }

   // set degrees to more than 360
   void test_set_degrees_high()
   {
      // setup
      Direction dir;
      // exercise
      dir.setDegrees(540.0);
      // verify
      assert(dir.radians == M_PI);
      // teardown
   }

   // set degrees to less than -360
   void test_set_degrees_low()
   {
      // setup
      Direction dir;
      // exercise
      dir.setDegrees(-540.0);
      // verify
      assert(dir.radians == -M_PI);
      // teardown
   }

   /********************************
   * SET DIRECTIONS
   ********************************/
   // set down
   void test_set_down()
   {
      // setup
      Direction dir;
      // exercise
      dir.setDown();
      // verify
      assert(dir.radians == M_PI);
      // teardown
   }

   // set up
   void test_set_up()
   {
      // setup
      Direction dir;
      dir.radians = M_PI;
      // exercise
      dir.setUp();
      // verify
      assert(dir.radians == 0.0);
      // teardown
   }

   // set right
   void test_set_right()
   {
      // setup
      Direction dir;
      // exercise
      dir.setRight();
      // verify
      assert(dir.radians == M_PI / 2.0);
      // teardown
   }

   // set left
   void test_set_left()
   {
      // setup
      Direction dir;
      // exercise
      dir.setLeft();
      // verify
      assert(dir.radians == -M_PI / 2.0);
      // teardown
   }

   /********************************
   * REVERSE
   ********************************/
   // reverse positive
   void test_reverse_positive()
   {
      // setup
      Direction dir;
      dir.radians = M_PI;
      // exercise
      dir.reverse();
      // verify
      assert(dir.radians == 2 * M_PI);
      // teardown
   }

   // reverse negative
   void test_reverse_negative()
   {
      // setup
      Direction dir;
      dir.radians = -M_PI;
      // exercise
      dir.reverse();
      // verify
      assert(dir.radians == 0);
      // teardown
   }

   /********************************
   * GET RADIANS
   ********************************/
   void test_get_radians()
   {
      // setup
      Direction dir;
      dir.radians = M_PI;
      // exercise
      double r = dir.getRadians();
      // verify
      assert(r == M_PI);
      // teardown
   }

   /********************************
   * GET DEGREES
   ********************************/
   void test_get_degrees()
   {
      // setup
      Direction dir;
      dir.radians = M_PI;
      // exercise
      double d = dir.getDegrees();
      // verify
      assert(d == 180.0);
      // teardown
   }
   
   /********************************
   * ADD RADIANS
   ********************************/
   // add radians normal
   void test_add_radians_normal()
   {
      // setup
      Direction dir;
      // exercise
      dir.addRadians(M_PI);
      // verify
      assert(dir.radians == M_PI);
      // teardown
   }

   // add more than 2pi radians
   void test_add_radians_high()
   {
      // setup
      Direction dir;
      // exercise
      dir.addRadians(M_PI * 3);
      // verify
      assert(dir.radians == M_PI);
      // teardown
   }

   // add less than -2pi radians
   void test_add_radians_low()
   {
      // setup
      Direction dir;
      // exercise
      dir.addRadians(-M_PI * 3);
      // verify
      assert(dir.radians == -M_PI);
      // teardown
   }

   /********************************
   * ADD DEGREES
   ********************************/
   // add degrees normal
   void test_add_degrees_normal()
   {
      // setup
      Direction dir;
      // exercise
      dir.addDegrees(180);
      // verify
      assert(dir.radians == M_PI);
      // teardown
   }

   // add more than 360 degrees
   void test_add_degrees_high()
   {
      // setup
      Direction dir;
      // exercise
      dir.addDegrees(540);
      // verify
      assert(dir.radians == M_PI);
      // teardown
   }

   // add less than -360 degrees
   void test_add_degrees_low()
   {
      // setup
      Direction dir;
      // exercise
      dir.addDegrees(-540);
      // verify
      assert(dir.radians == -M_PI);
      // teardown
   }
};