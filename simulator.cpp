/***********************************************************************
 * Source File:
 *    Simulator : Governs the relationship between gun and bullet
 * Author:
 *    Jenna Scholl
 * Summary:
 *    Ties all the elements together
 ************************************************************************/

#include "simulator.h"

/*********************************************
* SIMULATOR : RESET
* Reset the simulator
*********************************************/
void Simulator::reset()
{
   status = LOADED;
   double simTime = 0.0;
   projectile.reset();
   howitzer.generatePosition(ptUpperRight, 20.0);
   Position posHowitzer = howitzer.getPosition();
   Direction direction;
   direction.setUp();
   howitzer.setDirection(direction);
   ground.reset(posHowitzer);
   howitzer.setPosition(posHowitzer);
}

/*********************************************
* SIMULATOR : DRAW
* Draw the simulator on the screen
*********************************************/
void Simulator::draw(ogstream& gout) const
{
   // draw some text on the screen
   gout.setf(ios::fixed | ios::showpoint);
   gout.precision(1);

   ground.draw(gout);
   howitzer.draw(gout, simTime);
   if (status == FLYING)
   {
      projectile.draw(gout);

      gout.setPosition(Position(ptUpperRight.getMetersX() * 0.83, ptUpperRight.getMetersY() * 0.95));
      gout << "Altitude: "
           << projectile.getAltitude() << "\tm\n"
           << "Speed: "
           << projectile.getSpeed() << "\tm/s\n"
           << "Distance: "
           << projectile.getFlightDistance() << "\tm\n"
           << "Hang Time: "
           << projectile.getFlightTime() << "\ts\n";
   }
   else
   {
      gout.setPosition(Position(ptUpperRight.getMetersX() * 0.83, ptUpperRight.getMetersY() * 0.95));
      gout << "Angle: "
         << howitzer.getDirection().getDegrees() << " degrees\n";
   }

}

/*********************************************
* SIMULATOR : FIRE
* Fire the howitzer
*********************************************/
void Simulator::fire()
{
   status = FLYING;
   projectile.fire(howitzer.getPosition(), interval, howitzer.getDirection(), howitzer.getMuzzleVelocity());
}

/*********************************************
* SIMULATOR : ADVANCE
* Advance everything by one unit of time
*********************************************/
void Simulator::advance()
{
   if (status == FLYING)
   {
      simTime += interval;
      projectile.advance(interval);
      if (ground.getElevationMeters(projectile.getPosition()) >= getHeightMeters())
         status = LANDED;

      if (status == LANDED)
      {         
         if (!hitTarget())
         {
            status = LOADED;
            double simTime = 0.0;
            projectile.reset();
         }
         else
            reset();
      }
   }
}

/*********************************************
* SIMULATOR : INPUT
* Get input from the user
*********************************************/
void Simulator::input(const Interface* pUI)
{
   // fire that gun
   if (pUI->isSpace() && status == LOADED)
      fire();

   // recenter the gun
   else if (pUI->isUp() || pUI->isDown())
      howitzer.raise();

   // rotate left or right
   else if (pUI->isLeft())
      howitzer.rotate(-0.05);
   else if (pUI->isRight())
      howitzer.rotate(0.05);
}

/*********************************************
* SIMULATOR : HIT TARGET
* Have we hit the target?
*********************************************/
bool Simulator::hitTarget()
{
   if (ground.getTarget().getPixelsX() >= projectile.getPosition().getPixelsX() - 5 &&
       ground.getTarget().getPixelsX() <= projectile.getPosition().getPixelsX() + 5)
      return true;
   else
      return false;
}

/*********************************************
* SIMULATOR : GET HEIGHT METERS
* Get the height in meters
*********************************************/
double Simulator::getHeightMeters()
{
   return projectile.getAltitude();
}