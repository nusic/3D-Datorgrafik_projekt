#include "DynamicGameObject.h"


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

void DynamicGameObject::incrementPosition(double dx, double dy, double dz){
	position.x += dx;
	position.y += dy;
	position.z += dy;
}

void DynamicGameObject::incrementPosition(){
	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.y;
}

void DynamicGameObject::incrementAngleVel(float _dPhi, float _dTheta){
	phi += _dPhi;
	theta += _dTheta;
}

void DynamicGameObject::incrementAngleVel(){
	phi += dPhi;
	theta += dTheta;
}
