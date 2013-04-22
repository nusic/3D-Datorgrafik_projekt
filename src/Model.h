#include <vector>
#include <iostream>
#include <string>

#include "ModelMesh.h"
#include "sgct.h"

//#define NDEBUG

#ifndef MODEL_H
#define MODEL_H

class Model{
public:
	Model(ModelMesh* _mesh = NULL, 
		  glm::mat4 M = glm::mat4(1.0), 
		  std::string _shaderName = "std_shader");

	void drawModel(glm::mat4 MVP) const;

	void setShader(std::string _shaderName);
	void setModelMatrix(glm::mat4 _modelMatrix);



private:

	//transformation matrix specifik for this model
	glm::mat4 modelMatrix;
	ModelMesh* mesh;
	std::string shaderName;
	
	//Handles for mesh
	GLuint vertexShaderID;
	GLuint normalShaderID;
	GLuint UVShaderID;

	//Handle for matrix
	GLuint modelMatrixID;

	//GLuint textureShaderID;
	GLuint matrixShaderID;


	//std::vector<Model> children;
};


#endif