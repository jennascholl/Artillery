/***********************************************************************
 * Source File:
 *    Projectile : A bullet to hit a target
 * Author:
 *    Jenna Scholl
 * Summary:
 *    Everything we need to know about our ammunition
 ************************************************************************/

#include "projectile.h"
#include "physics.h"

/*********************************************
 * PROJECTILE : CONSTRUCTOR
 * Get everything set up
 *********************************************/
Projectile::Projectile() : flightPath(20), launchPos(Position())
{
   setMass(46.7);
   setRadius(0.07745);

   for (int i = 0; i < 20; i++)
   {
      flightPath[i].pos.setMetersX(0.0);
      flightPath[i].pos.setMetersY(0.0);
      flightPath[i].time = 0.0;
      flightPath[i].vel.setDX(0.0);
      flightPath[i].vel.setDY(0.0);

   }
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
   int size = flightPath.size();
   for (int i = 0; i < size; i++)
      gout.drawProjectile(flightPath[i].pos, 0.5 * (double)i);
}

/*********************************************
 * PROJECTILE : IS FLYING
 * Is the projectile currently in the air?
 *********************************************/
bool Projectile::isFlying()
{
   return !flightPath.empty()/* || flightPath.back().pos.getMetersY() > 0.0*/;
}

/*********************************************
 * PROJECTILE : GET ALTITUDE
 * Return the projecile's current altitude
 *********************************************/
double Projectile::getAltitude() const
{
   return flightPath.front().pos.getMetersY();
}

/*********************************************
 * PROJECTILE : GET POSITION
 * Return the projectile's current position
 *********************************************/
Position Projectile::getPosition() const
{
   return flightPath.front().pos;
}

/*********************************************
 * PROJECTILE : GET FLIGHT TIME
 * How long has the projectile been in the air?
 *********************************************/
double Projectile::getFlightTime() const
{
   return flightPath.front().time;
}

/*********************************************
 * PROJECTILE : GET FLIGHT DISTANCE
 * How far has the projectile traveled?
 *********************************************/
double Projectile::getFlightDistance() const
{
   double distance = flightPath.front().pos.getMetersX() - launchPos.getMetersX();
   if (distance < 0)
      return -distance;
   else
      return distance;
}

/*********************************************
 * PROJECTILE : GET SPEED
 * Return the projectile's current velocity
 *********************************************/
double Projectile::getSpeed() const
{
   return flightPath.front().vel.getSpeed();
}

/*********************************************
 * PROJECTILE : FIRE
 * Launch the projectile
 *********************************************/
void Projectile::fire(Position pos, double time, Direction angle, double vel)
{
   PVT pvt;
   pvt.pos = pos;
   pvt.vel = Velocity(vel, angle);
   pvt.time = time;

   flightPath.push_back(pvt);

   launchPos = pos;
}

/*********************************************
 * PROJECTILE : ADVANCE
 * Move the projectile by one unit of time
 *********************************************/
void Projectile::advance(double time)
{
   PVT pvt = flightPath.front();
   double speed = pvt.vel.getSpeed();
   double altitude = pvt.pos.getMetersY();
   Direction down;
   down.setDown();

   // modify velocity to accomodate wind resistance
   double density = densityFromAltitude(altitude);
   double dragCoefficient = dragFromSpeed(speed, altitude);
   double windResistance = forceFromDrag(density, dragCoefficient, radius, speed);
   double accelerationDrag = accelerationFromForce(windResistance, mass);
   double velocityWind = (velocityFromAcceleration(accelerationDrag, time));
   pvt.vel.addDY(-velocityWind);

   // modify velocity to handle gravity
   double accelerationGravity = gravityFromAltitude(altitude);
   double velocityGravity = (velocityFromAcceleration(accelerationGravity, time));
   pvt.vel.addDY(-velocityGravity);

   // inertia
   pvt.pos.addMetersX(velocityFromAcceleration(pvt.vel.getDX(), time));
   pvt.pos.addMetersY(velocityFromAcceleration(pvt.vel.getDY(), time));

   // update time
   pvt.time += time;

   // remove the oldest pvt when we reach 20
   if (flightPath.size() > 19)
      flightPath.pop_back();
      
   // add it to the back of the flight path
   flightPath.insert(flightPath.begin(), pvt);
}