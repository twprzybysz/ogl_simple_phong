#pragma once

#include "stdafx.h"
#include "ShaderProgram.h"
#include "Model.h"

typedef std::map<char*,ShaderProgram*> ShaderCollection;

/**
 * Class dedicated to create scenes
 */
class AbstractScene {
	public:
		AbstractScene(ShaderCollection* shaderMap):pShaderMap(shaderMap),pProj(0), pWorld(0){};
		virtual void Render() = 0;
		virtual ShaderProgram* getShader(char* shaderName) { return (*pShaderMap)[shaderName]; }

		virtual void setProjectionMatrix(glm::mat4* proj) { pProj = proj; }
		virtual void setWorldMatrix(glm::mat4* world) { pWorld = world; }
		virtual glm::mat4* getProjectionMatrix() { return pProj; }
		virtual glm::mat4* getWorldMatrix() { return pWorld; }

		void setLightPosition(glm::vec3* lightPos) { pLightPosition = lightPos; }
		glm::vec3 getLightPosition() { return *pLightPosition; }

		void setCurrentModel(Model *mod) { model = mod; }
		Model* getCurrentModel() { return model; }

		void setModelRotation(glm::mat4 *rot) { pRotation = rot; }

	private:
		// ban copying
		AbstractScene(AbstractScene& as);		

	protected:
		ShaderCollection* pShaderMap;
		glm::mat4* pProj;
		glm::mat4* pWorld;
		glm::vec3* pLightPosition;

		glm::mat4* pRotation;
		//model
		Model* model;
};