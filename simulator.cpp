/***********************************************************************
 * Source File:
 *    Simulator : Governs the relationship between gun and bullet
 * Author:
 *    Jenna Scholl & Neil Reed
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
   ground.reset(posHowitzer);
   howitzer.setPosition(posHowitzer);
}

/*********************************************
* SIMULATOR : DRAW
* Draw the simulator on the screen
*********************************************/
void Simulator::draw(ogstream& gout) const
{
   ground.draw(gout);
   howitzer.draw(gout, simTime);
   if (status == FLYING)
   {
      projectile.draw(gout);

      // draw some text on the screen
      gout.setf(ios::fixed | ios::showpoint);
      gout.precision(1);
      gout << "Time since the bullet was fired: "
         << projectile.getFlightTime() << "s\n";
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

      if (status == LANDED && !hitTarget())
      {
         status = LOADED;
         double simTime = 0.0;
         projectile.reset();
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
   if (ground.getTarget() == projectile.getPosition())
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