#include "Transformation.h"

Transformation::Transformation(){
	matrix = glm::mat4(1.0f);
}

Transformation::~Transformation(){

}

glm::mat4 Transformation::getMatrix() const{
	return matrix;
}

void Transformation::draw(glm::mat4 &P, glm::mat4 &V, glm::mat4 &parentModelMatrix){
	glm::mat4 M = parentModelMatrix * matrix;
	Node::draw(P, V, M);
}