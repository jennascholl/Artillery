/*************************************************************
 * 1. Name:
 *      Jenna Scholl & Neil Reed
 * 2. Assignment Name:
 *      Lab 08: M777 Howitzer
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was trying to make sure everything was
 *      thoroughly tested.
 * 5. How long did it take for you to complete the assignment?
 *      It took about 3 hours to complete this assignment
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "ground.h"     // for GROUND
#include "position.h"   // for POINT
#include "simulator.h"
#include "test.h"       // for TESTRUNNER()
using namespace std;

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   ogstream gout;

   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator* sim = (Simulator*)p;

   //
   // accept input
   //

   sim->input(pUI);

   //
   // perform all the game logic
   //

   sim->advance();

   //
   // draw everything
   //

   sim->draw(gout);
}


double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // run unit tests
   testRunner();

   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setPixelsX(700.0);
   ptUpperRight.setPixelsY(500.0);
   Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
   Interface ui(0, NULL,
      "Artillery Simulator",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Simulator sim(ptUpperRight);

   // set everything into action
   ui.run(callBack, &sim);


   return 0;
}
