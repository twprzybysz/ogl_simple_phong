#include "Viewer.h"

#include "stdafx.h"
#include "main.h"
#include "utils.h"

#include "Shader.h"
#include "ShaderProgram.h"
#include "ShaderUtils.h"
#include "utils.h"

#include "BumpScene.h"
#include "utils.h"

Viewer::Viewer(int width, int height): CoreApp(), m_width(width), m_height(height), isEnabled(true) {
	gAnimParam = 0;
}

void Viewer::update(double delta) {
	if (isEnabled) {
		gAnimParam += 1.0f * static_cast<float>(delta);

		gLightPos.x = 3.0f*cosf(gAnimParam);
		gLightPos.y = 3;
		gLightPos.z = 3.0f*sinf(gAnimParam);
	}
}

bool Viewer::Init() {
	whiteTexture = helpers::ogl::loadTexture(CONCAT("textures", "white.png"));

	char* modelArray[][6] = {
		{"bar", CONCAT("models", "bar.obj"), CONCAT(TEXTURES_PATH, "bar/albedo.png"), CONCAT(TEXTURES_PATH, "bar/subsbance.png"), CONCAT(TEXTURES_PATH, "bar/rough.png"),CONCAT(TEXTURES_PATH, "bar/normal.png") },
	};

	int length = sizeof(modelArray) / sizeof(modelArray[0]);

	for (int i = 0; i<length; i++) {
		Model * tmp = new Model();
		tmp->Init(modelArray[i][1], modelArray[i][2],modelArray[i][3], modelArray[i][4], modelArray[i][5]);
		modelMap.insert(std::pair<char*,Model*>(modelArray[i][0],tmp));
	}

	//
	// some global GL states
	//
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //
    // camera pos
    //
    gCamPos[0] = 7.0f;
    gCamPos[1] = 7.0f;
    gCamPos[2] = 7.0f;

	//
	// Eye pos
	//
	 gEyePos[0] = 0;
	 gEyePos[1] = 3;
	 gEyePos[2] = 0;

	//
	// Light pos
	//
	gLightPos.x = 20;
	gLightPos.y = 20;
	gLightPos.z = 20;

    //
    // shaders loader
    //
	char* parameters[][3] = {
		{"bumpShader", CONCAT(SHADERS_PATH, "bump.vs"), CONCAT(SHADERS_PATH, "bump.fs")},
	};

	int parametersLength = sizeof(parameters) / sizeof(parameters[0]);

	for (int i = 0; i<parametersLength; i++) {
		ShaderProgram* tmp = new ShaderProgram();
		if(shaderUtils::loadAndBuildShaderPairFromFile(tmp, parameters[i][1], parameters[i][2])) {
			shaderMap.insert(std::pair<char*,ShaderProgram*>(parameters[i][0],tmp));
		} else {
			delete tmp;
			assert(false && "Error in shader");
			exit(-1); 
		}		
	}

	//
    // UI:
    //
    TwAddVarRW(Globals::sMainTweakBar, "camera Z", TW_TYPE_FLOAT, &gCamPos[2], "min=-12.0 max=12.0 step=0.1");
	TwAddVarRW(Globals::sMainTweakBar, "camera Y", TW_TYPE_FLOAT, &gCamPos[1], "min=-12.0 max=12.0 step=0.1");
	TwAddVarRW(Globals::sMainTweakBar, "camera X", TW_TYPE_FLOAT, &gCamPos[0], "min=-12.0 max=12.0 step=0.1");

	TwAddVarRW(Globals::sMainTweakBar, "eye Z", TW_TYPE_FLOAT, &gEyePos[2], "min=-12.0 max=12.0 step=0.1");
	TwAddVarRW(Globals::sMainTweakBar, "eye Y", TW_TYPE_FLOAT, &gEyePos[1], "min=-12.0 max=12.0 step=0.1");
	TwAddVarRW(Globals::sMainTweakBar, "eye X", TW_TYPE_FLOAT, &gEyePos[0], "min=-12.0 max=12.0 step=0.1");

	TwAddVarRW(Globals::sMainTweakBar, "isAnimated", TW_TYPE_BOOLCPP, &isEnabled, "");
	TwAddVarRW(Globals::sMainTweakBar, "Object rotation", TW_TYPE_QUAT4F, &objRot, " label='Object rotation' open help='Change the object orientation.' ");
	TwAddVarRW(Globals::sMainTweakBar, "Camera rotation", TW_TYPE_QUAT4F, &camRot, " label='Camera rotation' open help='Change the object orientation.' ");
	

	scene.insert(std::pair<char*,AbstractScene*>("bumpScene",new BumpScene(&shaderMap)));

	return true;
}

Viewer::~Viewer(){	
	helpers::freeMap<SceneMap>(scene);
	helpers::freeMap<ShaderCollection>(shaderMap);

	glDeleteBuffers(1,&whiteTexture);
}

void Viewer::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::vec4 cam = glm::mat4_cast(camRot) * glm::vec4( gCamPos,1);

	gModelViewMatrix = glm::lookAt(glm::vec3(cam), gEyePos, glm::vec3(0.0f, 1.0f, 0.0f)); 
	gModelViewMatrix = gModelViewMatrix;

	BumpScene* currentScene = (BumpScene*)scene["bumpScene"];

	currentScene->setWorldMatrix(&gModelViewMatrix);
	currentScene->setProjectionMatrix(&gProjectionMatrix);
	currentScene->setLightPosition(&gLightPos);

	currentScene->setCurrentTexture(&whiteTexture);
	currentScene->setModelRotation(&glm::mat4_cast(objRot));	
	currentScene->setCurrentModel(modelMap["bar"]);				

	currentScene->Render();	
}