#include "Model.h"

Model::Model(glm::mat4 M, ModelMesh* _mesh): 
modelMatrix(M), mesh(_mesh) {
	std::cout << "created Model" << std::endl;
}

void Model::drawModel(glm::mat4 MVP) const{
	//stuff here
}