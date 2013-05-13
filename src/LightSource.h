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
	virtual void renderToDepthBuffer(glm::mat4 M, int lightSourceIndex);
	

	//This can only be called from the constructor
	bool initShadowMapBuffers();

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

	glm::mat4 getVP();
	static glm::mat4 getVPFromIndex(int index);


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

	//ShadowMap data
	static GLuint depthMatrixID; //Denna behövs det bara en av
	static GLuint depth_vertexPosition_modelspaceID; //Denna också

	static GLuint depthBiasID; //Array av depthBiasMVP-matriser i shadern

	static std::vector<GLuint> FBO;
	static std::vector<GLuint> depthTexture;


	static std::vector<glm::vec3> worldPosition;
	static std::vector<glm::vec3> worldDirection;

	static const int SHADOW_MAP_RESOLUTION = 1024;

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