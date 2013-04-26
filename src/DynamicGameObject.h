#ifndef DYNAMICGAMEOBJECT_H
#define DYNAMICGAMEOBJECT_H

#include "GameObject.h"

class DynamicGameObject : public GameObject{

public:
	DynamicGameObject(double x = 0, double y = 0, float s = 1, float _phi = 0);
	~DynamicGameObject();

	void setVelocity(double dx = 0, double dy = 0, double d = 0);
	void setAngleVel(float _dPhi, float dTheta);

	void incrementPosition();
	void incrementPosition(double dx, double dy, double dz = 0);

	void incrementAngleVel();
	void incrementAngleVel(float _dPhi, float _dTheta);


protected:
	glm::vec3 velocity;
	float dPhi, dTheta;

};
#endif
