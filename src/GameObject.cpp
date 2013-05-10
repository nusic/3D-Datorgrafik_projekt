#include "GameObject.h"

GameObject::GameObject(double x, double y, double z, float s, float phi){

	translationNode = new Translation(x,y,z);
	rotationNode = new Rotation(translationNode, phi, glm::vec3(0.0f, 1.0f, 0.0f));
	scaleNode = new Scaling(rotationNode, s, s, s);
	modelNode = new Model(scaleNode, new ModelMesh("data/meshes/suzanne.obj"), "SimpleTexture2", "SimpleColor");

	setPosition(x, y, z);
	setScale(s);
	setDirection(phi, 0.0f);
	setVelocity(0.0f, 0.0f, 0.0f);

	speed = 5;

}

GameObject::~GameObject(){

};


void GameObject::setPosition(double x, double y, double z){
	position.x = x;
	position.y = y;
	position.z = z;
}

void GameObject::setYPosition(float y){
    position.y = y;
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

float GameObject::getSpeed() const{
	return speed;
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






void GameObject::setVelocity(double dx, double dy, double dz){
	velocity.x = dx;
	velocity.y = dy;
	velocity.z = dz;
}

void GameObject::setAngleVel(float _dPhi, float _dTheta){
	dPhi = _dPhi;
	dTheta = _dTheta;
}

void GameObject::update(float dt){
	position.x += velocity.x * dt * speed;
	position.y += velocity.y * dt * speed;
	position.z += velocity.z * dt * speed;

	translationNode->setTranslation(position.x, position.y, position.z);
	rotationNode->setRotation(phi, glm::vec3(0.0f, 1.0f, 0.0f));
	scaleNode->setScaling(scale.x, scale.y, scale.z);
}

void GameObject::incrementAngleVel(float _dPhi, float _dTheta){
	phi += _dPhi;
	theta += _dTheta;
}

void GameObject::incrementAngleVel(){
	phi += dPhi;
	theta += dTheta;
}

glm::vec3 GameObject::getVelocity(){
	return velocity;
}



void GameObject::updateMatrix(){

}

Node* GameObject::getSceneGraphBranch() const{
	return translationNode;
}

Model* GameObject::getMainModel() const{
	return modelNode;
}

