#ifndef DYNAMICGAMEOBJECT_H
#define DYNAMICGAMEOBJECT_H

#include "GameObject.h"

class DynamicGameObject : public GameObject{

public:
	DynamicGameObject(double _x = 0, double _y = 0, float _s = 1, float _phi = 0);
	~DynamicGameObject();

	void setVelocity(double _dx, double _dy);
	void setAngleVel(float _dPhi, float dTheta);

	void incrementPosition();
	void incrementPosition(double _dx, double _dy);
	void incrementAngleVel();
	void incrementAngleVel(float _dPhi, float _dTheta);


protected:
	double dx, dy;
	float dPhi, dTheta;

};
#endif
