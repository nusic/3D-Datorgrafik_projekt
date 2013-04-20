#include <vector>
#include <iostream>
#include <string>

#include "ModelMesh.h"
#include "sgct.h"


#ifndef MODEL_H
#define MODEL_H

class Model{
public:
	Model(ModelMesh* _mesh = NULL, glm::mat4 M = glm::mat4(1.0));

	void drawModel(glm::mat4 MVP) const;

	//transformation matrix specifik for this model
	glm::mat4 modelMatrix;
	ModelMesh* mesh;
	std::string shaderName;

	//std::vector<Model> children;
};


#endif