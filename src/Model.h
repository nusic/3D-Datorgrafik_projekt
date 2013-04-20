#include <vector>
#include <iostream>

#include "ModelMesh.h"
#include "sgct.h"


#ifndef MODEL_H
#define MODEL_H

class Model{
public:
	Model(glm::mat4 M = glm::mat4(1.0), ModelMesh* _mesh = NULL);

	void drawModel(glm::mat4 MVP) const;

	//transformation matrix specifik for this model
	glm::mat4 modelMatrix;
	ModelMesh* mesh;
	GLuint shaderProgramID;

	std::vector<Model> children;
};


#endif