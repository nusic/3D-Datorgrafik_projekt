#include "FollowCamera.h"

FollowCamera::FollowCamera(GameObject* _target, float x, float y, float z) : Camera(x, y, z){
	target = _target;
}

void FollowCamera::updateLookAt(){
	setLookAt(target->getPosition().x, target->getPosition().y, target->getPosition().z);
}