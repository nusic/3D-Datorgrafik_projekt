
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



class Model{
public:
	Model(ModelMesh* _mesh = NULL, 
		  glm::mat4 M = glm::mat4(1.0),
		  std::string _textureName = "SimpleTexture",
		  std::string _shaderName = "SimpleColor");

	~Model();

	void setShader(std::string _shaderName);
	void setTexture(std::string _textureName);
	void setModelMatrix(glm::mat4 _modelMatrix);

    bool hasMesh() const;

	friend class Scene;
    void drawModel(glm::mat4 P, glm::mat4 V, glm::mat4 M);

protected:

	//transformation matrix specifik for this model
	glm::mat4 modelMatrix;
	std::vector<Model*> children;

private:

	ModelMesh* mesh;
	std::string shaderName;
	
	//Handles for the shader
	GLuint vertexPositionID;
	GLuint vertexUVID;
	GLuint vertexNormalID;

	GLuint textureID;

	GLuint MVPMatrixID;
	GLuint modelMatrixID;
	GLuint viewMatrixID;
	GLuint modelViewMatrixID;

	//Handle for matrix and texture
	GLuint texture;	

};


#endif
