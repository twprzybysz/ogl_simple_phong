#include "CoreApp.h"
#include "main.h"
#include "utils.h"
#include <assimp/Importer.hpp>      // C++ importer interface 
#include <assimp/scene.h>           // Output data structure 
#include <assimp/postprocess.h>     // Post processing flags
#include <iostream>

CoreApp::CoreApp() {
	instance = this;
}

void CoreApp::loop() {
	double deltaTime;
    utils::updateTimer(&deltaTime, &Globals::sAppTime);
	
    utils::calculateFps(&Globals::sFps);

	// call Update:
	instance->update(deltaTime);

	// render frame:
	instance->render();

	TwDraw();

	glutSwapBuffers();
}

void CoreApp::renderCall() {
	instance->render();
}


bool CoreApp::Run(int argc, char **argv){
	
	//
	// init GLUT
	//
	glutInit(&argc, argv);

#ifdef USE_ONLY_CORE_OPENGL_PROFILE
	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
#endif

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );//| GLUT_MULTISAMPLE);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(Globals::sMainWindowWidth, Globals::sMainWindowHeight);
	// glutMainLoop returns and we can release our resources
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	if (glutCreateWindow(WND_TITLE) < 1)
	{
		LOG_ERROR("Cannot create the main GLUT window!");
		return 1;
	}

	//KEYBOARD CALLBACKS
	glutKeyboardFunc(keyboardUp);
	glutSpecialFunc(specialKeyboardDown);
	glutSpecialUpFunc(specialKeyboardUp);
	//MOUSE CALLBACKS
	glutMouseFunc(mouseButtonPress);
	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mouseMove);
	//APP CALLBACKS
	glutDisplayFunc(renderCall);
	glutIdleFunc(loop);
	glutReshapeFunc(reshapeCall);

	// random:
	srand((unsigned int)time(NULL));   

	//
	// 'init' OpenGL: GLEW... and print some basic info
	//
	if (utils::initGL(true) == false) 
		return 1;
	
	// Initialize AntTweakBar
#ifdef USE_ONLY_CORE_OPENGL_PROFILE
	TwInit(TW_OPENGL_CORE, NULL);
#else
	TwInit(TW_OPENGL, NULL);
#endif
	Globals::sMainTweakBar = TwNewBar("TweakBar");
	TwAddVarRO(Globals::sMainTweakBar, "FPS", TW_TYPE_FLOAT, &Globals::sFps, NULL);

	//
	// init whole application:
	//
	if (this->Init() == false)
	{
		LOG_ERROR("cannot init application...");
		return 1;
	}

	glutMainLoop();

	//
	// finish:
	//
	//cleanUp();
	TwTerminate();

	return(0);
}

void CoreApp::reshapeCall(int width, int height) {
	instance->reshape(width, height);
}

void CoreApp::reshape(int width, int height) {
	Globals::sMainWindowWidth = width;
    Globals::sMainWindowHeight = height;

	float aspect = (float)width/(float)height;

    // Set the viewport to be the entire window
    glViewport(0, 0, width, height);

    // setup projection matrix
	gProjectionMatrix = glm::perspective(45.0f, aspect, 0.01f, 1000.0f);

	// Send the new window size to AntTweakBar
    TwWindowSize(width, height);
}

#pragma region mouse

///////////////////////////////////////////////////////////////////////////////
void CoreApp::mouseButtonPress(int button, int state, int x, int y) {
	TwEventMouseButtonGLUT(button, state, x, y);
}

///////////////////////////////////////////////////////////////////////////////
void CoreApp::mouseMove(int x, int y) {
	TwEventMouseMotionGLUT(x, y);	

}

///////////////////////////////////////////////////////////////////////////////
void CoreApp::mousePassiveMove(int button, int state, int x, int y) {
	TwEventMouseMotionGLUT(x, y);	
}
#pragma endregion

#pragma region keyboard
///////////////////////////////////////////////////////////////////////////////
void CoreApp::keyboardDown(unsigned char key, int x, int y) {
}

///////////////////////////////////////////////////////////////////////////////
void CoreApp::keyboardUp(unsigned char key, int x, int y) {
}

///////////////////////////////////////////////////////////////////////////////
void CoreApp::specialKeyboardDown(int key, int x, int y) {
	//    if (key == GLUT_KEY_UP)
 //       gCamPos[2] += 1;
 //   else if (key == GLUT_KEY_DOWN)
 //       gCamPos[2] -= 1;

	//else if (key == GLUT_KEY_LEFT)
 //       gCamPos[0] += 0.1f;
 //   else if (key == GLUT_KEY_RIGHT)
 //       gCamPos[0] -= 0.1f;

}

///////////////////////////////////////////////////////////////////////////////
void CoreApp::specialKeyboardUp(int key, int x, int y) {
}

#pragma endregion

CoreApp *CoreApp::instance = NULL;