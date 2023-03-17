/***********************************************************************
 * Source File:
 *    Projectile : A bullet to hit a target
 * Author:
 *    Jenna Scholl & Neil Reed
 * Summary:
 *    Everything we need to know about our ammunition
 ************************************************************************/

#include "projectile.h"
#include "physics.h"

/*********************************************
 * PROJECTILE : CONSTRUCTOR
 * Get everything set up
 *********************************************/
Projectile::Projectile()
{
   setMass(46.7);
   setRadius(0.07745);
   flightPath.reserve(20);
}

/*********************************************
 * PROJECTILE : RESET
 * Revert all the values back to their original state
 *********************************************/
void Projectile::reset()
{
   flightPath.clear();
}

/*********************************************
 * PROJECTILE : DRAW
 * Draw the projectile on the screen
 *********************************************/
void Projectile::draw(ogstream& gout) const
{
   for (int i = 0; i < 20; i++)
      gout.drawProjectile(flightPath[i].pos, 0.5 * (double)i);
}

/*********************************************
 * PROJECTILE : IS FLYING
 * Is the projectile currently in the air?
 *********************************************/
bool Projectile::isFlying()
{
   return flightPath.empty()/* || flightPath.back().pos.getMetersY() > 0.0*/;
}

/*********************************************
 * PROJECTILE : GET ALTITUDE
 * Return the projecile's current altitude
 *********************************************/
double Projectile::getAltitude()
{
   return flightPath.back().pos.getMetersY();
}

/*********************************************
 * PROJECTILE : GET POSITION
 * Return the projectile's current position
 *********************************************/
Position Projectile::getPosition()
{
   return flightPath.back().pos;
}

/*********************************************
 * PROJECTILE : GET FLIGHT TIME
 * How long has the projectile been in the air?
 *********************************************/
double Projectile::getFlightTime()
{
   return flightPath.back().time;
}

/*********************************************
 * PROJECTILE : GET FLIGHT DISTANCE
 * How far has the projectile traveled?
 *********************************************/
double Projectile::getFlightDistance()
{
   return flightPath.back().pos.getMetersX() - flightPath.front().pos.getMetersX();
}

/*********************************************
 * PROJECTILE : GET SPEED
 * Return the projectile's current velocity
 *********************************************/
double Projectile::getSpeed()
{
   return flightPath.back().vel.getSpeed();
}

/*********************************************
 * PROJECTILE : FIRE
 * Launch the projectile
 *********************************************/
void Projectile::fire(Position pos, double time, Direction angle, Velocity vel)
{
   PVT pvt;
   pvt.pos = pos;
   pvt.vel = vel;
   pvt.time = time;

   flightPath.push_back(pvt);
}

/*********************************************
 * PROJECTILE : ADVANCE
 * Move the projectile by one unit of time
 *********************************************/
void Projectile::advance(double time)
{
   PVT pvt = flightPath.back();
   double speed = pvt.vel.getSpeed();
   double altitude = pvt.pos.getMetersY();
   Direction down;
   down.setDown();

   // modify velocity to accomodate wind resistance
   double density = densityFromAltitude(altitude);
   double dragCoefficient = dragFromSpeed(speed, altitude);
   double windResistance = forceFromDrag(density, dragCoefficient, radius, speed);
   double accelerationDrag = accelerationFromForce(windResistance, mass);
   Velocity velocityWind(velocityFromAcceleration(accelerationDrag, time), down.getRadians());
   velocityWind.reverse();
   pvt.vel.addVelocity(velocityWind);

   // modify velocity to handle gravity
   double accelerationGravity = gravityFromAltitude(altitude);
   Velocity velocityGravity(velocityFromAcceleration(accelerationGravity, time), down.getRadians());
   pvt.vel.addVelocity(velocityWind);

   // inertia
   pvt.pos.addMetersX(velocityFromAcceleration(pvt.vel.getDX(), time));
   pvt.pos.addMetersY(velocityFromAcceleration(pvt.vel.getDY(), time));

   // update time
   pvt.time += time;

   // add it to the back of the flight path
   flightPath.push_back(pvt);
}