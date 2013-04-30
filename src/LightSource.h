#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H 

#include "sgct.h"


class LightSource{
public:
	LightSource(
		double _x = 0,
		double _y = 0,
		double _z = 0,
		std::string _shaderName = "SimpleColor");
	~LightSource();

	void bindVariables();


	void setPosition(double _x, double _y, double _z);
	void setColor(double _r, double _g, double _b);
	void setDirection(double _x, double _y, double _z);
	void setSpread(float _s);
	void setDirectional(bool _d);


	//Fruktansvärt fult med alla static. Kan man göra typ ett namespace eller nåt ist?

	static float* getPositionArray();
	static float* getColorArray();
	static float* getDirectionArray();
	static float* getSpreadArray();
	static bool* getDirectionalArray();

	static unsigned short getNumberOfLightSources();

	static GLuint lightPositionID;
	static GLuint lightColorID;
	static GLuint lightDirectionID;
	static GLuint lightSpreadID;
	static GLuint directionalID;

private:
	unsigned short index;
	static std::string shaderName;

	static std::vector<glm::vec3> position;
	static std::vector<glm::vec3> color;
	static std::vector<glm::vec3> direction;
	static std::vector<float> spread;
	static std::vector<bool> directional;

};

#endif