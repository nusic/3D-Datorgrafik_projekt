
//#define NDEBUG

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <iostream>
#include <string>
#include <cassert>

#include "ModelMesh.h"
#include "sgct.h"


class Model{
public:
	Model(ModelMesh* _mesh = NULL,
		  glm::mat4 M = glm::mat4(1.0),
		  std::string _shaderName = "SimpleColor");

	void setShader(std::string _shaderName);
	void setModelMatrix(glm::mat4 _modelMatrix);

    bool hasMesh() const;

	friend class Scene;
    void drawModel(glm::mat4 MVP);

protected:



	//transformation matrix specifik for this model
	glm::mat4 modelMatrix;
	std::vector<Model> children;

private:

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



};


#endif
