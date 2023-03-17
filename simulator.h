/***********************************************************************
 * Header File:
 *    Simulator
 * Author:
 *    Jenna Scholl & Neil Reed
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
   double interval;        // the rate at which time passes
   Howitzer howitzer;      // the gun
   Projectile projectile;  // the bullet
   Status status;          // the status of our launch
   double simTime;         // how long it's been since launch
   Ground ground;          // the ground

   void hitTarget();
   void getHeightMeters();
public:
   // constructor
   Simulator();

   // reset the simulator
   void reset();

   // draw the simulation
   void draw(ogstream& gout) const;

   // setters
   void setInterval(double interval)    { this->interval = interval;       }
   void setMuzzleVelocity(Velocity vel) { howitzer.setMuzzleVelocity(vel); }
   void setRadius(double radius)        { projectile.setRadius(radius);    }

   //special functions
   void fire();
   void advance();
   void input(const Interface* pUI);
};