#include "Camera.h"

Camera::Camera(double _x, double _y, double _z){
	setPosition(_x, _y, _z);
	setVelocity(0.0, 0.0, 0.0);
	setLookAt(0.0, 0.0, 0.0);

	fov = 45.0f;
	aspect = 4.0f / 3.0f;
	zNearClipping = 0.1f;
	zFarClipping = 100.0f;

	up.x = 0;
	up.y = 1;
	up.z = 0;

}

Camera::~Camera(){

}

void Camera::setPosition(double _x, double _y, double _z){
	position.x = _x;
	position.y = _y;
	position.z = _z;
}

void Camera::setVelocity(double _dx, double _dy, double _dz){
	velocity.x = _dx;
	velocity.y = _dy;
	velocity.z = _dz;
}

void Camera::setLookAt(double _x, double _y, double _z){
	lookAt.x = _x;
	lookAt.y = _y;
	lookAt.z = _z;
}

void Camera::incrementPosition(){
	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;
}

void Camera::incrementPosition(double _dx, double _dy, double _dz){
	position.x += _dx;
	position.y += _dy;
	position.z += _dz;
}

glm::mat4 Camera::getViewMatrix() const{

	return glm::lookAt(position, lookAt, up);
}

glm::mat4 Camera::getPerspectiveMatrix() const{

	return glm::perspective(fov, aspect, zNearClipping, zFarClipping);
}