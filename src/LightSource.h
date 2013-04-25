#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H 

#include "sgct.h"


class LightSource{
public:
	LightSource();
	~LightSource();


private:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 color;

};

#endif