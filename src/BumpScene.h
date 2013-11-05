#pragma once
#include "AbstractScene.h"
#include "Model.h"

class BumpScene : public AbstractScene {
public:
	explicit BumpScene(ShaderCollection* shader);
	virtual ~BumpScene();
	void Render();

	void setCurrentTexture(GLuint *tex) { whitetex = tex; }
private:
	BumpScene(BumpScene& scene); // forbidden to copy

	//tex
	GLuint *whitetex;
};