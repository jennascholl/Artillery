/***********************************************************************
 * Source File:
 *    Howitzer : The representation of the Howitzer on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about the M777 Howitzer.
 ************************************************************************/

#include "howitzer.h"

/*********************************************
 * HOWITZER : CONSTRUCTOR
 * Get everything set up
 *********************************************/
Howitzer::Howitzer() : muzzleVelocity(827.0)
{
   position.setPixelsX(0.0);
   position.setPixelsY(0.0);

   angle.setUp();
}

/*********************************************
 * HOWITZER : DRAW
 * Draw the Howitzer on the screen
 *********************************************/
void Howitzer::draw(ogstream& gout, double time) const
{
   gout.drawHowitzer(position, angle.getRadians(), time);
}

/*********************************************
 * HOWITZER : GENERATE POSITION
 * Generate a position for the Howitzer
 *********************************************/
Position Howitzer::generatePosition(const Position & ptUpperRight, double size)
{
   Position pos;
   pos.setPixelsX((int)random(ptUpperRight.getPixelsX() * 0.1,
      ptUpperRight.getPixelsX() * 0.9 - size));
   pos.setPixelsY(0.0);
   position.setPixelsX(pos.getPixelsX());
   position.setPixelsY(pos.getPixelsY());

   return pos;
}

/*********************************************
 * HOWITZER : RAISE
 * Bring the direction of the Howitzer back to center
 *********************************************/
void Howitzer::raise()
{
   // if the gun is pointing left, move it right
   if (angle.getRadians() < 0.0)
      angle.addRadians(0.003);

   // if it's pointing right, move it left
   else if (angle.getRadians() > 0.0)
      angle.addRadians(-0.003);

   if (angle.getRadians() < 0.003 && angle.getRadians() > -0.003)
      angle.setRadians(0.0);
}