#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H 

#include "sgct.h"


class LightSource{
public:
	LightSource(double _x, double _y, double _z, std::string _shaderName);
	~LightSource();
	void bindVariables();

	GLuint lightPositionID;
	GLuint lightColorID;
	GLuint lightDirectionID;
	GLuint lightSpreadID;
	GLuint directionalID;

	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 direction;
	float spread;

	bool directional;

private:
	std::string shaderName;

};

//Pippi Långstrump

#endif