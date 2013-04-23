#include "DynamicGameObject.h"



DynamicGameObject::DynamicGameObject(double _x, double _y, float _s, float _phi):
GameObject(_x, _y, _s, _phi){
	setVelocity(0.0, 0.0);
}

DynamicGameObject::~DynamicGameObject(){

}

void DynamicGameObject::setVelocity(double _dx, double _dy){
	dx = _dx;
	dy = _dy;
}

void DynamicGameObject::setAngleVel(float _dPhi, float _dTheta){
	dPhi = _dPhi;
	dTheta = _dTheta;	
}

void DynamicGameObject::incrementPosition(double _dx, double _dy){
	x += _dx;
	y += _dy;
}

void DynamicGameObject::incrementPosition(){
	x += dx;
	y += dy;
}

void DynamicGameObject::incrementAngleVel(float _dPhi, float _dTheta){
	phi += _dPhi;
	theta += _dTheta;
}

void DynamicGameObject::incrementAngleVel(){
	phi += dPhi;
	theta += dTheta;
}