#ifndef DYNAMICGAMEOBJECT_H
#define DYNAMICGAMEOBJECT_H

#include "GameObject.h"

class DynamicGameObject : public GameObject{

public:
	DynamicGameObject(double _x = 0, double _y = 0, float _s = 0);
	~DynamicGameObject();

	void setVelocity(double _dx, double _dy);
	void setAngleVel(float _dPhi, float dTheta);

	void incrementPosition(double _dx = dx, double _dy = dy);
	void incrementAngleVel(float _dPhi = dPhi, float _dTheta = dTheta);


protected:
	double dx, dy;
	float dPhi, dTheta;

};
#endif