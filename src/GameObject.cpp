#include "GameObject.h"

GameObject::GameObject(double x, double y, double z, float s, float phi):
Model(new ModelMesh("data/meshes/suzanne.obj"), glm::mat4(1.0f), "SimpleTexture", "SimpleColor") {
	setPosition(x, y, z);
	setScale(s);
	setDirection(phi, 0.0f);
	updateMatrix();
}

GameObject::~GameObject(){

};


void GameObject::setPosition(double x, double y, double z){
	position.x = x;
	position.y = y;
	position.z = z;
}

void GameObject::setDirection(float _phi, float _theta){
	phi = _phi;
	theta = _theta;
}

void GameObject::setScale(float s){
	scale.x = scale.y = scale.z = s;
}

void GameObject::setScale(float xs, float ys, float zs){
	scale.x = xs;
	scale.y = ys;
	scale.z = zs;
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
    //glm::mat4 T = glm::translate(E, glm::vec3(position.x, position.z, -position.y));
    glm::mat4 T = glm::translate(E, glm::vec3(position.x, position.z, -position.y));
    glm::mat4 ST = glm::rotate(T, phi, glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::scale(ST, scale);
}

