#include "Camera.h"

const float FRAME_SPEED = 50;

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

void Camera::incrementPosition(float dt){
	position.x += velocity.x * dt * FRAME_SPEED;
	position.y += velocity.y * dt * FRAME_SPEED;
	position.z += velocity.z * dt * FRAME_SPEED;
}

void Camera::incrementPosition(double dx, double dy, double dz, float dt){
	position.x += dx * dt * FRAME_SPEED;
	position.y += dy * dt * FRAME_SPEED;
	position.z += dz * dt * FRAME_SPEED;
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