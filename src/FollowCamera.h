#ifndef FOLLOWCAMERA_H
#define FOLLOWCAMERA_H

#include "sgct.h"
#include "Camera.h"
#include "Player.h"

class FollowCamera : public Camera{
public:
	FollowCamera(std::vector<Player*>& _targets);

	~FollowCamera();

	void setTargets(std::vector<Player*>& _targets);
	void setTheta(float _theta);
	void setFollowSpeed(float _followSpeed);
	void sitRotationSpeed(float _rotationSpeed);
	void setAngle(float _angle);

	virtual void update(float dt);

private:
	std::vector<Player*>& targets;
	float theta;
	float rotationSpeed;
	float followSpeed;
	float angle;
	float height;

	glm::vec3 getTargetsMinPos();
	glm::vec3 getTargetsMaxPos();
};

#endif