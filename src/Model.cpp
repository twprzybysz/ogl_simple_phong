#include "Model.h"

#include <assimp\Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "utils.h"

using namespace std;

Model::Model() { 
}

void Model::Init(const std::string& Filename, const std::string& diffuse, const std::string& spec, const std::string& gloss, const std::string& normal) {
	
	diffuse_mTextureBuffer = helpers::ogl::loadTexture(diffuse.c_str());
	sub_mTextureBuffer = helpers::ogl::loadTexture(spec.c_str());
	fresnel_mTextureBuffer = helpers::ogl::loadTexture(gloss.c_str());
	normal_mTextureBuffer = helpers::ogl::loadTexture(normal.c_str());

    Assimp::Importer Importer;
    const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace );
    if (pScene) {
		for (int i = 0; i < pScene->mNumMeshes; i++) {
			mModels.push_back(new Submodel(pScene->mMeshes[i]));
		}
    } else {
        printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
    }
}

void Model::PrepareTextures() {
	helpers::ogl::setTexture(GL_TEXTURE0, diffuse_mTextureBuffer);
	helpers::ogl::setTexture(GL_TEXTURE1, sub_mTextureBuffer);
	helpers::ogl::setTexture(GL_TEXTURE2, fresnel_mTextureBuffer);
	helpers::ogl::setTexture(GL_TEXTURE3, normal_mTextureBuffer);
}

void Model::Render() {
	for (VecModels::iterator it = mModels.begin() ; it != mModels.end(); ++it) {
		(*it)->Render();
	}
}

Model::~Model() {
	glDeleteBuffers(1,&diffuse_mTextureBuffer);
	glDeleteBuffers(1,&sub_mTextureBuffer);
	glDeleteBuffers(1,&fresnel_mTextureBuffer);
	glDeleteBuffers(1,&normal_mTextureBuffer);

	for (int i = 0; i < mModels.size(); i++) {
		Submodel* pModel = mModels.back();
		delete pModel;
		pModel = 0;
		mModels.pop_back();
	}
}