
//#define NDEBUG

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <iostream>
#include <string>
#include <cassert>

#include "ModelMesh.h"
#include "LightSource.h"
#include "sgct.h"
#include "ShadowMap.h"
#include "Camera.h"



class Model{
public:
	Model(ModelMesh* _mesh = NULL, 
		  glm::mat4 M = glm::mat4(1.0),
		  std::string _textureName = "SimpleTexture",
		  std::string _shaderName = "SimpleColor");

	~Model();

	void setShader(std::string _shaderName);
	void setMesh(ModelMesh * _mesh);
	void setTexture(std::string _textureName);
	void setLocalModelMatrix(glm::mat4 _localModelMatrix);

    bool hasMesh() const;

	friend class Scene;
    void drawModel(glm::mat4 P, glm::mat4 V, glm::mat4 M);
    void renderToDepthBuffer(glm::mat4 M, int lightSourceIndex);

protected:

	//transformation matrix specifik for this model
	glm::mat4 localModelMatrix;
	std::vector<Model*> children;

private:

	ModelMesh* mesh;
	std::string shaderName;
	
	//Handles for the shader
	GLuint vertexPositionID;
	GLuint vertexUVID;
	GLuint vertexNormalID;


	GLuint textureID;

	GLuint modelMatrixID;
	GLuint viewMatrixID;
	GLuint modelViewMatrixID;
	GLuint modelViewPerspectiveMatrixID;

	//Handle for matrix and texture
	GLuint texture;	

};


#endif
