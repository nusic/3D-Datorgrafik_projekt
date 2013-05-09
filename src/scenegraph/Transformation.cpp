#include "Transformation.h"

Transformation::Transformation(){
	matrix = glm::mat4(1.0f);
}

Transformation::~Transformation(){

}

glm::mat4 Transformation::getMatrix() const{
	return matrix;
}