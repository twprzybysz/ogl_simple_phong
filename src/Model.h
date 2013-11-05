#pragma once
#include "gl_3_3.h"
#include <vector>
#include "Submodel.h"

class Model{

public:
	Model();
	void Init(const std::string& Filename, const std::string& diffuse, const std::string& spec, const std::string& gloss, const std::string& normal);
	void Render();
	void PrepareTextures();
	~Model();

private:
	GLuint diffuse_mTextureBuffer;
	GLuint sub_mTextureBuffer;
	GLuint fresnel_mTextureBuffer;
	GLuint normal_mTextureBuffer;

	int face;
	typedef std::vector<Submodel*> VecModels;
	VecModels mModels;
};