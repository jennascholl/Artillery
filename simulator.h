/***********************************************************************
 * Header File:
 *    Simulator
 * Author:
 *    Jenna Scholl
 * Summary:
 *    Ties all the elements together
 ************************************************************************/

#pragma once

#include "howitzer.h"
#include "projectile.h"
#include "velocity.h"
#include "ground.h"
#include "uiDraw.h"
#include "uiInteract.h"

enum Status { LOADED, FLYING, LANDED };

class Simulator
{
private:
   Position ptUpperRight;
   double interval;        // the rate at which time passes (s)
   Howitzer howitzer;      // the gun
   Projectile projectile;  // the bullet
   Ground ground;          // the ground
   Status status;          // the status of our launch
   double simTime;         // how long it's been since launch (s)

   bool hitTarget();
   double getHeightMeters();

public:
   // constructor
   Simulator(Position ptUpperRight) : ptUpperRight(ptUpperRight), interval(0.5), 
      howitzer(), projectile(), ground(ptUpperRight), simTime(-0.5), status(LOADED) {
      reset(); reset();
   }

   // reset the simulator
   void reset();

   // draw the simulation
   void draw(ogstream& gout) const;

   // setters
   void setInterval(double interval)    { this->interval = interval;       }
   void setMuzzleVelocity(double vel)   { howitzer.setMuzzleVelocity(vel); }
   void setRadius(double radius)        { projectile.setRadius(radius);    }

   //special functions
   void fire();
   void advance();
   void input(const Interface* pUI);
};