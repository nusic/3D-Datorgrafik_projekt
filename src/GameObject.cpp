#include "GameObject.h"

GameObject::GameObject(double x, double y, double z, float s, float phi):
Model(new ModelMesh("data/meshes/suzanne.obj"), glm::mat4(1.0f), "SimpleTexture2", "SimpleColor") {
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


glm::vec3 GameObject::getPosition(){
	return position;
}

void GameObject::incrementPosition(double dx, double dy, double dz){
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

void GameObject::incrementPositionAndTurnTo(double dx, double dy, double dz){
	position.x += dx;
	position.y += dy;
	position.z += dz;

	setDirection(180.0f/3.14159f * (float) glm::atan(dx,dz));
}

void GameObject::updateMatrix(){

	//OBS, the order is reversed
	glm::mat4 E(1.0f);

    glm::mat4 T = glm::translate(E, glm::vec3(position.x, position.y, position.z));
    glm::mat4 ST = glm::rotate(T, phi, glm::vec3(0.0f, 1.0f, 0.0f));
    localModelMatrix = glm::scale(ST, scale);
    
    for (int i = 0; i < children.size(); ++i)
    {
    	/* code */
    }
}
