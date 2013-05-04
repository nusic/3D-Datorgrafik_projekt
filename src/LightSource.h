#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H 

#include "sgct.h"
#include <iostream>


class LightSource{
public:
	LightSource(double x=0, double y=0, double z=0, std::string _shaderName = "SimpleColor");
	~LightSource();

	void bindVariables();


	void setPosition(double _x, double _y, double _z);
	void setColor(double _r, double _g, double _b);
	void setDirection(double _x, double _y, double _z);
	void setIntensity(float _i);
	void setSpread(float _s);
	void setDirectional(bool _d);

	glm::vec3 getPosition();
	glm::vec3 getDirection();


	static float* getPositionArray();
	static float* getColorArray();
	static float* getDirectionArray();
	static float* getIntensityArray();
	static float* getSpreadArray();
	static int* getDirectionalArray();

	static unsigned short getNumberOfLightSources();

	static GLuint lightPositionID;
	static GLuint lightColorID;
	static GLuint lightDirectionID;
	static GLuint lightIntensityID;
	static GLuint lightSpreadID;
	static GLuint directionalID;
	static GLuint numberOfLightsID;

	static std::vector<glm::vec3> position;
	static std::vector<glm::vec3> direction;

private:
	unsigned short index;
	static std::string shaderName;

	
	static std::vector<glm::vec3> color;
	
	static std::vector<float> intensity;
	static std::vector<float> spread;
	static std::vector<int> directional;


};

#endif