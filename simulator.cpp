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
 * SIMULATOR : CONSTRUCTOR
 * Get everything set up
 *********************************************/
Simulator::Simulator()
{

}

/*********************************************
* SIMULATOR : RESET
* Reset the simulator
*********************************************/
void Simulator::reset()
{

}

/*********************************************
* SIMULATOR : DRAW
* Draw the simulator on the screen
*********************************************/
void Simulator::draw(ogstream& gout) const
{
   ground.draw(gout);
   howitzer.draw(gout, simTime);
   projectile.draw(gout);
}

/*********************************************
* SIMULATOR : FIRE
* Fire the howitzer
*********************************************/
void Simulator::fire()
{

}

/*********************************************
* SIMULATOR : ADVANCE
* Advance everything by one unit of time
*********************************************/
void Simulator::advance()
{

}

/*********************************************
* SIMULATOR : INPUT
* Get input from the user
*********************************************/
void Simulator::input(const Interface* pUI)
{

}

/*********************************************
* SIMULATOR : HIT TARGET
* Have we hit the target?
*********************************************/
void Simulator::hitTarget()
{

}

/*********************************************
* SIMULATOR : GET HEIGHT METERS
* Get the height in meters
*********************************************/
void Simulator::getHeightMeters()
{

}