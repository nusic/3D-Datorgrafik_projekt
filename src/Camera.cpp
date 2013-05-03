#include "Camera.h"

Camera::Camera(double x, double y, double z){
	setPosition(x, y, z);
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

void Camera::setPosition(double x, double y, double z){
	position.x = x;
	position.y = y;
	position.z = z;
}

void Camera::setVelocity(double dx, double dy, double dz){
	velocity.x = dx;
	velocity.y = dy;
	velocity.z = dz;
}

void Camera::setLookAt(double x, double y, double z){
	lookAt.x = x;
	lookAt.y = y;
	lookAt.z = z;
}

void Camera::incrementPosition(){
	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;
}

void Camera::incrementPosition(double dx, double dy, double dz){
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

void Camera::calcMatrices(){
	viewMatrix = glm::lookAt(position, lookAt, up);
	perspectiveMatrix = glm::perspective(fov, aspect, zNearClipping, zFarClipping);
}

glm::mat4 Camera::getViewMatrix() const{
	return viewMatrix;
}

glm::mat4 Camera::getPerspectiveMatrix() const{
	return perspectiveMatrix;
}