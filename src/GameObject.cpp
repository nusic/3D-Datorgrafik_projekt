#include "GameObject.h"

GameObject::GameObject(double _x, double _y, float _s):
Model(	new ModelMesh("data/meshes/suzanne.obj"), 
		glm::mat4(1.0f), 
		"SimpleColor") {
	setPosition(_x, _y);
	setSize(_s);
	updateMatrix();
}

GameObject::~GameObject(){

};


void GameObject::setPosition(double _x, double _y){
	x = _x;
	y = _y;
}

void GameObject::setDirection(float _phi, float _theta){
	phi = _phi;
	theta = _theta;
}

void GameObject::setSize(float s){
	xs = ys = zs = s;
}

void GameObject::setSize(float _xs, float _ys, float _zs){
	xs = _xs;
	ys = _ys;
	zs = _zs;
}

void GameObject::updateMatrix(){
	glm::mat4 E(1.0f);
	glm::mat4 S = glm::scale(E, glm::vec3(xs, ys, zs));
/*
	//Calc rotationg axis
	float sinPhi	= glm::sin(phi);
	float sinTheta 	= glm::sin(theta);
	float cosPhi	= glm::cos(phi);
	float cosTheta	= glm::cos(theta);

	glm::vec3 axis(	sinPhi * cosTheta,
					sinPhi * sinTheta,
					cosPhi			);

	glm::mat4 SR = glm::rotate(S, axis);
*/

	glm::mat4 SR = glm::rotate(S, phi, glm::vec3(0.0f, 1.0f, 0.0f));

	//The Z-value needs to be calculated (mapped value)

	modelMatrix = glm::translate(SR, glm::vec3(x, y, 0.0f));
}

