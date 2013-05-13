#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H 

#include "sgct.h"
#include "Node.h"
#include <iostream>


class LightSource : public Node{
public:
	LightSource(double x, double y, double z, std::string _shaderName = "SimpleColor");
	LightSource(Node* _parent = NULL, double x = 0, double y = 0, double z = 0, std::string _shaderName = "SimpleColor");

	virtual ~LightSource();

	virtual void renderToScreen(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M);
	

	void setPosition(double x, double y, double z);
	void setDirection(double x, double y, double z);	

	void setWorldPosition(double x, double y, double z);
	void setWorldDirection(double x, double y, double z);
	void setColor(double r, double g, double b);
	void setIntensity(float i);
	void setSpread(float s);
	void setDirectional(bool d);

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


	void setStandardValues();
	void bindVariables();

};

#endif