#ifndef LIGHT_OBJECT_H
#define LIGHT_OBJECT_H 

#include "GameObject.h"
#include "LightSource.h"

class LightObject : public GameObject{

public:
	LightObject(double x = 0, double y = 0, double z = 0, float Scale = 1.0f, float _phi = 0);

	void setPosition(double x, double y, double z = 0);
	void setDirection(float phi = 0, float theta = 0);
	void setDirection(double x, double y, double z, double parentPhi = 0);

	void updateLightOrientation(glm::mat4 parentModelMatrix);


	LightSource * light;

};

#endif