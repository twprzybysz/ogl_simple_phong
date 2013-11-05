/** @file main.h
 *  @brief common includes, function prototypes for samples
 *
 *	Effects in Games, June 2012
 */

#pragma once

#include "addons\AntTweakBar.h"

#define WND_TITLE "OpenGL Sample"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

//#define USE_ONLY_CORE_OPENGL_PROFILE
//#define DO_NOT_SHOW_CONSOLE


#ifdef DO_NOT_SHOW_CONSOLE
	#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif


using namespace std;

///////////////////////////////////////////////////////////////////////////////
struct Globals 
{
    static double sAppTime;	// global app time in seconds
    static float sFps;

    static unsigned int sMainWindowWidth;
    static unsigned int sMainWindowHeight;

    static TwBar *sMainTweakBar;
};
///////////////////////////////////////////////////////////////////////////////