#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H 

#include "sgct.h"
#include "Node.h"
#include <iostream>


class LightSource : public Node{
public:
	LightSource(double x=0, double y=0, double z=0, std::string _shaderName = "SimpleColor");
	virtual ~LightSource();

	virtual void draw(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M);

	void bindVariables();

	void setPosition(double x, double y, double z);
	void setDirection(double x, double y, double z);	

	void setWorldPosition(double _x, double _y, double _z);
	void setWorldDirection(double _x, double _y, double _z);
	void setColor(double _r, double _g, double _b);
	void setIntensity(float _i);
	void setSpread(float _s);
	void setDirectional(bool _d);

	glm::vec3 getPosition();
	glm::vec3 getDirection();
	glm::vec3 getWorldPosition();
	glm::vec3 getWorldDirection();


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

	//Detta är globala variabler
	static std::vector<glm::vec3> worldPosition;
	static std::vector<glm::vec3> worldDirection;

private:
	glm::vec3 position;
	glm::vec3 direction;

	unsigned short index;
	static std::string shaderName;

	
	static std::vector<glm::vec3> color;
	
	static std::vector<float> intensity;
	static std::vector<float> spread;
	static std::vector<int> directional;


};

#endif