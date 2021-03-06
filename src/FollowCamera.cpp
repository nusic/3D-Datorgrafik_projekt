#include "FollowCamera.h"

FollowCamera::FollowCamera(std::vector<Player*>& _targets):
Camera(0.0f, 0.0f, 0.0f), targets(_targets){
	theta = 1.0f;
	followSpeed = 1.0f;
	rotationSpeed = 1.0f;
	angle = 0.0f;
	height = 60.0f;
}

void FollowCamera::setTargets(std::vector<Player*>& _targets){
	targets = _targets;
}

void FollowCamera::setTheta(float _theta){
	theta = _theta;
}

void FollowCamera::setFollowSpeed(float _followSpeed){
	followSpeed = _followSpeed;
}

void FollowCamera::sitRotationSpeed(float _rotationSpeed){
	rotationSpeed = _rotationSpeed;
}

void FollowCamera::setAngle(float _angle){
	angle = _angle;
}

void FollowCamera::update(float dt){
	if(targets.size() == 0)
		return;

	angle -= rotationSpeed * 0.0005;

	glm::vec3 targetCenterGlobal = ((getTargetsMaxPos() + getTargetsMinPos()) * 0.5f);
	float maxTargetDistance = glm::length(getTargetsMaxPos() - getTargetsMinPos());
	float alpha = fov/2;
	float distance = glm::tan(alpha/180 * 3.1415) * maxTargetDistance / 2 * 5 + height;
	float height = glm::sin(theta) * distance;

	float l = glm::sqrt(abs(distance*distance - height*height));
	glm::vec3 cameraTargetPositionLocal = glm::vec3(l*glm::cos(angle), height, l*glm::sin(angle));
	glm::vec3 cameraTargetPositionGlobal = targetCenterGlobal + cameraTargetPositionLocal;

	glm::vec3 vectorDistanceToTarget = cameraTargetPositionGlobal - getPosition();
	glm::vec3 vectorDistanceToLookAt = targetCenterGlobal - lookAt;

	glm::vec3 lookAtDiff = followSpeed * dt * vectorDistanceToLookAt * 2.0f;
	setVelocity(
		followSpeed * vectorDistanceToTarget.x / 10,
		followSpeed * vectorDistanceToTarget.y / 10,
		followSpeed * vectorDistanceToTarget.z / 10);

	incrementPosition(dt);
	lookAt += lookAtDiff;

	Camera::update(dt);
}

glm::vec3 FollowCamera::getTargetsMinPos(){
	glm::vec3 minPos = targets[0]->getPosition();
	for (int i = 1; i < targets.size(); ++i){
		if (targets[i]->getPosition().x < minPos.x)
			minPos.x = targets[i]->getPosition().x;
		if (targets[i]->getPosition().y < minPos.y)
			minPos.y = targets[i]->getPosition().y;
		if (targets[i]->getPosition().z < minPos.z)
			minPos.z = targets[i]->getPosition().z;
	}
	return minPos;
}

glm::vec3 FollowCamera::getTargetsMaxPos(){
	glm::vec3 maxPos = targets[0]->getPosition();
	for (int i = 1; i < targets.size(); ++i){
		if (targets[i]->getPosition().x > maxPos.x)
			maxPos.x = targets[i]->getPosition().x;
		if (targets[i]->getPosition().y > maxPos.y)
			maxPos.y = targets[i]->getPosition().y;
		if (targets[i]->getPosition().z > maxPos.z)
			maxPos.z = targets[i]->getPosition().z;
	}
	return maxPos;
}