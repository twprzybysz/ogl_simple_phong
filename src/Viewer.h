#pragma once

#include "stdafx.h"
#include "CoreApp.h"

#include "ShaderProgram.h"
#include "AbstractScene.h"

#include <assimp\Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.h"


class AbstractScene;

typedef std::map<char*,ShaderProgram*> ShaderCollection;
typedef std::map<char*,Model*> ModelCollection; 
typedef std::map<char*,AbstractScene*> SceneMap; 

class Viewer : public CoreApp {

public:
	Viewer(int width, int height);
	~Viewer();
	bool Init();
	void render();
	void update(double delta);

protected:
	glm::vec3 gLightPos;
	glm::quat objRot;
	glm::quat camRot;

	#define VERTEX_ATTRIB_POSITION  0
	#define VERTEX_ATTRIB_TEXCOORD0 1

	// shaders:
	ShaderCollection shaderMap;
	// models
	ModelCollection modelMap;

	float gAnimParam;// = 0.0f;

	int m_width;
	int m_height;
	bool isEnabled;

	GLuint whiteTexture;
	SceneMap scene;
};