#include "Model.h"

Model::Model(ModelMesh* _mesh, glm::mat4 M): 
modelMatrix(M), mesh(_mesh) {
	std::cout << "created Model" << std::endl;
}

void Model::drawModel(glm::mat4 MVP) const{
	//stuff here
}