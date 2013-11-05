#pragma once 

#include "stdafx.h"

class CoreApp {

public:
	virtual void  update(double delta) = 0;
	// Main Rendering
	static void renderCall();

	virtual void render() = 0;
	// Game loop
	static void loop();

	bool Run(int argc, char **argv);

	void reshape(int width, int height);
	static void reshapeCall(int width, int height);

	static void mouseMove(int x, int y);

	static void mousePassiveMove(int button, int state, int x, int y);

	static void mouseButtonPress(int button, int state, int x, int y);

	static void keyboardDown(unsigned char key, int x, int y);

	static void keyboardUp(unsigned char key, int x, int y);

	static void specialKeyboardDown(int key, int x, int y);

	static void specialKeyboardUp(int key, int x, int y);

	virtual bool Init() = 0;
	CoreApp();

protected:
	static CoreApp *instance;

	// camera
	glm::vec3 gCamPos;
	glm::vec3 gEyePos;

	// transformations
	glm::mat4 gModelViewMatrix;
	glm::mat4 gProjectionMatrix;
};