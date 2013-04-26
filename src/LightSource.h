#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H 

#include "sgct.h"


class LightSource{
public:
	LightSource(double _x, double _y, double _z);
	~LightSource();

private:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 direction;
	float spread;

	bool directional;
};

#endif;