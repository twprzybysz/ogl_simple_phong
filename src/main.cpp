/** @file main.cpp
 *  @brief core code for the sample, init, freeGlut setup, etc, etc
 *
 *	Effects in Games, June 2012
 */

#include "main.h"
#include "stdafx.h"
#include "Viewer.h"

#pragma region globals

///////////////////////////////////////////////////////////////////////////////

// time:
double Globals::sAppTime = 0.0;	// global app time in seconds
float Globals::sFps = 0.0f;

unsigned int Globals::sMainWindowWidth = WINDOW_WIDTH;
unsigned int Globals::sMainWindowHeight = WINDOW_HEIGHT;

TwBar *Globals::sMainTweakBar = NULL;

#pragma endregion

///////////////////////////////////////////////////////////////////////////////
// entry point
int main(int argc, char **argv)
{
	Viewer app(Globals::sMainWindowWidth,Globals::sMainWindowHeight);
	return app.Run(argc,argv);
}