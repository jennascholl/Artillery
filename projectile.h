/***********************************************************************
 * Header File:
 *    Projectile
 * Author:
 *    Jenna Scholl & Neil Reed
 * Summary:
 *    Everything we need to know about our ammunition
 ************************************************************************/

#pragma once
#include "position.h"
#include "direction.h"
#include "velocity.h"
#include "uidraw.h"
#include <vector>

using namespace std;

/*********************************************
 * PVT
 * A struct to represent our projectile's current
 * position, velocity, and time
 *********************************************/
struct PVT
{
   Position pos;
   Velocity vel;
   double time;
};

 /*********************************************
  * PROJECTILE
  * A bullet to hit a target
  *********************************************/
class Projectile
{
private:
   double mass;                // mass in kg
   double radius;              // radius in meters
   Position launchPos;         // the starting position
   vector<PVT> flightPath;     // the projectile's last 20 positions, velocities, and times

public:
   // constructor
   Projectile();
   // reset the game
   void reset();

   // draw the ground on the screen
   void draw(ogstream& gout) const;

   bool isFlying();

   // getters
   Position getPosition() const;
   double getAltitude() const;
   double getFlightTime() const;
   double getFlightDistance() const;
   double getSpeed() const;

   // setters
   void setMass(double mass)     { this->mass = mass;     }
   void setRadius(double radius) { this->radius = radius; }

   // special functions
   void fire(Position pos, double time, Direction angle, double vel);
   void advance(double time);
};