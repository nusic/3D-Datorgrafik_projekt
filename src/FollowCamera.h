#ifndef FOLLOWCAMERA_H
#define FOLLOWCAMERA_H

#include "sgct.h"
#include "Camera.h"
#include "Player.h"

class FollowCamera : public Camera{
public:
	FollowCamera(
		std::vector<Player*> _targets,
		float _theta = 1.0f,
		float _followSpeed = 1,
		float _rotationSpeed = 1,
		float _angle = 0);

	~FollowCamera();

	void setTargets(std::vector<Player*> _targets);
	void setTheta(float _theta);
	void setFollowSpeed(float _followSpeed);
	void sitRotationSpeed(float _rotationSpeed);
	void setAngle(float _angle);

	virtual void update(float dt);

private:
	std::vector<Player*> targets;	
	float theta;
	float rotationSpeed;
	float followSpeed;
	float angle; 

	glm::vec3 getTargetsMinPos();
	glm::vec3 getTargetsMaxPos();
};

#endif