#include "Rotation.h"

Rotation::Rotation(float angle, glm::vec3 axis){
	setRotation(angle, axis);
}

Rotation::~Rotation(){

}

void Rotation::setRotation(float angle, glm::vec3 axis){
	/*
	Gillar inte riktigt att man måste kalla på konstruktorn för 
	glm::mat4 varje gång man ska skapa en rotationsmatris med glm.
	*/
	matrix = glm::rotate(glm::mat4(1.0f), angle, axis);
}