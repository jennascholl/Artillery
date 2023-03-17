/***********************************************************************
 * Source File:
 *    Howitzer : The representation of the Howitzer on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about the M777 Howitzer.
 ************************************************************************/

#include "howitzer.h"

/*********************************************
 * HOWITZER : CONSTRUCTOR
 * Get everything set up
 *********************************************/
Howitzer::Howitzer()
{

}

/*********************************************
 * HOWITZER : DRAW
 * Draw the Howitzer on the screen
 *********************************************/
void Howitzer::draw(ogstream& gout, double time) const
{
   gout.drawHowitzer(position, elevation.getRadians(), time);
}

/*********************************************
 * HOWITZER : GENERATE POSITION
 * Generate a position for the Howitzer
 *********************************************/
void Howitzer::generatePosition(double size)
{

}

/*********************************************
 * HOWITZER : RAISE
 * Bring the direction of the Howitzer back to center
 *********************************************/
void Howitzer::raise()
{
   
}