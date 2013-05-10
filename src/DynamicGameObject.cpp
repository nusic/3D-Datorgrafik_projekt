#include "DynamicGameObject.h"

DynamicGameObject::DynamicGameObject(double x, double y, float s, float _phi):
GameObject(x, y, 0, s, _phi){
	speed = 5.0f;
	setVelocity(0.0, 0.0, 0.0);
}

DynamicGameObject::~DynamicGameObject(){

}

void DynamicGameObject::setVelocity(double dx, double dy, double dz){
	velocity.x = dx;
	velocity.y = dy;
	velocity.z = dz;
}

void DynamicGameObject::setAngleVel(float _dPhi, float _dTheta){
	dPhi = _dPhi;
	dTheta = _dTheta;
}

void DynamicGameObject::incrementPosition(float dt){

	position.x += velocity.x * dt * speed;
	position.y += velocity.y * dt * speed;
	position.z += velocity.z * dt * speed;
}

void DynamicGameObject::incrementAngleVel(float _dPhi, float _dTheta){
	phi += _dPhi;
	theta += _dTheta;
}

void DynamicGameObject::incrementAngleVel(){
	phi += dPhi;
	theta += dTheta;
}

glm::vec3 DynamicGameObject::getVelocity(){
	return velocity;
}
