#include "LightSource.h"
#include "sgct.h"

LightSource::LightSource(
	double _x,
	double _y,
	double _z,
	std::string _shaderName){

	LightSource::position.push_back(glm::vec3(_x, _y, _z));
	LightSource::color.push_back(glm::vec3(1,1,1));
	LightSource::direction.push_back(glm::vec3(0,0,0));
	LightSource::spread.push_back(1);
	LightSource::directional.push_back(true);

	index = LightSource::position.size() - 1;

	shaderName = _shaderName;
}

std::string LightSource::shaderName = "SimpleColor";

std::vector<glm::vec3> LightSource::position;
std::vector<glm::vec3> LightSource::color;
std::vector<glm::vec3> LightSource::direction;
std::vector<float> LightSource::spread;
std::vector<bool> LightSource::directional;

GLuint LightSource::lightPositionID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightPosition_worldSpace");
GLuint LightSource::lightColorID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightColor");
GLuint LightSource::lightDirectionID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightDirection_worldSpace");
GLuint LightSource::lightSpreadID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("lightSpread");
GLuint LightSource::directionalID = sgct::ShaderManager::Instance()->getShader(shaderName).getUniformLocation("directional");


void LightSource::setPosition(double _x, double _y, double _z){
	LightSource::position[index] = glm::vec3(_x, _y, _z);
}

void LightSource::setColor(double _r, double _g, double _b){
	LightSource::color[index] = glm::vec3(_r, _g, _b);
}

void LightSource::setDirection(double _x, double _y, double _z){
	LightSource::direction[index] = glm::vec3(_x, _y, _z);
}

void LightSource::setSpread(float _s){
	LightSource::spread[index] = _s;
}

void LightSource::setDirectional(bool _d){
	LightSource::directional[index] = _d;
}


float* LightSource::getPositionArray(){
	return &(LightSource::position[0].x);
}

float* LightSource::getColorArray(){
	return &(LightSource::color[0].x);
}

float* LightSource::getDirectionArray(){
	return &(LightSource::direction[0].x);
}

float* LightSource::getSpreadArray(){
	return &LightSource::spread[0];
}
/*
bool* LightSource::getDirectionalArray(){
	return &LightSource::directional[0];
}
*/

unsigned short LightSource::getNumberOfLightSources(){
	return position.size();
}

LightSource::~LightSource(){
	
}