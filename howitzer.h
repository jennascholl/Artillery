/***********************************************************************
 * Header File:
 *    Howitzer
 * Author:
 *    Jenna Scholl & Neil Reed
 * Summary:
 *    Everything we need to know about the M777 Howitzer.
 ************************************************************************/

#pragma once

#include "position.h"
#include "direction.h"
#include "velocity.h"
#include "uidraw.h"

/*********************************************
 * HOWITZER
 * The M777 Howitzer
 *********************************************/
class Howitzer
{
private:
   Position position;
   Velocity muzzleVelocity;
   Direction elevation;

public:
   // constructor
   Howitzer();

   // draw the howitzer
   void draw(ogstream& gout, double time) const;

   // getters
   Position getPosition() { return position; }
   Velocity getMuzzleVelocity() { return muzzleVelocity; }

   // setters
   void generatePosition(double size);
   void setMuzzleVelocity(Velocity vel) { muzzleVelocity = vel; }

   // special functions
   void rotate(double radians) { elevation.addRadians(radians); }
   void raise();

};