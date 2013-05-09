#include "DynamicGameObject.h"

const float FRAME_SPEED = 50;

DynamicGameObject::DynamicGameObject(double x, double y, float s, float _phi):
GameObject(x, y, 0, s, _phi){
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

void DynamicGameObject::incrementPosition(double dx, double dy, double dz, float dt){
	position.x += dx * dt * FRAME_SPEED;
	position.y += dy * dt * FRAME_SPEED;
	position.z += dz * dt * FRAME_SPEED;
}

void DynamicGameObject::incrementPosition(float dt){
	position.x += velocity.x * dt * FRAME_SPEED;
	position.y += velocity.y * dt * FRAME_SPEED;
	position.z += velocity.z * dt * FRAME_SPEED;
}

void DynamicGameObject::incrementPositionAndTurnTo(double dx, double dy, double dz, float dt){
	position.x += dx * dt * FRAME_SPEED;
	position.y += dy * dt * FRAME_SPEED;
	position.z += dz * dt * FRAME_SPEED;

	velocity.x = dx;
	velocity.y = dy;
	velocity.z = dz;

	setDirection(180.0f/3.14159f * (float) glm::atan(dx,dz));
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
