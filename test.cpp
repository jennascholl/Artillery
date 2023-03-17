/***********************************************************************
 * Source File:
 *    Test : Test runner
 * Author:
 *    Br. Helfrich, Jenna Scholl, & Neil Reed
 * Summary:
 *    The test runner for all the unit tests
 ************************************************************************/

#include "test.h"
#include "testPosition.h"
#include "testGround.h"
#include "testVelocity.h"
#include "testDirection.h"

#include <iostream>

using namespace std;

/*****************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 ****************************************************************/
void testRunner()
{
   TestPosition().run();
   TestGround().run();
   TestVelocity().run();
   TestDirection().run();

   cout << "\nAll tests passed!" << endl;
}
