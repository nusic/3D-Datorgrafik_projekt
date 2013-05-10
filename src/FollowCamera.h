#ifndef FOLLOWCAMERA_H
#define FOLLOWCAMERA_H

#include "sgct.h"
#include "Camera.h"
#include "DynamicGameObject.h"

class FollowCamera : public Camera{
public:
	FollowCamera(GameObject* _target, float x, float y, float z);
	~FollowCamera();

	void updateLookAt();

	GameObject* target;


private:


	
};

#endif