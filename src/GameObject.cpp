#include "GameObject.h"

GameObject::GameObject(double _x, double _y, float _s, float _phi):
Model(new ModelMesh("data/meshes/suzanne.obj"), glm::mat4(1.0f), "SimpleColor") {
	setPosition(_x, _y);
	setSize(_s);
	setDirection(_phi, 0.0f);
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

/*
	//Calc rotationg axis
	float sinPhi	= glm::sin(phi);
	float sinTheta 	= glm::sin(theta);
	float cosPhi	= glm::cos(phi);
	float cosTheta	= glm::cos(theta);

	glm::vec3 axis(	sinPhi * cosTheta,
					sinPhi * sinTheta,
					cosPhi			);
*/

	//Obs, the order is reversed
	glm::mat4 E(1.0f);
    glm::mat4 T = glm::translate(E, glm::vec3(x, 1.0f, -y));
    glm::mat4 ST = glm::rotate(T, phi, glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::scale(ST, glm::vec3(xs, ys, zs));
}

