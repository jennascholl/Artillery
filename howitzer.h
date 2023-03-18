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
   double muzzleVelocity;     // speed of the shell when it leaves the Howitzer in m/s
   Direction angle;           // which way the gun is pointing

public:
   Position position;         // the farthest left point of the Howitzer
   // constructor
   Howitzer();

   // draw the howitzer
   void draw(ogstream& gout, double time) const;

   // getters
   Position getPosition()     const { return position;       }
   double getMuzzleVelocity() const { return muzzleVelocity; }
   Direction getDirection()   const { return angle;          }

   // setters
   Position generatePosition(const Position & ptUpperRight, double size);
   void setMuzzleVelocity(double vel) { muzzleVelocity = vel; }
   void setPosition(Position pos) { position = pos; }

   // special functions
   void rotate(double radians) { angle.addRadians(radians); }
   void raise();

};