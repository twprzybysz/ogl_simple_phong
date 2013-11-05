#include "Submodel.h"
#include "utils.h"

using namespace std;

Submodel::Submodel(aiMesh* paiMesh) {
	std::vector<float> m_Vert;
	std::vector<float> m_Norm;
	std::vector<float> m_Text;

	std::vector<float> m_Tangent;
	std::vector<float> m_BiTangent;

	std::vector<int> m_Ind;

	for (int j = 0; j < paiMesh->mNumVertices; j++) {
		m_Vert.push_back(paiMesh->mVertices[j].x);
		m_Vert.push_back(paiMesh->mVertices[j].y);
		m_Vert.push_back(paiMesh->mVertices[j].z);

		m_Norm.push_back(paiMesh->mNormals[j].x);
		m_Norm.push_back(paiMesh->mNormals[j].y);
		m_Norm.push_back(paiMesh->mNormals[j].z);

		m_Text.push_back(paiMesh->mTextureCoords[0][j].x);
		m_Text.push_back(paiMesh->mTextureCoords[0][j].y);

		if (paiMesh->HasTangentsAndBitangents()) {
			m_Tangent.push_back(paiMesh->mTangents[j].x);
			m_Tangent.push_back(paiMesh->mTangents[j].y);
			m_Tangent.push_back(paiMesh->mTangents[j].z);

			m_BiTangent.push_back(paiMesh->mBitangents[j].x);
			m_BiTangent.push_back(paiMesh->mBitangents[j].y);
			m_BiTangent.push_back(paiMesh->mBitangents[j].z);			
		}
	}

	for (unsigned int k = 0 ; k < paiMesh->mNumFaces ; k++) {
		const aiFace& Face = paiMesh->mFaces[k];
		assert(Face.mNumIndices == 3);
		m_Ind.push_back(Face.mIndices[0]);
		m_Ind.push_back(Face.mIndices[1]);
		m_Ind.push_back(Face.mIndices[2]);
	}

	helpers::ogl::setupBuffer(GL_ARRAY_BUFFER, m_PosBuffer, sizeof(float) * m_Vert.size(), &(m_Vert[0]), GL_STATIC_DRAW);
	helpers::ogl::setupBuffer(GL_ARRAY_BUFFER, m_NormalBuffer, sizeof(float) * m_Norm.size(),&(m_Norm[0]), GL_STATIC_DRAW);
	helpers::ogl::setupBuffer(GL_ARRAY_BUFFER, m_TexPosBuffer, sizeof(float)* m_Text.size(), &(m_Text[0]), GL_STATIC_DRAW);
	helpers::ogl::setupBuffer(GL_ARRAY_BUFFER, m_TangentBuffer, sizeof(float)* m_Tangent.size(), &(m_Tangent[0]), GL_STATIC_DRAW);
	helpers::ogl::setupBuffer(GL_ARRAY_BUFFER, m_BiTangentBuffer, sizeof(float)* m_BiTangent.size(), &(m_BiTangent[0]), GL_STATIC_DRAW);

	helpers::ogl::setupBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Index, sizeof(int)*m_Ind.size(), &(m_Ind[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_faceCount = paiMesh->mNumFaces * 3;
}

void Submodel::Render() {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1); 
	glEnableVertexAttribArray(2);
	//glEnableVertexAttribArray(3);
	//glEnableVertexAttribArray(4);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_PosBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_NormalBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_TexPosBuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	/*
	glBindBuffer(GL_ARRAY_BUFFER, m_TangentBuffer);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_BiTangentBuffer);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0);
	*/

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Index);
	glDrawElements(GL_TRIANGLES, m_faceCount, GL_UNSIGNED_INT, 0);	

	//glEnableVertexAttribArray(4);
	//glEnableVertexAttribArray(3);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

Submodel::~Submodel() {
	glDeleteBuffers(1,&m_PosBuffer);
	glDeleteBuffers(1,&m_NormalBuffer);
	glDeleteBuffers(1,&m_TexPosBuffer);
	glDeleteBuffers(1,&m_TangentBuffer);
	glDeleteBuffers(1,&m_BiTangentBuffer);
	glDeleteTextures(1, &m_Index);
}