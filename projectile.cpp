/***********************************************************************
 * Source File:
 *    Projectile : A bullet to hit a target
 * Author:
 *    Jenna Scholl & Neil Reed
 * Summary:
 *    Everything we need to know about our ammunition
 ************************************************************************/

#include "projectile.h"

/*********************************************
 * PROJECTILE : CONSTRUCTOR
 * Get everything set up
 *********************************************/
Projectile::Projectile()
{
   setMass(46.7);
   setRadius(0.07745);
   // how do I set the flight path?
}

/*********************************************
 * PROJECTILE : RESET
 * Revert all the values back to their original state
 *********************************************/
void Projectile::reset()
{
   // reset the flight path
}

/*********************************************
 * PROJECTILE : DRAW
 * Draw the projectile on the screen
 *********************************************/
void Projectile::draw(ogstream& gout) const
{
   for (int i = 0; i < 20; i++)
      gout.drawProjectile(flightPath[i], 0.5 * (double)i);
}

/*********************************************
 * PROJECTILE : IS FLYING
 * Is the projectile currently in the air?
 *********************************************/
bool Projectile::isFlying()
{
   return false;
}

/*********************************************
 * PROJECTILE : GET ALTITUDE
 * Return the projecile's current altitude
 *********************************************/
double Projectile::getAltitude()
{
   // where does the flight path start?
   return 0.0;
}

/*********************************************
 * PROJECTILE : GET POSITION
 * Return the projectile's current position
 *********************************************/
Position Projectile::getPosition()
{
   // where does the flight path start?
   return Position();
}

/*********************************************
 * PROJECTILE : GET FLIGHT TIME
 * How long has the projectile been in the air?
 *********************************************/
double Projectile::getFlightTime()
{
   return 0.0;
}

/*********************************************
 * PROJECTILE : GET FLIGHT DISTANCE
 * How far has the projectile traveled?
 *********************************************/
double Projectile::getFlightDistance()
{
   return 0.0;
}

/*********************************************
 * PROJECTILE : GET SPEED
 * Return the projectile's current velocity
 *********************************************/
double Projectile::getSpeed()
{
   return 0.0;
}

/*********************************************
 * PROJECTILE : FIRE
 * Launch the projectile
 *********************************************/
void Projectile::fire(Position pos, double time, Direction angle, Velocity vel)
{

}

/*********************************************
 * PROJECTILE : ADVANCE
 * Move the projectile by one unit of time
 *********************************************/
void advance(double time)
{

}