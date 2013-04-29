#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H 

#include "sgct.h"


class LightSource{
public:
	LightSource(double _x, double _y, double _z, std::string _shaderName);
	~LightSource();
	void bindVariables();

	void setPosition(double _x, double _y, double _z);
	void setColor(double _r, double _g, double _b);
	void setDirection(double _x, double _y, double _z);
	void setSpread(float _s);
	void setDirectional(bool _d);

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