#include "Transformation.h"

/*
	TRANSFORMATION
*/
Transformation::Transformation(Node * _parent):
Node(_parent){
	matrix = glm::mat4(1.0f);
}

Transformation::~Transformation(){

}

const glm::mat4& Transformation::getMatrix() const{
	return matrix;
}

void Transformation::renderToScreen(const glm::mat4 &P, const glm::mat4 &V, const glm::mat4 &parentModelMatrix){
	glm::mat4 M = parentModelMatrix * matrix;
	Node::renderToScreen(P, V, M);
}

void Transformation::renderToDepthBuffer(const glm::mat4 &VP, const glm::mat4 &parentModelMatrix){
	glm::mat4 M = parentModelMatrix * matrix;
	Node::renderToDepthBuffer(VP, M);
}






/*
	SCALING
*/

Scaling::Scaling(float sx, float sy, float sz){
	setScaling(sx,sy,sz);
}

Scaling::Scaling(Node * _parent, float sx, float sy, float sz):
Transformation(_parent){
	setScaling(sx,sy,sz);
}

Scaling::~Scaling(){

}

void Scaling::setScaling(float s){
	matrix[0][0] = s;
	matrix[1][1] = s;
	matrix[2][2] = s;
}

void Scaling::setScaling(float sx, float sy, float sz){
	matrix[0][0] = sx;
	matrix[1][1] = sy;
	matrix[2][2] = sz;
}

glm::vec3 Scaling::getScaling() const{
	return glm::vec3(matrix[0][0], matrix[1][1], matrix[2][2]);
}






/*
	ROTATION
*/

Rotation::Rotation(float angle, glm::vec3 _axis){
    axis = _axis;
	setRotation(angle);
}

Rotation::Rotation(Node * _parent, float angle, glm::vec3 _axis):
Transformation(_parent){
    axis = _axis;
	setRotation(angle);
}

Rotation::~Rotation(){

}

void Rotation::setRotation(float angle){
	/*
	Gillar inte riktigt att man måste kalla på konstruktorn för
	glm::mat4 varje gång man ska skapa en rotationsmatris med glm.
	Lättare optimering är dock att köra pass by reference. Kan börja
	med det om det skulle behövas.
	*/
	matrix = glm::rotate(glm::mat4(1.0f), angle, axis);
}

void Rotation::setAxis(glm::vec3 _axis){
    axis = _axis;
}





/*
	TRANSLATION
*/

Translation::Translation(float x, float y, float z){
	setTranslation(x, y, z);
}

Translation::Translation(Node* _parent, float x, float y, float z):
Transformation(_parent){
	setTranslation(x, y, z);
}

Translation::~Translation(){

}

void Translation::setTranslation(float x, float y, float z){
	matrix[3][0] = x;
	matrix[3][1] = y;
	matrix[3][2] = z;
}

glm::vec3 Translation::getTranslation() const{
	return glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
}
